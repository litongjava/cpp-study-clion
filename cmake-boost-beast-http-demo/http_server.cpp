#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

#ifdef _WIN32
// Windows系统

#elif defined(__APPLE__)
// macOS系统
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>

#elif defined(__linux__)
// Linux系统
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>

#endif


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace my_program_state {
  std::size_t
  request_count() {
    static std::size_t count = 0;
    return ++count;
  }

  std::time_t
  now() {
    return std::time(0);
  }
}


class http_connection : public std::enable_shared_from_this<http_connection> {
public:
  http_connection(tcp::socket socket)
    : socket_(std::move(socket)) {
  }

  // Initiate the asynchronous operations associated with the connection.
  void start() {
    read_request();
    check_deadline();
  }

private:
  // The socket for the currently connected client.
  tcp::socket socket_;

  // The buffer for performing reads.
  beast::flat_buffer buffer_{8192};

  // The request message.
  http::request<http::dynamic_body> request_;

  // The response message.
  http::response<http::dynamic_body> response_;

  // The timer for putting a deadline on connection processing.
  net::steady_timer deadline_{
    socket_.get_executor(), std::chrono::seconds(60)};

  // Asynchronously receive a complete request message.
  void read_request() {
    const std::shared_ptr<http_connection> &self = shared_from_this();

    auto handler = [self](beast::error_code ec, std::size_t bytes_transferred) {
      boost::ignore_unused(bytes_transferred);
      if (!ec) {
        self->process_request();
      }

    };
    http::async_read(socket_, buffer_, request_, handler);
  }

  // Determine what needs to be done with the request message.
  void process_request() {
    if (request_.target() == "/ws/ws1") {
      // 升级到WebSocket
      if (boost::beast::websocket::is_upgrade(request_)) {
        // 创建一个新的WebSocket会话
        std::make_shared<websocket_session>(std::move(socket_))->run(std::move(request_));
        return; // WebSocket会话接管了socket
      }
    }

    response_.version(request_.version());
    response_.keep_alive(false);

    switch (request_.method()) {
      case http::verb::get:
        response_.result(http::status::ok);
        response_.set(http::field::server, "Beast");
        create_response();
        break;
      case http::verb::post:
        response_.result(http::status::ok);
        response_.set(http::field::server, "Beast");
        create_post_response();
        break;
      default:
        // We return responses indicating an error if
        // we do not recognize the request method.
        response_.result(http::status::bad_request);
        response_.set(http::field::content_type, "text/plain");
        beast::ostream(response_.body())
          << "Invalid request-method '"
          << std::string(request_.method_string())
          << "'";
        break;
    }

    write_response();
  }

  // Construct a response message based on the program state.
  void create_response() {
    if (request_.target() == "/count") {
      response_.set(http::field::content_type, "text/html");
      beast::ostream(response_.body())
        << "<html>\n"
        << "<head><title>Request count</title></head>\n"
        << "<body>\n"
        << "<h1>Request count</h1>\n"
        << "<p>There have been "
        << my_program_state::request_count()
        << " requests so far.</p>\n"
        << "</body>\n"
        << "</html>\n";
    } else if (request_.target() == "/time") {
      response_.set(http::field::content_type, "text/html");
      beast::ostream(response_.body())
        << "<html>\n"
        << "<head><title>Current time</title></head>\n"
        << "<body>\n"
        << "<h1>Current time</h1>\n"
        << "<p>The current time is "
        << my_program_state::now()
        << " seconds since the epoch.</p>\n"
        << "</body>\n"
        << "</html>\n";
    } else {
      response_.result(http::status::not_found);
      response_.set(http::field::content_type, "text/plain");
      beast::ostream(response_.body()) << "File not found\r\n";
    }
  }

  void create_post_response() {
    if (request_.target() == "/email") {
      beast::basic_multi_buffer<std::allocator<char>> &body = this->request_.body();
      const std::string &body_str = boost::beast::buffers_to_string(body.data());
      std::cout << "receive body is " << body_str << std::endl;
      this->response_.set(http::field::content_type, "text/json");
      Json::Value root;
      Json::Reader reader;
      Json::Value src_root;
      bool parse_success = reader.parse(body_str, src_root);
      if (!parse_success) {
        std::cout << "Failed to parse JSON data!" << std::endl;
        root["error"] = 1001;
        std::string jsonstr = root.toStyledString();
        beast::ostream(this->response_.body()) << jsonstr;
        return;
      }

      const Json::String &email = src_root["email"].asString();
      std::cout << "email is " << email << std::endl;

      root["error"] = 0;
      root["email"] = src_root["email"];
      root["msg"] = "recevie email post success";
      std::string jsonstr = root.toStyledString();
      beast::ostream(this->response_.body()) << jsonstr;
    } else {
      response_.result(http::status::not_found);
      response_.set(http::field::content_type, "text/plain");
      beast::ostream(response_.body()) << "File not found\r\n";
    }
  }

  // Asynchronously transmit the response message.
  void write_response() {
    const std::shared_ptr<http_connection> &self = shared_from_this();

    response_.content_length(response_.body().size());

    auto handler = [self](beast::error_code ec, std::size_t) {
      self->socket_.shutdown(tcp::socket::shutdown_send, ec);
      self->deadline_.cancel();
    };
    http::async_write(
      socket_,
      response_,
      handler);
  }

  // Check whether we have spent enough time on this connection.
  void check_deadline() {
    const std::shared_ptr<http_connection> &self = shared_from_this();

    auto handler = [self](beast::error_code ec) {
      if (!ec) {
        // Close socket to cancel any outstanding operation.
        self->socket_.close(ec);
      }
    };

    deadline_.async_wait(handler);
  }
};

// "Loop" forever accepting new connections.
void http_server(tcp::acceptor &acceptor, tcp::socket &socket) {
  // 定义回调函数
  auto accept_handler = [&acceptor, &socket](beast::error_code ec) {
    if (!ec) {
      std::make_shared<http_connection>(std::move(socket))->start();
    }
    http_server(acceptor, socket);
  };

  // 使用定义的回调函数
  acceptor.async_accept(socket, accept_handler);
}

int main(int argc, char *argv[]) {
  const boost::asio::ip::address address = net::ip::make_address("127.0.0.1");
  ushort port = static_cast<unsigned short>(8080);

  try {
    net::io_context ioc{1};

    tcp::acceptor acceptor{ioc, {address, port}};
    tcp::socket socket{ioc};
    http_server(acceptor, socket);
    ioc.run();
  }
  catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
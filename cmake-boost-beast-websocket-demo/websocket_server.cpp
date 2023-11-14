#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include <thread>

namespace beast = boost::beast;    // from <boost/beast.hpp>
namespace http = beast::http; // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;  // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;  // from <boost/asio/ip/tcp.hpp>

void do_session(tcp::socket &socket) {
  try {
    websocket::stream <tcp::socket> ws{std::move(socket)};
    ws.accept();

    for (;;) {
      beast::flat_buffer buffer;
      ws.read(buffer);
      ws.text(ws.got_text());
      ws.write(buffer.data());
    }
  }
  catch (beast::system_error const &se) {
    if (se.code() != websocket::error::closed)
      std::cerr << "Error: " << se.code().message() << std::endl;
  }
  catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

int main() {
  try {
    net::io_context ioc{1};
    tcp::acceptor acceptor{ioc, {net::ip::make_address("0.0.0.0"), 8080}};
    for (;;) {
      tcp::socket socket{ioc};
      acceptor.accept(socket);
      std::thread{std::bind(&do_session, std::move(socket))}.detach();
    }
  }
  catch (std::exception const &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
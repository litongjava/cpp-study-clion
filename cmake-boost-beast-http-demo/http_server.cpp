#include "http_default_handler.h"
#include <boost/asio/spawn.hpp>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// "Loop" forever accepting new connections.
void http_server(tcp::acceptor &acceptor, tcp::socket &socket) {
  // 定义回调函数
  auto accept_handler = [&acceptor, &socket](beast::error_code ec) {
    if (!ec) {
      std::make_shared<http_default_handler>(std::move(socket))->start();
    }
    http_server(acceptor, socket);
  };

  // 使用定义的回调函数
  acceptor.async_accept(socket, accept_handler);
}

int main(int argc, char *argv[]) {
  const boost::asio::ip::address address = net::ip::make_address("127.0.0.1");
  unsigned short port = static_cast<unsigned short>(8080);

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
#include "WebSocketServer.h"

WebSocketServer::WebSocketServer(net::io_context &ioc, unsigned short port)
  : _ioc(ioc),
    _acceptor(ioc, net::ip::tcp::endpoint(net::ip::tcp::v4(), port)){
  std::cout << "Server start on port : " << port << std::endl;
}

void WebSocketServer::StartAccept() {
  auto con_ptr = std::make_shared<Connection>(_ioc);
  boost::asio::ip::tcp::socket &socket = con_ptr->GetSocket();

  auto token = [this, con_ptr](error_code err) {
    try {
      if (!err) {
        con_ptr->AsyncAccept();
      } else {
        int errorCode = err.value();
        const std::string &string = err.message();
        std::cout << "acceptor async_accept failed, err is " << errorCode << &string << std::endl;
      }

      StartAccept();
    }
    catch (std::exception &exp) {
      std::cout << "async_accept error is " << exp.what() << std::endl;
    }
  };

  _acceptor.async_accept(socket, token);
}
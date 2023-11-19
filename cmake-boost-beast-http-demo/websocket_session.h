//
// Created by Administrator on 11/19/2023.
//
#pragma once

#include <memory>

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/http/dynamic_body.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/websocket/stream.hpp>
#include <boost/beast/websocket/impl/stream.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/flat_buffer.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class websocket_session : public std::enable_shared_from_this<websocket_session> {
public:
  explicit websocket_session(tcp::socket socket)
    : ws_(std::move(socket)) {}

  void run(http::request<http::dynamic_body> req) {
    // 接受WebSocket握手
    auto handler = [self = shared_from_this()](beast::error_code ec) {
      if (!ec) {
        self->read_message();
      }
    };
    ws_.async_accept(req, handler);
  }

private:
  beast::websocket::stream<beast::tcp_stream> ws_;

  void read_message() {
    // 读取WebSocket消息
    auto handler = [self = shared_from_this()](beast::error_code ec, std::size_t bytes) {
      if (!ec) {
        self->write_message(bytes);
      }
    };
    ws_.async_read(buffer_, handler);
  }

  void write_message(std::size_t bytes) {
    // 回应WebSocket消息
    ws_.text(ws_.got_text());
    auto handler = [self = shared_from_this()](beast::error_code ec, std::size_t) {
      if (!ec) {
        self->buffer_.consume(self->buffer_.size());
        self->read_message();
      }
    };
    ws_.async_write(buffer_.data(), handler);
  }

  beast::flat_buffer buffer_;
};




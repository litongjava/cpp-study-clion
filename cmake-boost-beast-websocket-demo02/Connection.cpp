#include "Connection.h"
#include "ConnectionMgr.h"

Connection::Connection(boost::asio::io_context &ioc)
  : _ioc(ioc),
    _ws_ptr(std::make_unique<stream<tcp_stream>>(make_strand(ioc))) {
  // 生成随机的 UUID
  boost::uuids::random_generator generator;
  boost::uuids::uuid uuid = generator();

  // 将 UUID 转换为字符串
  _uuid = boost::uuids::to_string(uuid);
}

std::string Connection::GetUid() {
  return _uuid;
}

boost::asio::ip::tcp::socket &Connection::GetSocket() {
  auto &socket = boost::beast::get_lowest_layer(*_ws_ptr).socket();
  return socket;
}

void Connection::AsyncAccept() {
  auto self = shared_from_this();
  auto handler = [self](boost::system::error_code err) {
    try {
      if (!err) {
        ConnectionMgr::GetInstance().AddConnection(self);
        self->Start();
      } else {
        const std::string &string = err.message();
        std::cout << "websocket accept failed, err is " << &string << std::endl;
      }
    }
    catch (std::exception &exp) {
      std::cout << "websocket async accept exception is " << exp.what();
    }
  };
  _ws_ptr->async_accept(handler);
}

void Connection::Start() {
  auto self = shared_from_this();
  auto handler = [self](error_code err, std::size_t buffer_bytes) {
    try {
      if (err) {
        const std::string &message = err.message();
        std::cout << "websocket async read error is " << &message << std::endl;
        ConnectionMgr::GetInstance().RmvConnection(self->GetUid());
        return;
      }
      self->_ws_ptr->text(self->_ws_ptr->got_text());
      std::string recv_data = boost::beast::buffers_to_string(self->_recv_buffer.data());
      self->_recv_buffer.consume(self->_recv_buffer.size());
      std::cout << "websocket receive msg is " << recv_data << std::endl;
      self->AsyncSend(std::move(recv_data));
      self->Start();
    }
    catch (std::exception &exp) {
      std::cout << "exception is " << exp.what() << std::endl;
      ConnectionMgr::GetInstance().RmvConnection(self->GetUid());
    }
  };
  _ws_ptr->async_read(_recv_buffer, handler);
}

void Connection::AsyncSend(std::string msg) {
  {
    std::lock_guard<std::mutex> lck_gurad(_send_mtx);
    int que_len = _send_que.size();
    _send_que.push(msg);
    if (que_len > 0) {
      return;
    }
  }

  SendCallBack(std::move(msg));
}


void Connection::SendCallBack(std::string msg) {
  auto self = shared_from_this();
  auto handler = [self](error_code err, std::size_t nsize) {
    try {
      if (err) {
        const std::string &message = err.message();
        std::cout << "async send err is " << &message << std::endl;
        ConnectionMgr::GetInstance().RmvConnection(self->_uuid);
        return;
      }

      std::string send_msg;
      {
        std::lock_guard<std::mutex> lck_gurad(self->_send_mtx);
        self->_send_que.pop();
        if (self->_send_que.empty()) {
          return;
        }

        send_msg = self->_send_que.front();
      }

      self->SendCallBack(std::move(send_msg));
    }
    catch (std::exception &exp) {
      std::cout << "async send exception is " << exp.what() << std::endl;
      ConnectionMgr::GetInstance().RmvConnection(self->_uuid);
    }
  };
  const boost::asio::const_buffers_1 &buffers1 = boost::asio::buffer(msg.c_str(), msg.length());
  _ws_ptr->async_write(buffers1, handler);
}

#include <uwebsockets/App.h>
#include <iostream>

int main() {
  uWS::App().get("/hello", [](auto *res, auto *req) {
    res->end("Hello World!");
  }).listen(3000, [](auto *token) {
    if (token) {
      std::cout << "Server started on port 3000" << std::endl;
    } else {
      std::cerr << "Failed to start server" << std::endl;
    }
  }).run();
}

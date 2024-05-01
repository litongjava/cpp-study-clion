#include <iostream>
#include <httplib.h>

void handler(const httplib::Request &req, httplib::Response &res) {
  res.set_content("Hello, World!", "text/plain");
};

int main() {
  int port = 8080;
  printf("Server is running on port %d\n", port);
  httplib::Server svr;

  svr.Get("/", handler);

  if (!svr.listen("0.0.0.0", port)) {
    std::cerr << "Error starting server on port " << port << std::endl;
    return 1;
  }

  return 0;
}
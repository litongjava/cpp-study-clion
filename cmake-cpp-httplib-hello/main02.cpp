#include <iostream>
#include <string>
#include <httplib.h>

int main(int argc, char *argv[]) {
  httplib::Server svr;

  svr.Get("/", [](const httplib::Request &req, httplib::Response &res) {
    res.set_content("Hello, World!", "text/plain");
  });

  std::string host = "localhost";
  int port = 8080;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--host") {
      if (i + 1 < argc) {
        host = argv[++i];
      } else {
        std::cerr << "--host requires an argument" << std::endl;
        return 1;
      }
    } else if (arg == "--port") {
      if (i + 1 < argc) {
        port = std::stoi(argv[++i]);
      } else {
        std::cerr << "--port requires an argument" << std::endl;
        return 1;
      }
    } else {
      std::cerr << "Unknown option: " << arg << std::endl;
      return 1;
    }
  }

  std::cout << "Server is running on host " << host << " and port " << port << "..." << std::endl;
  svr.listen(host.c_str(), port);

  return 0;
}

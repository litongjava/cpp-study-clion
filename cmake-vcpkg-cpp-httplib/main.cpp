#include <iostream>
#include <httplib.h>
#include <chrono>
#include <thread>

void handler(const httplib::Request &req, httplib::Response &res) {
  res.set_content("Hello, World!", "text/plain");
};


void sse_handler(const httplib::Request &req, httplib::Response &res) {
  // Set headers for SSE
  res.set_header("Cache-Control", "no-cache");
  res.set_header("Content-Type", "text/event-stream");
  res.set_header("Connection", "keep-alive");

  res.set_content_provider(
    "text/event-stream", // Content type
    [&](size_t offset, httplib::DataSink &sink) -> bool {
      auto s = "data: Hello at " + std::to_string(time(nullptr)) + "\n\n";
      sink.write(s.data(), s.size());
      std::this_thread::sleep_for(std::chrono::seconds(2));  // simulate wait
      return true;  // continue sending data
    },
    [](bool success) {
      // Finalize the response. You can handle the success or failure case here if needed.
    }
  );
};

int main() {
  int port = 8090;
  printf("Server is running on port %d\n", port);
  httplib::Server svr;

  svr.Get("/", handler);
  svr.Get("/events", sse_handler);

  if (!svr.listen("0.0.0.0", port)) {
    std::cerr << "Error starting server on port " << port << std::endl;
    return 1;
  }

  return 0;
}
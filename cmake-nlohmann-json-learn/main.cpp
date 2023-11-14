#include <iostream>
#include "json.hpp"
int main() {
  std::string results = "hello";
  nlohmann::json  json_object= nlohmann::json{{"content", results}};
  auto json_string=json_object.dump(-1, ' ', false,nlohmann::json::error_handler_t::replace);
  std::cout << json_string << std::endl;
  return 0;
}

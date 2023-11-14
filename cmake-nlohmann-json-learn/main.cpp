#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
int main() {

  json jres;
  std::string results = "hello";
  jres = json{{"content", results}};

  auto json_string=jres.dump(-1, ' ', false, json::error_handler_t::replace);

  std::cout << json_string << std::endl;
  return 0;
}

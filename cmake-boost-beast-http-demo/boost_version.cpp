#include <boost/version.hpp>
#include <iostream>

int main() {
  std::cout << "Boost version: "
            << BOOST_VERSION / 100000 << "."  // 主版本号
            << BOOST_VERSION / 100 % 1000 << "."  // 次版本号
            << BOOST_VERSION % 100             // 补丁级别
            << std::endl;
  return 0;
}

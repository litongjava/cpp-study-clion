#include <iostream>
#include <mpg123.h>

int main() {
  // 初始化libmpg123库
  mpg123_init();

  const char *okInfo = mpg123_plain_strerror(MPG123_OK);
  std::cout << "MPG123_OK: " << okInfo << std::endl;

  // 清理库
  mpg123_exit();

  return 0;
}

#include <iostream>
#include <mpg123.h>

int main() {
  const char *file_path = "../samples/Apollo13-wehaveaproblem.ogg.mp3";

  // 初始化mpg123库
  mpg123_init();
  mpg123_handle *mh = mpg123_new(NULL, NULL);
  if (mh == NULL) {
    std::cerr << "Error: Unable to create mpg123 handle." << std::endl;
    return 1;
  }

  // 打开MP3文件
  if (mpg123_open(mh, file_path) != MPG123_OK) {
    std::cerr << "Error: Unable to open file." << std::endl;
    return 1;
  }

  // 获取MP3文件的信息
  long rate;
  int channels, encoding;
  if (mpg123_getformat(mh, &rate, &channels, &encoding) != MPG123_OK) {
    std::cerr << "Error: Unable to get format information." << std::endl;
    return 1;
  }

  // 打印信息
  std::cout << "File: " << file_path << std::endl;
  std::cout << "Sample Rate: " << rate << " Hz" << std::endl;
  std::cout << "Channels: " << channels << std::endl;
  std::cout << "Encoding: " << encoding << std::endl;

  // 清理
  mpg123_close(mh);
  mpg123_delete(mh);
  mpg123_exit();

  return 0;
}

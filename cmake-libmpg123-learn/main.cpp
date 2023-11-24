#include <mpg123.h>
#include <vector>
#include <iostream>

int main() {
  const char *file_path = "../samples/Apollo13-wehaveaproblem.ogg.mp3";

  mpg123_handle *mh;
  unsigned char *buffer;
  size_t buffer_size;
  size_t done;

  // 初始化库
  mpg123_init();
  mh = mpg123_new(NULL, NULL);
  if (mh == NULL) {
    std::cerr << "Error initializing mpg123 handle" << std::endl;
    return 1;
  }

  // 打开MP3文件
  if (mpg123_open(mh, file_path) != MPG123_OK) {
    std::cerr << "Error opening MP3 file: " << mpg123_strerror(mh) << std::endl;
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

  // 清除所有格式设置并设置解码格式为32位浮点
  mpg123_format_none(mh);
  if (mpg123_format(mh, rate, channels, encoding) != MPG123_OK) {
    std::cerr << "Error setting format: " << mpg123_strerror(mh) << std::endl;
    return 1;
  }

  // 获取缓冲区大小
  buffer_size = mpg123_outblock(mh);
  buffer = new unsigned char[buffer_size];

  std::vector<float> pcmf32;

  // 解码循环
  int err = mpg123_read(mh, buffer, buffer_size, &done);
  while (err == MPG123_OK) {
    // 转换并存储到pcmf32中
    float *float_buffer = reinterpret_cast<float *>(buffer);
    size_t num_floats = done / sizeof(float);
    pcmf32.insert(pcmf32.end(), float_buffer, float_buffer + num_floats);
    err = mpg123_read(mh, buffer, buffer_size, &done);
  }

  if (err != MPG123_DONE && err != MPG123_OK) {
    std::cerr << "Decoding error: " << err << ":" << mpg123_strerror(mh) << std::endl;
  }

  // 清理
  delete[] buffer;
  mpg123_close(mh);
  mpg123_delete(mh);
  mpg123_exit();

  // 打印pcm数据的一部分或执行其他操作
  for (size_t i = 0; i < 10 && i < pcmf32.size(); ++i) {
    std::cout << pcmf32[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}

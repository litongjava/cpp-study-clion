#include <iostream>
#include <fstream>
#include <vector>
#include <speex/speex_preprocess.h>

int main(int argc, char **arvc) {
  const char *filename = "../pcm/16k_1.pcm";
  std::ifstream file(filename, std::ios::binary);

  if (!file) {
    std::cerr << "无法打开文件: " << filename << std::endl;
    return 1;
  }

  // 获取文件大小
  file.seekg(0, std::ios::end);
  size_t fileSize = file.tellg();
  file.seekg(0, std::ios::beg);

  // 计算有多少个int16_t样本
  size_t numSamples = fileSize / sizeof(int16_t);

  // 读取文件内容到vector
  std::vector<int16_t> pcm16(numSamples);
  file.read(reinterpret_cast<char *>(pcm16.data()), fileSize);

  if (!file) {
    printf("读取文件时出错\n");
    return 2;
  }

  file.close();

  std::cout << "文件读取完毕，样本数: " << pcm16.size() << std::endl;


}

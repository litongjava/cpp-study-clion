#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <memory>

extern "C" {
#include "simplevad/simple_vad.h"
#include "simplevad/period_format.h"
}

int add_period_activity(struct periods *per, int is_active, int is_last);

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
    std::cerr << "读取文件时出错" << std::endl;
    return 2;
  }

  file.close();

  std::cout << "文件读取完毕，样本数: " << pcm16.size() << std::endl;

  //读取30毫秒的样本
  const size_t tempSize = 16 * 3 * 10; // 假设16kHz，30ms约等于16*30=480个样本
  int16_t temp[tempSize];
  size_t pcmIndex = 0;

  std::unique_ptr<simple_vad, decltype(&simple_vad_free)> vad(simple_vad_create(), &simple_vad_free);
  if (!vad) {
    return 4;
  }

  struct periods *per = periods_create();

  int res = 0;
  while (res == 0) {
    size_t count = 0;

    int is_last = false;
    while (count < tempSize) {
      if (pcmIndex >= pcm16.size()) {
        std::cout << "到达文件末尾" << std::endl;
        is_last = true;
        res = 1;
        break;
      }

      temp[count++] = pcm16[pcmIndex++];
    }
    int is_active = process_vad(vad.get(), temp);
    add_period_activity(per, is_active, is_last);
    printf("pcmIndex %d,is_active %d,is_last %d\n", pcmIndex, is_active, is_last);
  }

  periods_free(per);
  return 0;
}

int add_period_activity(struct periods *per, int is_active, int is_last) {
  static int old_is_active = 0;
  static int count = 0;
  int res_add = period_add_vad_activity(per, is_active, is_last);
  if (res_add != 0) {
    return res_add;
  }
  if (is_active != old_is_active) {
    old_is_active = is_active;
  }
  count += 1;
  if (is_last) {
    //periods_print(per);
    std::cout << "total frames " << count << "\n";
  }
  return 0;
}

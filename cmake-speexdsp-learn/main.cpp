#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "speex/speex_preprocess.h"


int main(int argc, char **argv) {
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
  std::vector<int16_t> pcm16(numSamples); // 音频数据
  file.read(reinterpret_cast<char *>(pcm16.data()), fileSize);

  if (!file) {
    printf("读取文件时出错\n");
    return 2;
  }

  file.close();

  std::cout << "文件读取完毕，样本数: " << pcm16.size() << std::endl;

  int sample_rate = 16000; // 例如，16 kHz
  int chunk_size = (sample_rate / 1000) * 30; // 30 毫秒的帧大小
  //init vad
  SpeexPreprocessState *st = speex_preprocess_state_init(160, sample_rate);
  int vad = 1;
  speex_preprocess_ctl(st, SPEEX_PREPROCESS_SET_VAD, &vad);
//
  // 处理音频帧
  for (size_t i = 0; i < pcm16.size(); i += chunk_size) {
    spx_int16_t frame[chunk_size];
    for (int j = 0; j < chunk_size; ++j) {
      if (i + j < pcm16.size()) {
        frame[j] = (spx_int16_t) (pcm16[i + j]);
      } else {
        frame[j] = 0; // 对于超出范围的部分填充 0
      }
    }
    int is_speech = speex_preprocess_run(st, frame);
    printf("is_speech: %d \n", is_speech);
  }

  //destroy
  speex_preprocess_state_destroy(st);
  printf("end\n");
}

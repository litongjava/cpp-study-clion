#include <iostream>
#include <vector>
#include <string>

#define DR_WAV_IMPLEMENTATION

#include "dr_wav.h"

// 一个简单的函数，用于从 WAV 文件中读取音频数据
bool readWavFile(const std::string &filename, std::vector<float> &outAudioData) {
  unsigned int channels;
  unsigned int sampleRate;
  drwav_uint64 totalSampleCount;

  float *pSampleData = drwav_open_file_and_read_pcm_frames_f32(filename.c_str(), &channels, &sampleRate,
                                                               &totalSampleCount, NULL);
  if (pSampleData == NULL) {
    std::cerr << "Failed to open/read WAV file." << std::endl;
    return false;
  }

  // 将音频数据复制到 std::vector 中
  outAudioData.assign(pSampleData, pSampleData + totalSampleCount * channels);

  // 释放 drwav 分配的内存
  drwav_free(pSampleData, NULL);

  return true;
}

int main() {
  std::string wavFilePath = "jfk.wav";  // 替换为您的 WAV 文件路径
  std::vector<float> audioData;

  if (readWavFile(wavFilePath, audioData)) {
    std::cout << "Successfully read WAV file. Total samples: " << audioData.size() << std::endl;
  } else {
    std::cerr << "Failed to read WAV file." << std::endl;
  }

  return 0;
}
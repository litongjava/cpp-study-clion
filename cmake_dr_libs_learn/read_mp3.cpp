#include <iostream>
#include <vector>
#include <cstdint>

#define DR_MP3_IMPLEMENTATION

#include "dr_libs/dr_mp3.h"

#define COMMON_SAMPLE_RATE 16000

bool read_mp3(const std::string &fname, std::vector<float> &pcmf32, bool stereo) {
  drmp3 mp3;
  if (!drmp3_init_file(&mp3, fname.c_str(), nullptr)) {
    fprintf(stderr, "error: failed to open '%s' as MP3 file\n", fname.c_str());
    return false;
  }

  if (mp3.sampleRate != COMMON_SAMPLE_RATE) {
    fprintf(stderr, "%s: MP3 file '%s' must be %i kHz\n", __func__, fname.c_str(), COMMON_SAMPLE_RATE / 1000);
    return false;
  }

  if (mp3.channels != 1 && mp3.channels != 2) {
    fprintf(stderr, "%s: MP3 file '%s' must be mono or stereo\n", __func__, fname.c_str());
    return false;
  }

  if (stereo && mp3.channels != 2) {
    fprintf(stderr, "%s: MP3 file '%s' must be stereo for this operation\n", __func__, fname.c_str());
    return false;
  }

  drmp3_uint64 frameCount;
  float *pSampleData = drmp3__full_read_and_close_f32(&mp3, nullptr, &frameCount);

  pcmf32.assign(pSampleData, pSampleData + frameCount * mp3.channels);
  drmp3_free(pSampleData, nullptr);

  return true;
}

int main() {
  std::cout << "Hello, World!" << std::endl;
  std::string mp3_file_path = "../samples/jfk.mp3"; // 替换为您的 MP3 文件路径
  std::vector<float> pcmf32; // mono-channel F32 PCM

  if (!read_mp3(mp3_file_path, pcmf32, false)) {
    std::cerr << "Failed to read MP3 file" << std::endl;
    return -1;
  }

  printf("size of samples: %zu\n", pcmf32.size());
  return 0;
}

//
// Created by Tong Li on 11/17/2023.
//
#pragma once

#ifndef CMAKE_WHISER_CPP_DEMO_COMMON_H
#define CMAKE_WHISER_CPP_DEMO_COMMON_H
#define COMMON_SAMPLE_RATE 16000

#include <string>
#include <vector>



//
// Audio utils
//
// Read WAV audio file and store the PCM data into pcmf32
// The sample rate of the audio must be equal to COMMON_SAMPLE_RATE
// If stereo flag is set and the audio has 2 channels, the pcmf32s will contain 2 channel PCM
bool read_wav(
  const std::string &fname,
  std::vector<float> &pcmf32,
  std::vector<std::vector<float>> &pcmf32s,
  bool stereo);

#endif //CMAKE_WHISER_CPP_DEMO_COMMON_H

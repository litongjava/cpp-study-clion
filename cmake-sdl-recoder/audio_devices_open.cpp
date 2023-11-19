//
// Created by Administrator on 11/17/2023.
//
#include <SDL.h>
#include <SDL_audio.h>

bool initAudio(int capture_id, int sample_rate);

int main(int argc, char **argv) {
  SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetHintWithPriority(SDL_HINT_AUDIO_RESAMPLING_MODE, "medium", SDL_HINT_OVERRIDE);

  {
    int nDevices = SDL_GetNumAudioDevices(SDL_TRUE);
    fprintf(stderr, "%s: found %d capture devices:\n", __func__, nDevices);
    for (int i = 0; i < nDevices; i++) {
      fprintf(stderr, "%s:    - Capture device #%d: '%s'\n", __func__, i, SDL_GetAudioDeviceName(i, SDL_TRUE));
    }

    for (int i = 0; i < nDevices; i++) {
      initAudio(i, 16000);
    }

  }
}

bool initAudio(int capture_id, int sample_rate) {


  SDL_AudioSpec capture_spec_requested;
  SDL_AudioSpec capture_spec_obtained;

  SDL_zero(capture_spec_requested);
  SDL_zero(capture_spec_obtained);

  capture_spec_requested.freq = sample_rate;
  capture_spec_requested.format = AUDIO_F32;
  capture_spec_requested.channels = 1;
  capture_spec_requested.samples = 1024;

  SDL_AudioDeviceID m_dev_id_in;
  if (capture_id >= 0) {
    fprintf(stderr, "%s: attempt to open capture device %d : '%s' ...\n", __func__, capture_id,
            SDL_GetAudioDeviceName(capture_id, SDL_TRUE));
    m_dev_id_in = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(capture_id, SDL_TRUE), SDL_TRUE,
                                      &capture_spec_requested, &capture_spec_obtained, 0);
  } else {
    fprintf(stderr, "%s: attempt to open default capture device ...\n", __func__);
    m_dev_id_in = SDL_OpenAudioDevice(nullptr, SDL_TRUE, &capture_spec_requested, &capture_spec_obtained, 0);
  }

  if (!m_dev_id_in) {
    fprintf(stderr, "%s: couldn't open an audio device for capture: %s!\n", __func__, SDL_GetError());
    m_dev_id_in = 0;

    return false;
  } else {;
    const char *deviceName = SDL_GetAudioDeviceName(capture_id, SDL_TRUE);
    fprintf(stderr, "%s: opened device name:'%s'\n", __func__, deviceName);
    fprintf(stderr, "%s: obtained spec for input device (SDL Id = %d):\n", __func__, m_dev_id_in);
    fprintf(stderr, "%s:     - sample rate:       %d\n", __func__, capture_spec_obtained.freq);
    fprintf(stderr, "%s:     - format:            %d (required: %d)\n", __func__, capture_spec_obtained.format,
            capture_spec_requested.format);
    fprintf(stderr, "%s:     - channels:          %d (required: %d)\n", __func__, capture_spec_obtained.channels,
            capture_spec_requested.channels);
    fprintf(stderr, "%s:     - samples per frame: %d\n", __func__, capture_spec_obtained.samples);
  }
  return true;
}

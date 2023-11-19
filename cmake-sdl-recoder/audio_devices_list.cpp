//
// Created by Administrator on 11/17/2023.
//

#include <SDL.h>
#include <SDL_audio.h>

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
  }
}
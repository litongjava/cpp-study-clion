extern "C" {
#include <libavformat/avformat.h>
}

#include <iostream>

int main(int argc, char **argv) {

  const char *version = av_version_info();
  std::cout << "FFmpeg version: " << version << std::endl;
  return 0;
}

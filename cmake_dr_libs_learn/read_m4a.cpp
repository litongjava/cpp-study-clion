extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
}

#define COMMON_SAMPLE_RATE 16000

#include <samplerate.h>
#include <vector>
#include <string>

bool resample(const float *input, size_t inputSampleRate, size_t inputSize,
              std::vector<float> &output, size_t outputSampleRate) {
  // Initialize Converter
  int error;
  SRC_STATE *src_state = src_new(SRC_SINC_FASTEST, 1, &error);
  if (src_state == NULL) {
    fprintf(stderr,"error %s\n",src_strerror(error));
    return false;
  }

  // set convert param
  SRC_DATA src_data;
  src_data.data_in = input;
  src_data.input_frames = inputSize;
  src_data.data_out = new float[inputSize]; // assign size
  src_data.output_frames = inputSize;
  src_data.src_ratio = double(outputSampleRate) / inputSampleRate;

  // convert
  error = src_process(src_state, &src_data);
  if (error) {
    fprintf(stderr,"Error converting sample rate: %s\n",src_strerror(error));
    delete[] src_data.data_out;
    src_delete(src_state);
    return false;
  }

  // Copy the transformed data into the output vector
  output.assign(src_data.data_out, src_data.data_out + src_data.output_frames_gen);

  // clean
  delete[] src_data.data_out;
  src_delete(src_state);

  return true;
}

bool read_m4a(const std::string &fname, std::vector<float> &pcmf32, bool stereo) {
  avformat_network_init();

  AVFormatContext* formatContext = avformat_alloc_context();
  if (avformat_open_input(&formatContext, fname.c_str(), nullptr, nullptr) != 0) {
    fprintf(stderr, "Could not open file %s\n", fname.c_str());
    return false;
  }

  if (avformat_find_stream_info(formatContext, nullptr) < 0) {
    fprintf(stderr, "Could not find stream information\n");
    avformat_close_input(&formatContext);
    return false;
  }

  const AVCodec* codec = nullptr;
  int streamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, -1, -1, &codec, 0);
  if (streamIndex < 0) {
    fprintf(stderr, "Could not find any audio stream in the file\n");
    avformat_close_input(&formatContext);
    return false;
  }

  AVCodecContext* codecContext = avcodec_alloc_context3(codec);
  avcodec_parameters_to_context(codecContext, formatContext->streams[streamIndex]->codecpar);

  if (avcodec_open2(codecContext, codec, nullptr) < 0) {
    fprintf(stderr, "Could not open codec\n");
    avcodec_free_context(&codecContext);
    avformat_close_input(&formatContext);
    return false;
  }

  SwrContext* swrCtx = swr_alloc_set_opts(nullptr,
                                          stereo ? AV_CH_LAYOUT_STEREO : AV_CH_LAYOUT_MONO,
                                          AV_SAMPLE_FMT_FLT,
                                          COMMON_SAMPLE_RATE,
                                          codecContext->channel_layout,
                                          codecContext->sample_fmt,
                                          codecContext->sample_rate,
                                          0, nullptr);
  if (!swrCtx || swr_init(swrCtx) < 0) {
    fprintf(stderr, "Could not initialize the resampling context\n");
    swr_free(&swrCtx);
    avcodec_free_context(&codecContext);
    avformat_close_input(&formatContext);
    return false;
  }

  AVPacket packet;
  av_init_packet(&packet);
  packet.data = nullptr;
  packet.size = 0;

  AVFrame* frame = av_frame_alloc();

  while (av_read_frame(formatContext, &packet) >= 0) {
    if (packet.stream_index == streamIndex) {
      int ret = avcodec_send_packet(codecContext, &packet);
      if (ret < 0) {
        fprintf(stderr, "Error sending packet for decoding\n");
        break;
      }

      while (ret >= 0) {
        ret = avcodec_receive_frame(codecContext, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
          break;
        } else if (ret < 0) {
          fprintf(stderr, "Error during decoding\n");
          break;
        }

        // Resample frames and convert them to float PCM format
        // ...

        av_frame_unref(frame);
      }
    }
    av_packet_unref(&packet);
  }

  // Clean up
  av_frame_free(&frame);
  swr_free(&swrCtx);
  avcodec_free_context(&codecContext);
  avformat_close_input(&formatContext);
  avformat_network_deinit();

  return true;
}

int main(int argc, char** argv){
  printf("hello world");
  return 0;
}

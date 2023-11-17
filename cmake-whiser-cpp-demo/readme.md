### linux
```shell
git clone git@github.com:ggerganov/whisper.cpp.git
cmake -B build
cmake --build cmake-build-release --target install -- -j 12
```
cmake-3.23.4-linux-x86_64

```shell
./demo01 -m ../../../../project-ping/whisper.cpp/models/ggml-base.en.bin ../../../../project-ping/whisper.cpp/samples/jfk.wav
whisper_init_from_file_with_params_no_state: loading model from '../../../../project-ping/whisper.cpp/models/ggml-base.en.bin'
whisper_model_load: loading model
whisper_model_load: n_vocab       = 51864
whisper_model_load: n_audio_ctx   = 1500
whisper_model_load: n_audio_state = 512
whisper_model_load: n_audio_head  = 8
whisper_model_load: n_audio_layer = 6
whisper_model_load: n_text_ctx    = 448
whisper_model_load: n_text_state  = 512
whisper_model_load: n_text_head   = 8
whisper_model_load: n_text_layer  = 6
whisper_model_load: n_mels        = 80
whisper_model_load: ftype         = 1
whisper_model_load: qntvr         = 0
whisper_model_load: type          = 2 (base)
whisper_model_load: adding 1607 extra tokens
whisper_model_load: n_langs       = 99
whisper_model_load:      CPU buffer size =   156.67 MB
whisper_model_load: model size    =  156.58 MB
whisper_init_state: kv self size  =   16.52 MB
whisper_init_state: kv cross size =   18.43 MB
whisper_init_state: compute buffer (conv)   =   14.79 MB
whisper_init_state: compute buffer (encode) =   85.93 MB
whisper_init_state: compute buffer (cross)  =    4.71 MB
whisper_init_state: compute buffer (decode) =   96.41 MB

system_info: n_threads = 4 / 16 | AVX = 1 | AVX2 = 1 | AVX512 = 0 | FMA = 1 | NEON = 0 | ARM_FMA = 0 | METAL = 0 | F16C = 1 | FP16_VA = 0 | WASM_SIMD = 0 | BLAS = 0 | SSE3 = 1 | SSSE3 = 1 | VSX = 0 | CUDA = 0 | COREML = 0 | OPENVINO = 0 |

main: processing '../../../../project-ping/whisper.cpp/samples/jfk.wav' (176000 samples, 11.0 sec), 4 threads, 1 processors, lang = en, task = transcribe, timestamps = 1 ...


[00:00:00.000 --> 00:00:11.000]   And so my fellow Americans, ask not what your country can do for you, ask what you can do for your country.

whisper_print_timings:     load time =   623.23 ms
whisper_print_timings:     fallbacks =   0 p /   0 h
whisper_print_timings:      mel time =    13.21 ms
whisper_print_timings:   sample time =    12.19 ms /     1 runs (   12.19 ms per run)
whisper_print_timings:   encode time =  1532.25 ms /     1 runs ( 1532.25 ms per run)
whisper_print_timings:   decode time =   114.96 ms /    27 runs (    4.26 ms per run)
whisper_print_timings:   batchd time =     0.00 ms /     1 runs (    0.00 ms per run)
whisper_print_timings:   prompt time =     0.00 ms /     1 runs (    0.00 ms per run)
whisper_print_timings:    total time =  2305.99 ms
```
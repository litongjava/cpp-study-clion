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

```
(base) ping@PingdeMacBook-Pro cmake-whiser-cpp-demo % cp ../../../project-litongjava/whisper.cpp/ggml-metal.metal .
(base) ping@PingdeMacBook-Pro cmake-whiser-cpp-demo % ./cmake-build-debug/demo01 -m ../../../project-litongjava/whisper.cpp/models/ggml-base.en.bin ../../../project-litongjava/whisper.cpp/samples/jfk.wav
whisper_init_from_file_with_params_no_state: loading model from '../../../project-litongjava/whisper.cpp/models/ggml-base.en.bin'
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
whisper_backend_init: using Metal backend
ggml_metal_init: allocating
ggml_metal_init: found device: Apple M2
ggml_metal_init: picking default device: Apple M2
ggml_metal_init: default.metallib not found, loading from source
ggml_metal_init: error: could not use bundle path to find ggml-metal.metal, falling back to trying cwd
ggml_metal_init: loading 'ggml-metal.metal'
ggml_metal_init: GPU name:   Apple M2
ggml_metal_init: GPU family: MTLGPUFamilyApple8 (1008)
ggml_metal_init: hasUnifiedMemory              = true
ggml_metal_init: recommendedMaxWorkingSetSize  = 11453.25 MB
ggml_metal_init: maxTransferRate               = built-in GPU
ggml_metal_add_buffer: allocated 'backend         ' buffer, size =   156.68 MB, (  157.20 / 11453.25)
whisper_model_load:    Metal buffer size =   156.67 MB
whisper_model_load: model size    =  156.58 MB
whisper_backend_init: using Metal backend
ggml_metal_init: allocating
ggml_metal_init: found device: Apple M2
ggml_metal_init: picking default device: Apple M2
ggml_metal_init: default.metallib not found, loading from source
ggml_metal_init: error: could not use bundle path to find ggml-metal.metal, falling back to trying cwd
ggml_metal_init: loading 'ggml-metal.metal'
ggml_metal_init: GPU name:   Apple M2
ggml_metal_init: GPU family: MTLGPUFamilyApple8 (1008)
ggml_metal_init: hasUnifiedMemory              = true
ggml_metal_init: recommendedMaxWorkingSetSize  = 11453.25 MB
ggml_metal_init: maxTransferRate               = built-in GPU
ggml_metal_add_buffer: allocated 'backend         ' buffer, size =    16.52 MB, (  173.72 / 11453.25)
whisper_init_state: kv self size  =   16.52 MB
ggml_metal_add_buffer: allocated 'backend         ' buffer, size =    18.43 MB, (  192.15 / 11453.25)
whisper_init_state: kv cross size =   18.43 MB
whisper_init_state: loading Core ML model from '../../../project-litongjava/whisper.cpp/models/ggml-base.en-encoder.mlmodelc'
whisper_init_state: first run on a device may take a while ...
whisper_init_state: Core ML model loaded
ggml_metal_add_buffer: allocated 'backend         ' buffer, size =     0.02 MB, (  196.51 / 11453.25)
whisper_init_state: compute buffer (conv)   =    5.67 MB
ggml_metal_add_buffer: allocated 'backend         ' buffer, size =     0.02 MB, (  196.53 / 11453.25)
whisper_init_state: compute buffer (cross)  =    4.71 MB
ggml_metal_add_buffer: allocated 'backend         ' buffer, size =     0.02 MB, (  196.54 / 11453.25)
whisper_init_state: compute buffer (decode) =   96.41 MB
ggml_metal_add_buffer: allocated 'backend         ' buffer, size =     4.05 MB, (  200.59 / 11453.25)
ggml_metal_add_buffer: allocated 'backend         ' buffer, size =     3.08 MB, (  203.67 / 11453.25)
ggml_metal_add_buffer: allocated 'backend         ' buffer, size =    94.78 MB, (  298.45 / 11453.25)

system_info: n_threads = 4 / 8 | AVX = 0 | AVX2 = 0 | AVX512 = 0 | FMA = 0 | NEON = 1 | ARM_FMA = 1 | METAL = 1 | F16C = 0 | FP16_VA = 1 | WASM_SIMD = 0 | BLAS = 1 | SSE3 = 0 | SSSE3 = 0 | VSX = 0 | CUDA = 0 | COREML = 1 | OPENVINO = 0 | 

main: processing '../../../project-litongjava/whisper.cpp/samples/jfk.wav' (176000 samples, 11.0 sec), 4 threads, 1 processors, lang = en, task = transcribe, timestamps = 1 ...


[00:00:00.000 --> 00:00:11.000]   And so my fellow Americans, ask not what your country can do for you, ask what you can do for your country.

whisper_print_timings:     load time =   433.60 ms
whisper_print_timings:     fallbacks =   0 p /   0 h
whisper_print_timings:      mel time =     5.40 ms
whisper_print_timings:   sample time =    11.73 ms /     1 runs (   11.73 ms per run)
whisper_print_timings:   encode time =   209.48 ms /     1 runs (  209.48 ms per run)
whisper_print_timings:   decode time =    86.51 ms /    27 runs (    3.20 ms per run)
whisper_print_timings:   batchd time =     0.00 ms /     1 runs (    0.00 ms per run)
whisper_print_timings:   prompt time =     0.00 ms /     1 runs (    0.00 ms per run)
whisper_print_timings:    total time =   911.62 ms
ggml_metal_free: deallocating
ggml_metal_free: deallocating

```
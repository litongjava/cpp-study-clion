cmake_minimum_required(VERSION 3.26)
project(cmake_dir_libs_dir_wav_learn)

set(CMAKE_CXX_STANDARD 17)

find_package(SampleRate CONFIG REQUIRED)
find_package(FFMPEG REQUIRED)


add_executable(main main.cpp)

add_executable(hello_world hello_world.cpp)
add_executable(demo01 demo01.cpp)
add_executable(read_mp3 read_mp3.cpp)
target_link_libraries(read_mp3 PRIVATE SampleRate::samplerate)

add_executable(ffmpeg_version ffmpeg_version.cpp)
target_include_directories(ffmpeg_version PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(ffmpeg_version PRIVATE ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(ffmpeg_version PRIVATE ${FFMPEG_LIBRARIES})

add_executable(read_m4a read_m4a.cpp)
target_include_directories(read_m4a PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(read_m4a PRIVATE ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(read_m4a PRIVATE ${FFMPEG_LIBRARIES} SampleRate::samplerate)

cmake_minimum_required(VERSION 3.27)
project(BlockyEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/libs)

#SDL
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/libs/SDL2")
include_directories("${SDL2_PATH}/include/SDL2")

#SDL Image
set(SDL_IMAGE_PATH "${CMAKE_SOURCE_DIR}/libs/SDL2_image")
include_directories("${SDL_IMAGE_PATH}/include/SDL2")

#SDL Mixer
set(SDL_MIXER_PATH "${CMAKE_SOURCE_DIR}/libs/SDL2_mixer")
include_directories("${SDL_MIXER_PATH}/include/SDL2")

#Final
add_executable(${PROJECT_NAME} main.cpp
        playAudioWavFile.cpp
        playAudioWavFile.hpp)
target_link_libraries(${PROJECT_NAME}
        mingw32

        "${SDL2_PATH}/lib/libSDL2main.a"
        "${SDL2_PATH}/lib/libSDL2.dll.a"

        "${SDL_IMAGE_PATH}/lib/libSDL2_image.dll.a"
        "${SDL_MIXER_PATH}/lib/libSDL2_mixer.dll.a"
)

cmake_minimum_required(VERSION 3.27)
project(BlockyEngine)

#set(CMAKE_CXX_STANDARD 17)

# Build shared objects, standard will be for Windows
if (${LINUX})
endif ()

set(blocky_build_tests ON CACHE BOOL "")

#region Dynamic Fetching

#SDL GFX
# TODO GFX is a mess to build, either externalproject or make a fork of it to build with CMakeLists.txt
#build_lib(
#        sdl_gfx
#        "http://www.ferzkopp.net/Software/SDL2_gfx/SDL2_gfx-1.0.4.tar.gz"
#        TRUE
#)

#endregion //Dynamic Fetching

#STB_Image TODO Make this a precompiled header :)
include_directories("${CMAKE_SOURCE_DIR}/libs/stb_image")

add_subdirectory(engine)

#Final
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} BlockyEngineInternal)
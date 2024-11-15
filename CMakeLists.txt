cmake_minimum_required(VERSION 3.27)
project(BlockyEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/libs)

#SDL
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/libs/SDL2")
include_directories("${SDL2_PATH}/include/SDL2")

#STB_Image
include_directories("${CMAKE_SOURCE_DIR}/libs/stb_image")

#GLM
include_directories("${CMAKE_MODULE_PATH}")

#Final
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(engine)
add_subdirectory(libs/SDL2_gfx)



target_link_libraries(${PROJECT_NAME}
        mingw32
        sdl_gfx

)

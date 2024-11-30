cmake_minimum_required(VERSION 3.27)
project(BlockyEngine)

set(blocky_build_tests ON CACHE BOOL "")
add_subdirectory(engine)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} BlockyEngineInternal)
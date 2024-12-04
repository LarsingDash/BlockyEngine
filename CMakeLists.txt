cmake_minimum_required(VERSION 3.27)
project(BlockyEngine)

add_subdirectory(engine)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Blocky::Engine)
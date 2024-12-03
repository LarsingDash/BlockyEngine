cmake_minimum_required(VERSION 3.27)
project(BlockyEngine)

set(blocky_build_tests ON CACHE BOOL "")
add_subdirectory(engine)

add_executable(${PROJECT_NAME} main.cpp)


#Box2d
find_package(box2d CONFIG REQUIRED) #todo: use same include strategy as other libs
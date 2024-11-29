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
add_executable(${PROJECT_NAME} main.cpp
        engine/components/physics/rigidBody/BoxRigidBody.cpp
        engine/components/physics/rigidBody/BoxRigidBody.hpp
        engine/components/physics/rigidBody/CircleRigidBody.cpp
        engine/components/physics/rigidBody/CircleRigidBody.hpp)

add_subdirectory(engine)
add_subdirectory(libs/SDL2_gfx)

#todo: vcpkg: stb used by renderer
find_package(Stb REQUIRED)
include_directories("${Stb_INCLUDE_DIR}")

#Box2d
find_package(box2d CONFIG REQUIRED) #todo: use same include strategy as other libs

target_link_libraries(${PROJECT_NAME}
        mingw32
        sdl_gfx
        box2d::box2d
)

find_package(Stb REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
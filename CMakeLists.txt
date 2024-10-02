cmake_minimum_required(VERSION 3.27)
project(BlockyEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/libs)

#SDL
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/libs/SDL2")
include_directories("${SDL2_PATH}/include/SDL2")

#STB_Image
include_directories("${CMAKE_SOURCE_DIR}/libs/stb_image")

#Final
add_executable(${PROJECT_NAME}
        main.cpp
        Engine/WindowModule.cpp
        Engine/InputModule.cpp
        Engine/BlockyEngine.cpp
        Engine/Renderer/SoftwareRenderer.cpp
        Engine/Renderer/HardwareRenderer.cpp
        Engine/Renderable/Rectangle.cpp
        Engine/Renderable/Circle.cpp
        Engine/Renderable/RenderManager.cpp
        Engine/Renderer/BaseRenderer.h
)

target_link_libraries(${PROJECT_NAME}
        mingw32

        "${SDL2_PATH}/lib/libSDL2main.a"
        "${SDL2_PATH}/lib/libSDL2.dll.a"
)

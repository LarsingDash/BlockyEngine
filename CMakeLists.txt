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
include_directories("${CMAKE_SOURCE_DIR}/libs/glm")

#Final
add_executable(${PROJECT_NAME} main.cpp
        GameObject/GameObject.cpp
        GameObject/GameObject.h
        GameObject/Transform.cpp
        GameObject/Transform.h
        Component/Component.h
        GameObject/GameObjectManager.cpp
        GameObject/GameObjectManager.h
)

target_link_libraries(${PROJECT_NAME}
        mingw32

        "${SDL2_PATH}/lib/libSDL2main.a"
        "${SDL2_PATH}/lib/libSDL2.dll.a"
)

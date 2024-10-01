cmake_minimum_required(VERSION 3.27)
project(BlockyEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/libs)

#SDL
set(SDL2_PATH "${CMAKE_MODULE_PATH}/SDL2")
include_directories("${SDL2_PATH}/include/SDL2")

#STB_Image
include_directories("${CMAKE_MODULE_PATH}/stb_image")

#GLM
include_directories("${CMAKE_MODULE_PATH}/glm")

#Final
add_executable(${PROJECT_NAME}
        main.cpp
        renderer.cpp
        GameObject/GameObjectManager.cpp
        GameObject/GameObject.cpp
        GameObject/Transform.cpp
        Component/ExampleComponent.cpp
        Component/OtherComponent.cpp
        Component/TransExampleComponent.cpp
        Component/TransOtherComponent.cpp
)

target_link_libraries(${PROJECT_NAME}
        mingw32

        "${SDL2_PATH}/lib/libSDL2main.a"
        "${SDL2_PATH}/lib/libSDL2.dll.a"
)

cmake_minimum_required(VERSION 3.27)
project(BlockyEngine)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(LIBS_DIR "${PROJECT_SOURCE_DIR}/libs")

# Libraries
set(LIBRARIES
        "GTest;"
        "SDL2;"
)

#option(ENABLE_TESTING "Enables google test" ON)
set(ENABLE_TESTING TRUE)

#CMake Modules
include(FetchContent)
include(fetch_lib)

# Build shared objects, standard will be for Windows
if (${LINUX})
endif ()

#region Dynamic Fetching

#SDL2
build_lib(
        SDL2_t
        "https://github.com/libsdl-org/SDL/releases/download/release-2.30.9/SDL2-devel-2.30.9-mingw.zip"
        TRUE
)
set(SDL2_DIR "${LIBS_DIR}/SDL2_t/cmake")
message("SDL DIR: ${SDL2_DIR}")
find_package(SDL2 CONFIG REQUIRED)

if (${ENABLE_TESTING})
    #    find_package(GTest CONFIG QUIET)
    #    if (NOT GTest_POPULATED)
    #        message(STATUS GTest)
    #        FetchContent_Declare(
    #                googletest
    #                URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
    #        )
    #
    #        FetchContent_MakeAvailable(
    #                googletest
    #        )
    #    endif ()
    build_lib(
            googletest
            "https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip"
            TRUE
    )
    set(GTest_DIR "${LIBS_DIR}/googletest")
    add_subdirectory(${GTest_DIR})

    if (${WIN32})
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif ()
endif ()

#GLM
build_lib(
        glm
        "https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip"
        TRUE
)

#endregion //Dynamic Fetching

#SDL
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/libs/SDL2")
include_directories("${SDL2_PATH}/include/SDL2")

#STB_Image TODO Make this a precompiled header :)
include_directories("${CMAKE_SOURCE_DIR}/libs/stb_image")

#GLM
include_directories("${CMAKE_MODULE_PATH}")

#Final
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(engine)
add_subdirectory(libs/SDL2_gfx)

target_link_libraries(${PROJECT_NAME}
        sdl_gfx
)

#Google Test
# TODO Ctest integration
if (${ENABLE_TESTING})
    message(STATUS "Linking Googletest")
    add_executable(GoogleTest engine/testMain.cpp engine/testing/TestLogger.hpp)
    target_link_libraries(${PROJECT_NAME} gtest gtest_main)
    include(GoogleTest)
endif ()
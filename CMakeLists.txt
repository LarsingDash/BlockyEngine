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

message("SDL2 INCLUDE DIRS: ${SDL2_INCLUDE_DIRS}")
message("SDL2 LIBRARY DIRS: ${SDL2_LIBRARIES}")

#GoogleTest
if (${ENABLE_TESTING})
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

#Final
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(engine)
add_subdirectory(libs/SDL2_gfx)
add_subdirectory(libs/glm)

target_link_libraries(${PROJECT_NAME}
        glm
        SDL2::SDL2
        sdl_gfx
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${SDL_INCLUDE_DIRS}
)

if (EXISTS "${LIBS_DIR}/glm")
    message("GLM DOES EXIST")
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE
        "${LIBS_DIR}"
)

# Meant to copy the dll to the build-debug,
# however it cant find the sdl dll behind the bin directory...
#set_target_properties(${PROJECT_NAME} PROPERTIES
#        INSTALL_RPATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>/bin"
#        BUILD_WITH_INSTALL_RPATH TRUE
#)
#
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory
#        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/bin"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "${SDL2_DIR}/../x86_64-w64-mingw32/bin/SDL2.dll"
#        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/bin"
#        COMMENT "Copying SDL2.dll to build folder"
#)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_DIR}/../x86_64-w64-mingw32/bin/SDL2.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying SDL2.dll to build folder"
)

#Google Test
# TODO Ctest integration
if (${ENABLE_TESTING})
    message(STATUS "Linking Googletest")
    add_executable(Google_Test engine/testMain.cpp engine/testing/TestLogger.hpp
            engine/testing/BLogger_Fixture.cpp
            engine/testing/BLogger_Fixture.hpp)
    target_link_libraries(Google_Test gtest gtest_main gmock)
    include(GoogleTest)
endif ()
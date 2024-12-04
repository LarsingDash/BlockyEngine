# The engine name
set(ENGINE_TARGET "BlockyEngineInternal")
set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")

include(cmake/fetch_lib.cmake) #The cmake module used for fetching libraries from the internet

# Options that have to be set by the user, using our engine
option(blocky_build_as_shared "Builds the engine as a shared library" ON)
option(blocky_build_tests "Builds the testing folder along with the library" OFF)

#This just looks cool...
mark_as_advanced(
        blocky_build_as_shared
        blocky_build_tests
)

# Versioning for ease of use to minimally change the links
set(GTEST_VERSION "1.15.2")
set(SDL_VERSION "2.30.9")
set(GLM_VERSION "1.0.1")
set(BOX2D_VERSION "3.0.0")

# Sets the dependencies of the blocky engine, as in, which libraries to build and whatnot
set(BLOCKY_DEPS
        googletest https://github.com/google/googletest/releases/download/v${GTEST_VERSION}/googletest-${GTEST_VERSION}.tar.gz
        SDL2 https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VERSION}/SDL2-devel-${SDL_VERSION}-mingw.zip
        SDL2_gfx https://github.com/Dogukan-lab/sdl_gfx_offshoot/releases/download/v1.0.0/SDL_gfx.tar.gz
        glm https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
        box2d https://github.com/erincatto/box2d/archive/refs/tags/v${BOX2D_VERSION}.tar.gz
        stb_image https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_image.h
)

########################################################################################################################

# Get the range for to loop through BLOCKY_DEPS
list(LENGTH BLOCKY_DEPS DEPS_LENGTH)
math(EXPR LIST_RANGE "${DEPS_LENGTH}-1")
#message(STATUS "DEPS LENGTH ${LIST_RANGE}")

# This for loop goes through the Blocky_DEPS and uses the build_lib function from fetch_lib.cmake
# Syntax is (var RANGE begin end)
# Because of the Blocky_DEPS structure as a pair it will go through the loop mod 2, because it will always be NAME;URL
foreach (INDEX RANGE 0 ${LIST_RANGE})
    math(EXPR MOD_RESULT "${INDEX} % 2")
    if (${MOD_RESULT} EQUAL 0)
        list(GET BLOCKY_DEPS ${INDEX} LIB_NAME)
    else ()
        list(GET BLOCKY_DEPS ${INDEX} LIB_URL)
        message(STATUS "Library: ${LIB_NAME}, URL: ${LIB_URL}")
        if (${LIB_NAME} STREQUAL "stb_image")
            build_lib_from_file("${DEPS_DIR}/${LIB_NAME}"
                    "stb_image"
                    "h"
                    ${LIB_URL}
            )
        else ()
            build_lib(${DEPS_DIR}
                    ${LIB_NAME}
                    ${LIB_URL}
                    TRUE
            )
        endif ()
    endif ()
endforeach ()

########################################################################################################################

# IMPORTANT MINGW Toolchain dependent, should not be used for Linux as well!
set(SDL2_DIR "${DEPS_DIR}/SDL2/cmake")
message("SDL DIR: ${SDL2_DIR}")
find_package(SDL2 CONFIG REQUIRED)

message("SDL2 INCLUDE DIRS: ${SDL2_INCLUDE_DIRS}")
message("SDL2 LIBRARY DIRS: ${SDL2_LIBRARIES}")

add_subdirectory("${DEPS_DIR}/SDL2_gfx")
add_subdirectory("${DEPS_DIR}/glm")

find_package(box2d)

########################################################################################################################

if (blocky_build_tests)
    message(STATUS "Building the blocky engine tests")

    enable_testing()

    set(GTest_DIR "${DEPS_DIR}/googletest")
    add_subdirectory(${GTest_DIR})
    add_subdirectory(testing)
endif ()

# Set the target
if (block_build_as_shared)
    add_library(${ENGINE_TARGET} SHARED BlockyEngine.cpp)
else ()
    add_library(${ENGINE_TARGET} STATIC BlockyEngine.cpp)
endif ()

# Create said target with alias
add_library(Blocky::Engine ALIAS ${ENGINE_TARGET})

add_subdirectory(moduleManager)
add_subdirectory(sceneManager)
add_subdirectory(components)
add_subdirectory(gameObject)
add_subdirectory(logging)

target_link_libraries(${ENGINE_TARGET} PRIVATE
        glm
        SDL2::SDL2
        sdl_gfx
        box2d::box2d
)

target_include_directories(${ENGINE_TARGET} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${SDL2_INCLUDE_DIRS}
        ${DEPS_DIR}
)

# Temporarily just copy the SDL2 dll to the build folder
if (WIN32)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(SDL2_DLL "${SDL2_DIR}/../x86_64-w64-mingw32/bin/SDL2.dll")
    else ()
        set(SDL2_DLL "${SDL2_DIR}/../i686-w64-mingw32/bin/SDL2.dll")
    endif ()

    if (EXISTS ${SDL2_DLL})
        add_custom_command(TARGET ${ENGINE_TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL2_DLL}"
                "${CMAKE_BINARY_DIR}"
                COMMENT "Copying SDL2.dll to build folder"
        )
    endif ()
elseif (${UNIX})
    #Unix ver not supported yet
    message(FATAL_ERROR "UNIX SYSTEM ARE NOT YET SUPPORTED FOR DYNAMIC LIBRARY LINKAGE")
endif ()
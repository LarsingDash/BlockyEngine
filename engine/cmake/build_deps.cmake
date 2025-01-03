cmake_minimum_required(VERSION 3.22)

set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")
set(DEPS_DOWNLOADED FALSE CACHE BOOL INTERNAL "")

# Versioning for ease of use to minimally change the links
set(GTEST_VERSION "1.15.2")
set(SDL_VERSION "2.30.9")
set(SDLTTF_VERSION "2.22.0")
set(GLM_VERSION "1.0.1")
set(BOX2D_VERSION "2.4.1")
set(IMGUI_VERSION "1.91.5")
set(SDL_MIXER_VERSION "2.8.0")
set(JSON_VERSION "3.11.3")

set(BLOCKY_DEPS
        googletest https://github.com/google/googletest/releases/download/v${GTEST_VERSION}/googletest-${GTEST_VERSION}.tar.gz
        SDL2_gfx https://github.com/Dogukan-lab/sdl_gfx_offshoot/releases/download/v1.0.0/SDL_gfx.tar.gz
        SDL2_ttf https://github.com/libsdl-org/SDL_ttf/releases/download/release-${SDLTTF_VERSION}/SDL2_ttf-devel-${SDLTTF_VERSION}-mingw.tar.gz glm https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
        box2d https://github.com/erincatto/box2d/archive/refs/tags/v${BOX2D_VERSION}.tar.gz
        stb_image https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_image.h
        imgui https://github.com/ocornut/imgui/archive/refs/tags/v${IMGUI_VERSION}.tar.gz
        json https://github.com/nlohmann/json/releases/download/v${JSON_VERSION}/json.hpp
)

function(setup_platform_specifics)
    # Sets the dependencies, OS dependant of the blocky engine, as in, which libraries to build and whatnot
    if (${MINGW})
        set(SDL2_DEP
                SDL2 https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VERSION}/SDL2-devel-${SDL_VERSION}-mingw.zip
        )
        set(SDL2_mixer_DEP
                SDL2_mixer https://github.com/libsdl-org/SDL_mixer/releases/download/release-${SDL_MIXER_VERSION}/SDL2_mixer-devel-${SDL_MIXER_VERSION}-mingw.zip
        )
        message(STATUS "APPENDING LINK: ${SDL2_DEP}")
        message(STATUS "APPENDING LINK: ${SDL2_mixer_DEP}")
        list(APPEND BLOCKY_DEPS ${SDL2_DEP})
        list(APPEND BLOCKY_DEPS ${SDL2_mixer_DEP})
        message(STATUS "${BLOCKY_DEPS}")
    elseif (${LINUX})
        message(STATUS "${BLOCKY_DEPS}")
        find_package(SDL2 CONFIG REQUIRED)
        find_package(SDL2_mixer CONFIG REQUIRED)
    endif ()

    set(BLOCKY_DEPS "${BLOCKY_DEPS}" PARENT_SCOPE)
endfunction()

########################################################################################################################

function(setup_dependencies)
    #    setup_platform_specifics()
    # Get the range for to loop through BLOCKY_DEPS
    message(STATUS "SETTING UP DEPENDENCIES: ${BLOCKY_DEPS}")
    list(LENGTH BLOCKY_DEPS DEPS_LENGTH)
    math(EXPR LIST_RANGE "${DEPS_LENGTH}-1")

    # This for loop goes through the Blocky_DEPS and uses the build_lib function from fetch_lib.cmake
    # Syntax is (var RANGE begin end)
    # Because of the Blocky_DEPS structure as a pair it will go through the loop mod 2, because it will always be NAME;URL
    foreach (INDEX RANGE 0 ${LIST_RANGE})
        math(EXPR MOD_RESULT "${INDEX} % 2")
        if (${MOD_RESULT} EQUAL 0)
            list(GET BLOCKY_DEPS ${INDEX} LIB_NAME)
        else ()
            message(STATUS "DOWNLOADING: ${LIB_NAME}, ${LIB_URL}")
            list(GET BLOCKY_DEPS ${INDEX} LIB_URL)
            message(STATUS "Library: ${LIB_NAME}, URL: ${LIB_URL}")
            if (${LIB_NAME} STREQUAL "stb_image")
                build_lib_from_file("${DEPS_DIR}/${LIB_NAME}"
                        "stb_image"
                        "h"
                        ${LIB_URL}
                )
            elseif (${LIB_NAME} STREQUAL "json")
                build_lib_from_file("${DEPS_DIR}/${LIB_NAME}"
                        "json"
                        "hpp"
                        ${LIB_URL}
                )
            else ()
                message(STATUS "BUILDING LIB: ${LIB_NAME}")
                build_lib(${DEPS_DIR}
                        ${LIB_NAME}
                        ${LIB_URL}
                        TRUE
                )
            endif ()
        endif ()
    endforeach ()
endfunction()

########################################################################################################################
# Temporarily just copy the SDL2 dll to the build folder

function(copy_dll_to_build dll dll_location)
    message(STATUS "${dll} starting copy to build")
    add_custom_command(TARGET ${ENGINE_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${dll_location}"
            "${CMAKE_BINARY_DIR}"
            COMMENT "Copying SDL2.dll to build folder"
    )
endfunction()
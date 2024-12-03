cmake_minimum_required(VERSION 3.22)

set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")
set(DEPS_DOWNLOADED FALSE CACHE BOOL INTERNAL "")

# Versioning for ease of use to minimally change the links
set(GTEST_VERSION "1.15.2")
set(SDL_VERSION "2.30.9")
set(GLM_VERSION "1.0.1")
set(BOX2D_VERSION "3.0.0")

set(BLOCKY_DEPS
        googletest https://github.com/google/googletest/releases/download/v${GTEST_VERSION}/googletest-${GTEST_VERSION}.tar.gz
        SDL2_gfx https://github.com/Dogukan-lab/sdl_gfx_offshoot/releases/download/v1.0.0/SDL_gfx.tar.gz
        glm https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
        box2d https://github.com/erincatto/box2d/archive/refs/tags/v${BOX2D_VERSION}.tar.gz
        stb_image https://raw.githubusercontent.com/nothings/stb/refs/heads/master/stb_image.h
)

function(setup_platform_specifics)
    # Sets the dependencies, OS dependant of the blocky engine, as in, which libraries to build and whatnot
    if (${MINGW})
        set(SDL2_MINGW
                SDL2 https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VERSION}/SDL2-devel-${SDL_VERSION}-mingw.zip
        )
        list(APPEND BLOCKY_DEPS ${SDL2_MINGW})
        message(STATUS "${BLOCKY_DEPS}")
    elseif (${LINUX})
        message(STATUS "${BLOCKY_DEPS}")
        find_package(SDL2 CONFIG REQUIRED)
    endif ()
endfunction()


########################################################################################################################

function(setup_dependencies)
    # Get the range for to loop through BLOCKY_DEPS
    if (NOT DEPS_DOWNLOADED)
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
        set(DEPS_DOWNLOADED TRUE CACHE BOOL INTERNAL "")
    else ()
        message(STATUS "Dependencies already within the engine/dependencies folder")
    endif ()
endfunction()

########################################################################################################################
# Temporarily just copy the SDL2 dll to the build folder

function(copy_dll_to_build dll dll_location)
    message(STATUS "CMAKE BIN DIR: ${CMAKE_BINARY_DIR}")
    message(STATUS "DLL TO COPY: ${dll} LOCATION: ${dll_location}")
    if (EXISTS dll)
        message(STATUS "${dll} starting copy...")
        add_custom_command(TARGET ${ENGINE_TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${dll_location}
                "${CMAKE_BINARY_DIR}"
                COMMENT "Copying SDL2.dll to build folder"
        )
    endif ()
endfunction()
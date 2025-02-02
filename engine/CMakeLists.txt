# Engine name
set(ENGINE_TARGET "BlockyEngineInternal")

include(cmake/fetch_lib.cmake) # The cmake module used for fetching libraries from the internet
include(cmake/build_deps.cmake)

# Options that have to be set by the user, using our engine
option(blocky_build_as_shared "Builds the engine as a shared library" OFF)
option(blocky_build_tests "Builds the testing folder along with the library" OFF)

mark_as_advanced(
        blocky_build_as_shared
        blocky_build_tests
)

########################################################################################################################

setup_platform_specifics()
setup_dependencies()

if (${MINGW})
    message(STATUS "BUILDING MINGW SDL2")
    set(SDL2_DIR "${DEPS_DIR}/SDL2/cmake")
    set(SDL2_mixer_DIR "${DEPS_DIR}/SDL2_mixer/cmake")
    set(SDL2_ttf_DIR "${DEPS_DIR}/SDL2_ttf/cmake")
    set(SDL_NET_DIR "${DEPS_DIR}/SDL_net/x86_64-w64-mingw32")
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_mixer CONFIG REQUIRED)
    find_package(SDL2_ttf CONFIG REQUIRED)

    message("SDL2 INCLUDE DIRS: ${SDL2_INCLUDE_DIRS}")
    message("SDL2 LIBRARY DIRS: ${SDL2_LIBRARIES}")
endif ()

set(BOX2D_INCLUDE_DIRS "${DEPS_DIR}/box2d/include")

# Box2D Options
set(BOX2D_BUILD_UNIT_TEST OFF CACHE BOOL INTERNAL "")
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL INTERNAL "")
###

add_subdirectory("${DEPS_DIR}/SDL2_gfx")
add_subdirectory("${DEPS_DIR}/glm")
add_subdirectory("${DEPS_DIR}/box2d")

if (blocky_build_tests)
    message(STATUS "Building the blocky engine tests")

    enable_testing()

    set(GTest_DIR "${DEPS_DIR}/googletest")
    add_subdirectory(${GTest_DIR})
    add_subdirectory(testing)
endif ()

########################################################################################################################

# Set the target
if (blocky_build_as_shared)
    message(STATUS "BUILDING ${ENGINE_TARGET} AS A SHARED LIB")
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
add_subdirectory(utilities)

set(SDL_TTF_INCLUDE_DIR "${DEPS_DIR}/SDL2_ttf/x86_64-w64-mingw32/include/SDL2")
set(SDL2_mixer_INCLUDE_DIR "${DEPS_DIR}/SDL2_mixer/x86_64-w64-mingw32/include/SDL2")
target_link_libraries(${ENGINE_TARGET} PRIVATE
        mingw32
        glm
        SDL2::SDL2
        SDL2_mixer::SDL2_mixer
        SDL2::SDL2main
        sdl_gfx
        ${SDL_NET_DIR}/lib/libSDL2_net.dll.a
        SDL2_ttf::SDL2_ttf
        box2d
)

# Set the -fPIC for creating it alongside Shared Objects
if (LINUX)
    set_target_properties(
            sdl_gfx PROPERTIES POSITION_INDEPENDENT_CODE ON
    )
endif ()

set(IMGUI_PATH ${DEPS_DIR}/imgui)
set(IMGUI_SOURCES
        ${IMGUI_PATH}/imgui.cpp
        ${IMGUI_PATH}/imgui_draw.cpp
        ${IMGUI_PATH}/imgui_tables.cpp
        ${IMGUI_PATH}/imgui_widgets.cpp
        ${IMGUI_PATH}/backends/imgui_impl_sdl2.cpp
        ${IMGUI_PATH}/backends/imgui_impl_sdlrenderer2.cpp
)

set(SDL_TTF_INCLUDE_DIR "${DEPS_DIR}/SDL2_ttf/x86_64-w64-mingw32/include/SDL2")
set(SDL2_mixer_INCLUDE_DIR "${DEPS_DIR}/SDL2_mixer/x86_64-w64-mingw32/include/SDL2")
set(JSON_INCLUDE_DIR "${DEPS_DIR}/json/single_include/nlohmann")

target_sources(${ENGINE_TARGET} PRIVATE ${IMGUI_SOURCES})
target_include_directories(${ENGINE_TARGET} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${SDL2_INCLUDE_DIRS}
        ${BOX2D_INCLUDE_DIRS}
        ${DEPS_DIR}
        ${IMGUI_PATH}
        ${IMGUI_PATH}/backends
        ${SDL_TTF_INCLUDE_DIR}
        ${SDL_NET_DIR}/include/SDL2
        ${SDL2_mixer_INCLUDE_DIR}
        ${JSON_INCLUDE_DIR}
)

# Copies dll to build directory
if (MINGW)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        copy_dll_to_build(SDL2_DLL "${SDL2_DIR}/../x86_64-w64-mingw32/bin/SDL2.dll")
        copy_dll_to_build(SDL2_mixer_DLL "${SDL2_mixer_DIR}/../x86_64-w64-mingw32/bin/SDL2_mixer.dll")
        copy_dll_to_build(SDL2_TTF_DLL "${SDL2_ttf_DIR}/../x86_64-w64-mingw32/bin/SDL2_ttf.dll")
        copy_dll_to_build(SDL2_NET_DLL "${SDL_NET_DIR}/../x86_64-w64-mingw32/bin/SDL2_net.dll")
    else ()
        copy_dll_to_build(SDL2_DLL "${SDL2_DIR}/../i686-w64-mingw32/bin/SDL2.dll")
        copy_dll_to_build(SDL2_NET_DLL "${SDL_NET_DIR}/../i686-w64-mingw32/bin/SDL2_net.dll")
        copy_dll_to_build(SDL2_mixer_DLL "${SDL2_mixer_DIR}/../i686-w64-mingw32/bin/SDL2_mixer.dll")
        copy_dll_to_build(SDL2_TTF_DLL "${SDL2_ttf_DIR}/../i686-w64-mingw32/bin/SDL2_ttf.dll")
    endif ()
endif ()
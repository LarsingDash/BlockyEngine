# The engine name
set(ENGINE_TARGET "BlockyEngineInternal")

include(cmake/fetch_lib.cmake) #The cmake module used for fetching libraries from the internet
include(cmake/build_deps.cmake)

# Options that have to be set by the user, using our engine
option(blocky_build_as_shared "Builds the engine as a shared library" OFF)
option(blocky_build_tests "Builds the testing folder along with the library" OFF)

#This just looks cool...
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
    message("SDL DIR: ${SDL2_DIR}")
    find_package(SDL2 CONFIG REQUIRED)

    message("SDL2 INCLUDE DIRS: ${SDL2_INCLUDE_DIRS}")
    message("SDL2 LIBRARY DIRS: ${SDL2_LIBRARIES}")
endif ()

add_subdirectory("${DEPS_DIR}/SDL2_gfx")
add_subdirectory("${DEPS_DIR}/glm")

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

target_link_libraries(${ENGINE_TARGET} PRIVATE
        glm
        SDL2::SDL2
        sdl_gfx
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
target_sources(${ENGINE_TARGET} PRIVATE ${IMGUI_SOURCES})
target_include_directories(${ENGINE_TARGET} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${SDL2_INCLUDE_DIRS}
        ${DEPS_DIR}
        ${IMGUI_PATH}
        ${IMGUI_PATH}/backends
)

# Copies dll to build directory
if (MINGW)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        copy_dll_to_build(SDL2_DLL "${SDL2_DIR}/../x86_64-w64-mingw32/bin/SDL2.dll")
    else ()
        copy_dll_to_build(SDL2_DLL "${SDL2_DIR}/../i686-w64-mingw32/bin/SDL2.dll")
    endif ()
endif ()
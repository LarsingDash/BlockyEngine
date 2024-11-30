# Blocky Engine

The Blocky Engine is a modular C++ game engine which can be used for 2D game development. Blocky Engine can be used
without
requiring knowledge about
rendering APIs, audio, physics or networking, as it abstracts all that behind the given modules. It only openly uses GLM
for transformations, meaning that the game developer does interact with the GLM mathematics library a bit.

## Use

After installation (see below) the Blocky Engine can be used by creating an instance of a BlockyEngine in your code.
After that `Run()` can be
called on this instance to let the Blocky Engine take over the flow of the program.

```cpp
#include <BlockyEngine.hpp>

int main(void) {
    BlockyEngine engine;
    engine.Run();
}
```

Temporarily, a scene can be made by adding GameObjects to the `testScene` in the constructor in `SceneManager.cpp`.
Custom Components can be made by creating a class that inherits from `Component`, implementing a constructor,
destructor, `void Start()`, `void Update(float delta)` and `void End()`. Note that the constructor and destructor are
intended to be used for the component's own data, whereas Start and End should be used for interaction with Blocky
Engine's various modules.

## Custom Modules

Currently, the Blocky Engine only contains the Window Module (internally containing the Rendering Module) with a tight
coupling. Custom Modules are therefore not yet supported. In the future, these modules will be linked through
libraries (.dll/.so), found through a config file. Custom implementations of these modules could be made by following
the same module interface, and
included by changing the filepath in this config file.

## Configuration

The Blocky Engine has simple configuration, it will download its dependencies automatically into its 'dependencies' folder. 

### Options

The Blocky Engine also supports multiple options, such as: building with tests and building as a static or shared
library.

To set these options, in your projects cmake set the following:

```cmake
set(blocky_build_tests ON CACHE INTERNAL "This is a description")
set(blocky_build_as_shared ON CACHE INTERNAL "This is also a description")
```

This sets the option within Blocky Engine to on. It is recommended to cache these options, because otherwise it will
reset these options (which is not necessary). You can also add a description, but that is optional.

## Installation

To run the Blocky Engine, download this project from GitHub and have CLion installed (or any other IDE that supports
CMake). Open the project using either a MinGW toolchain configuration or WSL/Linux toolchain, there is no support for
Mac devices. When cloning the engine it should, on its own, be able
to download the dependencies it needs. If it is not able to download anything, then see below to configure it.

### Manually download dependencies

After correctly installing the required libraries (as listed below) everything will be handled in the CMakeLists.txt of the
Blocky Engine.

### SDL2

This build of Blocky Engine is intended to be used with SDL release 2.30.9. The library can be downloaded
at [the official GitHub](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.9) listed as
`SDL2-devel-2.30.9-mingw.zip`. From this zip file, extract the `bin`, `include` and
`lib` folders from `x86_64-w64-mingw32` into `engine/dependencies/SDL2/`. 
In the case of Linux it's required that you have the SDL-development libraries downloaded on your system/distro. If the dependencies are not installed, the Blocky Engine will try to install the dependencies itself, which in the case of Linux is not encouraged. Obscure libraries such as SDL_gfx, will be handled by the engine.
The `PATH` environment variable needs to be
pointing to
this bin folder. This can be
done in CLion by setting the variable in the run configuration to `engine/dependencies/SDL2/bin;` (make sure to enable
include
system environment variables).
Or if that's too difficult simply copy and paste the DLL/SO into the cmake-build directory.


### SDL2_gfx

The Rendering Module, currently embedded in Blocky Engine, not only uses SDL2 for rendering, but also the SDL2_gfx
extension library for certain specific functionality. This is a source-code library, of which all files can be
downloaded at [the official website](https://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/files.html). These files
should be placed in `engine/dependencies/SDL2_gfx/` in addition to the following CMakeLists.txt:

```cmake
find_package(SDL2 REQUIRED)
add_library(sdl_gfx)

target_sources(sdl_gfx PRIVATE
        SDL2_framerate.c
        SDL2_gfxPrimitives.c
        SDL2_imageFilter.c
        SDL2_rotozoom.c
)

target_link_libraries(sdl_gfx PUBLIC
        SDL2::SDL2
)
target_link_directories(sdl_gfx PUBLIC
        ${SDL2_INCLUDE_DIRS}
)
```

The reason we're using `find_package()` is because SDL2 should always be built before including SDL_gfx,
meaning we can use the variables provided by the SDL2 config.

### glm

The Blocky Engine uses GLM for all mathematics. The GLM library can be downloaded
from [the official GitHub](https://github.com/g-truc/glm/releases/tag/1.0.1) listed as `glm-1.0.1-light.zip`. The
contents of this zip file should be extracted to `engine/dependencies/glm/`.

### stb_image

This project uses the stb_image header for parsing PNG formats. This header can be directly copied
from [the official GitHub](https://github.com/nothings/stb/blob/master/stb_image.h). This header file should be placed
in `engine/dependencies/stb_image/stb_image.h`.
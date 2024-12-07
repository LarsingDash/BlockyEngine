# Blocky Engine

Blocky Engine is a modular C++ game engine which can be used for 2D game development. Blocky Engine can be used
without
requiring knowledge about
rendering APIs, audio, physics or networking, as it abstracts all that behind the given modules. It only openly uses GLM
for transformations, meaning that the game developer does interact with the GLM mathematics library a bit.

## Use

After installation (see below) Blocky Engine can be used following these steps:
1. Create an instance of a BlockyEngine.
2. Create a scene.
3. Add the scene to the SceneManager from BlockyEngine instance, also select is as the starting scene.
4. Finally, `Run()` can be
called on the BlockyEngine instance to let Blocky Engine take over the flow of the program.

```cpp
#include <BlockyEngine.hpp>
#include "CustomComponents/ExampleComponent"

int main() {
	//Step 1
	BlockyEngine blockyEngine;
	
	//Step 2
	//Create a root for the scene
	auto exampleRoot = std::make_unique<GameObject>("ExampleScene");
	exampleRoot->SetActive(false);	//Do not forget to set the scene as inactive

	//Add and configure a child object
	auto& child = exampleRoot->AddChild("ExampleChild");
	child.transform->SetPosition(300.f, 300.f);
	child.transform->SetRotation(45.f);
	child.transform->SetScale(25.f, 50.f);
	
	//Add and configure a component
	auto& component = child.AddComponent<ExampleComponent>("ExampleComponent", 10);
	component.componentTransform->SetPosition(2.5f, 0.f);
	component.SetExampleValue(100);
	
	//Step 3
	SceneManager& sceneManager = blockyEngine.GetSceneManager();
	sceneManager.AddScene(std::move(exampleRoot));
	sceneManager.SwitchScene("ExampleScene");

	//Step 4
	blockyEngine.Run();
}
```
Notes:
- Creating prefabs or scenes (technically the same thing, often just larger) should be the only time when a GameObject is instantiated by directly using the constructor. When building within a prefab (or scene), `AddChild()` should always be used for either a new GameObject, or one from instantiating a prefab.
- After creating a prefab, it should always immediately be set to inactive before add any Components, this can be done using `prefabRoot->SetActive(false)`. This needs to be done to prevent Components from triggering `Start()`, and thus registering themselves to various Modules
- For easier compatibility with the `SceneManager`, it is recommended to create a prefab using `std::make_unique<GameObject>("ExampleRootName")`. Then use `std::move(exampleRoot)` when adding the scene to the Manager using `.AddScene()`.

### Data Types

This engine uses the game development philosophy of Unity, in which, it uses the GameObjects, Transforms and Components as primary data types. The engine provides these types alongside itself:

- GameObject: The core datatype that the user of this engine will mostly be interfacing with when creating scenes and
  the like. It has support for: Multiple Components of the same type, parent-children relations and prefab instantiation.
- Transform: This is used to transform a GameObject or Component. It supports getting and setting on local-space (meaning relative to it's parent), and getting on world-space (meaning absolute). `Transform` itself is abstract and is not directly used, but does facilitate all core logic for its inheritors:
  - GameObject Transform: Used by GameObjects to stay relative to their parenting GameObject.
  - Component Transform: Used by Components to stay relative to the GameObjects that owns this Component.
- Component: `Component` itself is abstract and cannot be directly added to a GameObject. Instead, it is the base for al components that define the logic of the game. These components can be custom-made (see chapter below) or provided by Blocky Engine:
  - Renderable: This is the base class for anything that will be drawn to the screen (apart from UI). `Renderable` itself is not directly usable, since it's abstract, use instead: `RectangleRenderable`, `EllipseRenderable`, `SpriteRenderable` or `AnimationRenderable`. The AnimationRenderable is inherited from SpriteRenderable and can be controlled by an `AnimationController`. 
  - Animation Controller: An `AnimationController` must be used in combination with an `AnimationRenderable` to animate. The tag of this renderable must be given to the controller for it to connect automatically, they also need to be components of the same GameObject. Different animations can then be added to the controller and triggered from other components.

### Custom Components

Components drive the behavior of a game. However, Blocky Engine only provides the standard components as listed above (and some examples). For GameObjects to start behaving uniquely, custom components must be made. This can be done by inheriting from `Component`. Displayed below is a template of how a custom component should be made, with some extra notes:

```c++
#ifndef EXAMPLECOMPONENT_H
#define EXAMPLECOMPONENT_H

#include <components/Component.hpp>

class ExampleComponent : public Component {
    public:
        ExampleComponent(GameObject* gameObject, const char* tag, int startingValue);
        ~ExampleComponent() = default; //Optional

        void Start() override;
        void Update(float delta) override;
        void End() override;
		
		void SetExampleValue(int value);
	
    private:
        Component* _clone(GameObject& parent) override;
        
        int _exampleValue;
};
#endif //EXAMPLECOMPONENT_H
```

Notes:
- The constructor of Component requires a GameObject& aside from the tag. This reference will be set in GameObject's AddComponent<...>() method. Therefor, only a tag and any custom values need to be passed through this method.
- An `ExampleComponent()`, `Start()`, `Update(float delta)`, `End()` and `_clone(const GameObject& parent)` are all required for this custom component "ExampleComponent" to be allowed to be used as `.AddComponent<ExampleComponent>()`. An `~ExampleComponent()` can optionally be used if this custom component has a need for it, the same goes for `ExampleComponent(const ExampleComponent& other)`. Copy-assignment, move-constructor en move-assignment should not be implemented in components.
- `_clone(...)` is used in prefab instantiation, after which `Start()` will be called if the prefab should be active. Keep in mind that any references to other GameObjects or Components that ExampleComponent might have will still point to the versions from the prefab. Therefor, it is recommended to design the game in a way where these references can be consistently re-established in `Start()`. For any member variables that are not compatible with an "= default" copy-constructor, the copy-constructor should be implemented manually.
- Custom methods, like `SetExampleValue(int value)` as shown in the example for a `main` setup, can of course be (publicly or privately) added to a custom Component.

```c++
#include <gameObject/GameObject.hpp>

ExampleComponent::ExampleComponent(GameObject* gameObject, const char* tag, int startingValue) :
    Component(gameObject, tag, false), _exampleValue(startingValue) {}

void ExampleComponent::Start() {
    //Interaction with other GameObjects, Components or Modules, not this Component's data. For example:
    //InputModule& inputModule = ModuleManager::GetInstance().GetModule<WindowModule>().GetInputModule();
}

void ExampleComponent::Update(float delta) {
    //This logic is updated every frame
}

void ExampleComponent::End() {
    //Unsubscribe from anything that has been subscribed to in Start()
}

void ExampleComponent::SetExampleValue(int value) { _exampleValue = value; }
```

Notes:
- The `constructor` and `destructor` are intended to be used for the component's own data, whereas `Start()` and `End()` should be used for interacting with (other) GameObjects, or components or Blocky Engine's various modules.
- The constructor has an optional boolean (by default false) that decides if this Component type has an extra `ComponentTransform`. This is mainly used for when components on the same GameObject need to be able to be separated. This option is explicitly specified as false in the example code for extra clarity.
- `_clone()` will be the same for almost all components, however it is simply required for prefabs to work. Since scenes can also be considered to be big prefabs, this method is required for every component. It is called from the parenting GameObject of the prefab when it's cloning itself and all of its components. The point is to simply create an identical copy to give to the newly created instance of the prefab.
- The #include for `GameObject` at the top of this source file is optional if a component doesn't interact with any GameObject logic (which is rare, hence why it's included in this template). Since `Component` only forward-declares GameObject, this include is required for any further use. **_Never_** include `GameObject` (or anything that includes it) in a component's header, as that will cause a circular include chain, only in the source file.

## Custom Modules

Currently, Blocky Engine only contains the Window Module (internally containing the Rendering Module) with a tight
coupling. Custom Modules are therefore not yet supported. In the future, these modules will be linked through
libraries (.dll/.so), found through a config file. Custom implementations of these modules could be made by following
the same module interface, and
included by changing the filepath in this config file.

## Configuration

Blocky Engine has simple configuration, it will download its dependencies automatically into its 'dependencies'
folder. To set up the engine through the cmake:

```cmake
cmake_minimum_required(VERSION 3.27)
project(CustomProject)

# The options that are provided with Blocky Engine are always off.

# Since this will be downloaded into your project, but this can be any directory. 
# It is discouraged to make this a hardcoded path, so use the cmake vars for this.
add_subdirectory("deps/engine")
add_executable(${PROJECT_NAME} main.cpp)

# This is the target where we want to link to, this one changes
# depending on if you turned on the `blocky_build_shared` option.
target_link_libraries(${PROJECT_NAME} Blocky::Engine) 
```

### Options

Blocky Engine also supports multiple options, such as: building with tests and building as a static or shared
library.

To set these options, in your projects cmake set the following:

```cmake
set(blocky_build_tests ON CACHE INTERNAL "This is a description")
set(blocky_build_as_shared ON CACHE INTERNAL "This is also a description")
```

This sets the option within Blocky Engine to on. It is recommended to cache these options, because otherwise it will
reset these options (which is not necessary). You can also add a description, but that is optional.

## Installation

To run Blocky Engine, download this project from GitHub and have CLion installed (or any other IDE that supports
CMake). Open the project using a MinGW toolchain configuration. When cloning the engine it should, on its own, be
able
to download the dependencies it needs. If it is not able to download everything, then see below to configure it.

## Manually download dependencies

After correctly installing the required libraries (as listed below) everything will be handled in the CMakeLists.txt of
the
Blocky Engine.

### SDL2

This build of Blocky Engine is intended to be used with SDL release 2.30.9. The library can be downloaded
at [the official GitHub](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.9) listed as
`SDL2-devel-2.30.9-mingw.zip`. From this zip file, extract the `bin`, `include` and
`lib` folders from `x86_64-w64-mingw32` into `engine/dependencies/SDL2/`.
In the case of Linux it's required that you have the SDL-development libraries downloaded on your system/distro. If the
dependencies are not installed, Blocky Engine will try to install the dependencies itself, which in the case of
Linux is not encouraged. Obscure libraries such as SDL_gfx, will be handled by the engine.
The `PATH` environment variable needs to be
pointing to
this bin folder. This can be
done in CLion by setting the variable in the run configuration to `engine/dependencies/SDL2/bin;` (make sure to enable
include
system environment variables).
Or if that's too difficult simply copy and paste the DLL/SO into the cmake-build directory.

### SDL2_gfx

### SDL2_gfx Offshoot

For this project there is also a stripped down version of SDL_gfx
[here](https://github.com/Dogukan-lab/sdl_gfx_offshoot/releases/tag/v1.0.0), there, will be no need
to set up the cmake (seen below).
---

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

Blocky Engine uses GLM for all mathematics. The GLM library can be downloaded
from [the official GitHub](https://github.com/g-truc/glm/releases/tag/1.0.1) listed as `glm-1.0.1-light.zip`. The
contents of this zip file should be extracted to `engine/dependencies/glm/`.

### stb_image

This project uses the stb_image header for parsing PNG formats. This header can be directly copied
from [the official GitHub](https://github.com/nothings/stb/blob/master/stb_image.h). This header file should be placed
in `engine/dependencies/stb_image/stb_image.h`.
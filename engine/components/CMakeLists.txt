target_sources(${ENGINE_TARGET} PRIVATE
        Component.cpp
        ComponentTransform.cpp
        Move.cpp
)

add_subdirectory(animation)
add_subdirectory(audio)
add_subdirectory(example)
add_subdirectory(json)
add_subdirectory(pathfinding)
add_subdirectory(physics)
add_subdirectory(renderables)

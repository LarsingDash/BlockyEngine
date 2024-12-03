target_sources(${PROJECT_NAME} PRIVATE
        Component.cpp
        ComponentTransform.cpp
        example/SpawnerComp.cpp
        example/MovementComp.cpp
)
add_subdirectory(animation)
add_subdirectory(example)
add_subdirectory(renderables)

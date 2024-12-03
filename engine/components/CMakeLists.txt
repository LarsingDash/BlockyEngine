target_sources(${PROJECT_NAME} PRIVATE
        Component.cpp
        ComponentTransform.cpp
        example/SpawnerComp.cpp
        example/MovementComp.cpp
)
add_subdirectory(renderables)
add_subdirectory(animation)

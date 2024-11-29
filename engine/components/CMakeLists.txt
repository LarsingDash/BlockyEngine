target_sources(${PROJECT_NAME} PRIVATE
        Component.cpp
        ComponentTransform.cpp
)
add_subdirectory(physics/physicsShape)
add_subdirectory(renderables)

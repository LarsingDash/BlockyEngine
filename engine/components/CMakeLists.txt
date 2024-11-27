target_sources(${PROJECT_NAME} PRIVATE
        Component.cpp
        ComponentTransform.cpp
)
add_subdirectory(physicsShape)
add_subdirectory(renderables)

target_sources(${PROJECT_NAME} PRIVATE
        Component.cpp
        ComponentTransform.cpp
)
add_subdirectory(collider)
add_subdirectory(renderables)

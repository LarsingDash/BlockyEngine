target_sources(${PROJECT_NAME} PRIVATE
        Component.cpp
        ComponentTransform.cpp
)
add_subdirectory(renderables)
add_subdirectory(animation)
add_subdirectory(custom)

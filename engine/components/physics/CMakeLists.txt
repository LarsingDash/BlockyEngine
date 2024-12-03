target_sources(${PROJECT_NAME} PRIVATE
        PhysicsBody.cpp
)

add_subdirectory(collider)
add_subdirectory(shape)
add_subdirectory(rigidBody)
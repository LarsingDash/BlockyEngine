target_sources(${ENGINE_TARGET} PRIVATE
        PhysicsBody.cpp
)

add_subdirectory(collider)
add_subdirectory(shape)
add_subdirectory(rigidBody)
add_subdirectory(collision)
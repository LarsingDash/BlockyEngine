target_sources(${ENGINE_TARGET} PRIVATE
        WindowModule.cpp
)

add_subdirectory(physics)
add_subdirectory(rendering)
add_subdirectory(input)

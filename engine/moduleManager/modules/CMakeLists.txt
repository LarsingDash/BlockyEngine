target_sources(${ENGINE_TARGET} PRIVATE
        WindowModule.cpp
)

add_subdirectory(audio)
add_subdirectory(rendering)
add_subdirectory(input)

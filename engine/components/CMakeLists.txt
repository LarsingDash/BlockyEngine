﻿target_sources(${ENGINE_TARGET} PRIVATE
        Component.cpp
        ComponentTransform.cpp
)

add_subdirectory(audio)
add_subdirectory(physics)
add_subdirectory(animation)
add_subdirectory(example)
add_subdirectory(renderables)

target_sources(${ENGINE_TARGET} PRIVATE
        ModuleManager.cpp
        ModuleWrapper.cpp
)

add_subdirectory(modules)
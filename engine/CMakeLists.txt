add_subdirectory(moduleManager)
add_subdirectory(sceneManager)
add_subdirectory(components)
add_subdirectory(gameObject)
add_subdirectory(logging)

target_sources(${PROJECT_NAME} PRIVATE
        BlockyEngine.cpp
)

#add_library(BlockyEngineInternal SHARED BlockyEngine.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
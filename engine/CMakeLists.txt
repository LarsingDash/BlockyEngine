target_sources(${PROJECT_NAME} PRIVATE
        BlockyEngine.cpp
)

add_subdirectory(moduleManager)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
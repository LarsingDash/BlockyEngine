#Google Test
set(TARGET "Testing")

enable_testing()

set(GTest_DIR "${LIBS_DIR}/googletest")
add_subdirectory(${GTest_DIR})

if (${WIN32})
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()

message(STATUS "Linking ${TARGET}")

set(SOURCES
        testMain.cpp
        BLogger_Fixture.cpp
        TestTest.cpp
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} BlockyEngineInternal gtest gtest_main gmock)

include(GoogleTest)

add_test(
        NAME RunAllTests COMMAND ${TARGET}
)

add_test(
        NAME BLogger_Tests
        COMMAND ${TARGET} --gtest_filter=BLogger_Fixture.*
)
add_test(
        NAME TestTest
        COMMAND ${TARGET} --gtest_filter=TestTest.*
)
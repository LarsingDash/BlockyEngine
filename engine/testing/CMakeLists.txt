#Google Test
set(TARGET "Testing")

if (${WIN32})
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()

message(STATUS "Linking ${TARGET}")

# Sets the sources in a list for convenience
set(SOURCES
        testMain.cpp
        tests/BLogger_Fixture.cpp
        tests/TestTest.cpp
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} ${ENGINE_TARGET} gtest gtest_main gmock)
include(GoogleTest)
#gtest_discover_tests(${TARGET})

# CTest integration
# Adds the test to the CTest config to run for a target
add_test(
        NAME RunAllTests COMMAND ${TARGET}
)

# These ones add a filtering option to the target to run only certain tests.
add_test(
        NAME BLogger_Tests
        COMMAND ${TARGET} --gtest_filter=BLogger_Fixture.*
)
add_test(
        NAME TestTest
        COMMAND ${TARGET} --gtest_filter=TestTest.*
)
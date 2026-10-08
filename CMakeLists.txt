cmake_minimum_required(VERSION 3.29)
project(PTR)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.16.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(PtrTests
        tests/testUnique.cpp
        tests/testShared.cpp
)

target_link_libraries(PtrTests
        PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(PtrTests)

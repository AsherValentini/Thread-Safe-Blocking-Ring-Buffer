cmake_minimum_required(VERSION 3.10)
project(thread-safe-blocking-ring-buffer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_executable(prog
	src/main.cpp
)

enable_testing()
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(ring_tests
	tests/ring_buffer_tests.cpp
)

target_link_libraries(ring_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(ring_tests)


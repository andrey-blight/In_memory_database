cmake_minimum_required(VERSION 3.29)
project(database_library)

# set standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# install gtest for testing
set(CMAKE_OSX_ARCHITECTURES "arm64")

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)

# header directories
include_directories(include)

# cpp files for headers
file(GLOB_RECURSE LIB_SOURCES src/*.cpp)

# create library database
add_library(database STATIC ${LIB_SOURCES}
        src/column.cpp
        src/commands/SelectCommand.cpp)
target_include_directories(database PUBLIC include)

# Create tests files
add_executable(test_database tests/create_tests.cpp tests/insert_tests.cpp)
target_link_libraries(test_database database GTest::gtest GTest::gtest_main)
enable_testing()
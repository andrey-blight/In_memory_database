cmake_minimum_required(VERSION 3.29)
project(database)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_executable(main main.cpp)

target_link_libraries(main database)

cmake_minimum_required(VERSION 3.20)

project(khustup)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/generators")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build/generators")

add_subdirectory(src)
add_subdirectory(tests)
enable_testing()

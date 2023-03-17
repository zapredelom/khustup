cmake_minimum_required(VERSION 3.18)

project(khustup)

IF(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
  include_directories(/usr/include/opencv4)
  include(FetchContent)
  FetchContent_Declare(
    rpi_ws281x
    GIT_REPOSITORY git@github.com:jgarff/rpi_ws281x.git
  )
  FetchContent_MakeAvailable(rpi_ws281x)
endif()

set(CMAKE_CXX_STANDARD 20)
add_compile_options(/experimental:module)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# force MD for all configs
add_compile_options(/MD)
enable_testing()

if(MSVC)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/generators")
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build/generators")
else()
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/Release/generators")
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/Debug/generators")
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build/Releas/generators")
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build/Debug/generators")
endif()

add_subdirectory(src)
add_subdirectory(tests)

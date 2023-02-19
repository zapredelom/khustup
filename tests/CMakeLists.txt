
enable_testing()
set(CMAKE_VERBOSE_MAKEFILE ON)
file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp)

find_package(GTest REQUIRED)

add_executable(tests test_main.cpp ${sources})

target_link_libraries(tests GTest::GTest GTest::gtest_main utils)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(tests tests)

file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp)

add_executable(tests main.cpp ${sources})


target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
find_package(gtest REQUIRED)

target_link_libraries(tests gtest::gtest utils)

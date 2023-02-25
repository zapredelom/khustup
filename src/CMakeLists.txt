include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(utils)
add_subdirectory(models)
add_subdirectory(services)

find_package(opencv REQUIRED)
add_executable(main main.cpp)
add_dependencies(main utils models)
target_link_libraries(main utils models services opencv::opencv)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(utils)
add_subdirectory(models)
add_subdirectory(services)

#find_package(opencv REQUIRED)
add_executable(main main.cpp)
add_dependencies(main utils models services)

target_include_directories(main PRIVATE ${rpi_ws281x_SOURCE_DIR})

target_link_libraries(main models services utils opencv_core opencv_highgui  pthread ws2811)

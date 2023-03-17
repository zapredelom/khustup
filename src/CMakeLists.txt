include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(opencv REQUIRED)
find_package(Qt6  REQUIRED)
find_package(boost REQUIRED)

add_subdirectory(utils)
add_subdirectory(models)
add_subdirectory(services)
add_subdirectory(ui)


add_executable(main main.cpp)
add_dependencies(main utils models services ui)

target_include_directories(main PRIVATE ${rpi_ws281x_SOURCE_DIR})

target_link_libraries(main ui models services utils opencv::opencv qt::qt boost::boost ) # pthread ws2811)

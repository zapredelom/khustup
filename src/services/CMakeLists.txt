file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ) 
add_library(services ${sources})

target_include_directories(services PRIVATE ${rpi_ws281x_SOURCE_DIR})
target_link_libraries(services PRIVATE opencv_core opencv_highgui opencv_videoio)


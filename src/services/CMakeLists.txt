# file(GLOB_RECURSE sources
#     ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ) 
set (sources 
    ${CMAKE_CURRENT_SOURCE_DIR}/scale_decorator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/drawer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/draw_update_subject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simulation/simulation.cpp
)
add_library(services ${sources})
target_include_directories(services PRIVATE ${rpi_ws281x_SOURCE_DIR})
find_package(OpenCV REQUIRED)
target_include_directories(services PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(services PRIVATE ${OpenCV_LIBS})


# file(GLOB_RECURSE sources
# ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
if(ON_RASBERRY_PI)
	set(rpi_sources "${CMAKE_CURRENT_SOURCE_DIR}/rpi/rpi_drawer.cpp")
endif()

set(sources
    ${CMAKE_CURRENT_SOURCE_DIR}/scale_decorator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/drawer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/draw_update_subject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simulation/simulation.cpp
    ${rpi_sources}
    ${CMAKE_CURRENT_SOURCE_DIR}/draw_network_subject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/draw_network_observer.cpp
)
add_library(services ${sources})
target_include_directories(services PRIVATE  ${Boost_INCLUDE_DIRS} ${rpi_ws281x_SOURCE_DIR})
find_package(OpenCV REQUIRED)
target_include_directories(services PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(services PRIVATE ${boost_libs} ${OpenCV_LIBS})


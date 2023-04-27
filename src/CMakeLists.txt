include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(OpenCV REQUIRED)
#find_package(Qt6 REQUIRED)
find_package(Boost REQUIRED)

add_subdirectory(utils)
add_subdirectory(models)
add_subdirectory(services)
add_subdirectory(networking)

# add_subdirectory(ui)
add_executable(main main.cpp)
add_dependencies(main utils models services networking)

target_include_directories(main PRIVATE ${rpi_ws281x_SOURCE_DIR} ${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(main  models services utils networking  ${OpenCV_LIBS} ${Qt_Libs} ${boost_libs})

if(UNIX)
  target_link_libraries(main pthread)
  if(ON_RASBERRY_PI)
    target_link_libraries(main ws2811)
  endif()
endif()

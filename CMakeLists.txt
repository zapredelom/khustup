cmake_minimum_required(VERSION 3.18)
project(khustup)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(EXISTS /proc/cpuinfo)
  file(READ /proc/cpuinfo CPU_INFO)
  string(FIND ${CPU_INFO} "Hardware	: BCM" FOUND_INDEX)

  if(FOUND_INDEX GREATER -1)
    set(ON_RASBERRY_PI TRUE)
  else()
    set(ON_RASBERRY_PI FALSE)
  endif()
else()
  set(ON_RASBERRY_PI FALSE)
endif()

if(ON_RASBERRY_PI)
  add_compile_definitions(ON_RASBERRY_PI)
  include_directories(/usr/include/opencv4)
  include(FetchContent)
  FetchContent_Declare(
    rpi_ws281x
    GIT_REPOSITORY git@github.com:jgarff/rpi_ws281x.git
  )
  FetchContent_MakeAvailable(rpi_ws281x)
endif()

if(MSVC)
  add_compile_options(/MD)
  add_compile_options(/experimental:module)
  enable_testing()
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/generators")
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build/generators")
  list(APPEND CMAKE_PREFIX_PATH "C:/opencv/opencv/build/x64/vc16/lib")
  list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.4.2/msvc2019_64/lib/cmake")
else()
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/Release/generators")
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/build/Debug/generators")
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build/Releas/generators")
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build/Debug/generators")
endif()

add_subdirectory(src)
# add_subdirectory(tests)

set(INSTALL_INCLUDE_DIR include)
install(TARGETS models
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_SOURCE_DIR}/include/models/color.h
  ${CMAKE_SOURCE_DIR}/include/models/coordinate.h
  ${CMAKE_SOURCE_DIR}/include/models/draw_canvas.h
  ${CMAKE_SOURCE_DIR}/include/models/draw_point.h
  ${CMAKE_SOURCE_DIR}/include/models/draw_update.h
  DESTINATION ${INSTALL_INCLUDE_DIR}/models)

install(TARGETS services
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_SOURCE_DIR}/include/services/draw_network_subject.h
  ${CMAKE_SOURCE_DIR}/include/services/draw_update_observer.h
  ${CMAKE_SOURCE_DIR}/include/services/draw_update_subject.h
  ${CMAKE_SOURCE_DIR}/include/services/drawer.h
  ${CMAKE_SOURCE_DIR}/include/services/scale_decorator.h

  ${CMAKE_SOURCE_DIR}/include/services/simulation/simulation.h
  ${CMAKE_SOURCE_DIR}/include/services/rpi/rpi_drawer.h
  DESTINATION ${INSTALL_INCLUDE_DIR}/services)

install(FILES ${CMAKE_SOURCE_DIR}/include/utils/measurer.h
  ${CMAKE_SOURCE_DIR}/include/utils/type_aliases.h
  DESTINATION ${INSTALL_INCLUDE_DIR}/utils
)
install(TARGETS utils
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

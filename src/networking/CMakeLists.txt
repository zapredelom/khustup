set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/draw_client.cpp ${CMAKE_CURRENT_SOURCE_DIR}/draw_update_raw_data.cpp)
add_library(networking STATIC ${SOURCES})
target_include_directories(networking PRIVATE  ${Boost_INCLUDE_DIRS})

target_link_libraries(networking PRIVATE ${boost_libs})

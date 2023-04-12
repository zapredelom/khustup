set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/draw_client.cpp ${CMAKE_CURRENT_SOURCE_DIR}/draw_update_raw_data.cpp)
add_library(networking STATIC ${SOURCES})

target_link_libraries(networking PRIVATE boost::boost)
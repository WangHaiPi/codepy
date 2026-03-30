cmake_minimum_required(VERSION 3.14)
project(codepy VERSION 1.1.0 LANGUAGES CXX)

add_library(codepy INTERFACE)
target_include_directories(codepy INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS codepy EXPORT codepy-config)
install(FILES codepy.h DESTINATION include)
install(EXPORT codepy-config DESTINATION share/codepy)

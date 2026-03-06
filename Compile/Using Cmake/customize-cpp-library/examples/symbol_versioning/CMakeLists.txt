cmake_minimum_required(VERSION 3.10)
project(SymbolVersioningExample)

add_library(mylib SHARED version.c)
set_target_properties(mylib PROPERTIES VERSION 2.0 SOVERSION 1)
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(mylib PROPERTIES LINK_FLAGS "-Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/version_script.map")

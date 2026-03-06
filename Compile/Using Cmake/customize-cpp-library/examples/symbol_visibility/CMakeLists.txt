cmake_minimum_required(VERSION 3.10)
project(SymbolVisibilityExample)

add_library(mylib SHARED core.c)
set_target_properties(mylib PROPERTIES C_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN 1)
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

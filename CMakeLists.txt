#Project level CMake lists. Binds Field_Plotter project to libraries and includes

cmake_minimum_required (VERSION 3.14)
project (Field_Plotter)

include_directories("${CMAKE_SOURCE_DIR}/include")
link_directories("${CMAKE_SOURCE_DIR}/libs")
message("found ${CMAKE_SOURCE_DIR}/include and ${CMAKE_SOURCE_DIR}/libs")

add_subdirectory(src)


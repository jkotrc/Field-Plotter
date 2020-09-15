#Project level CMake lists. Binds Field_Plotter project to libraries and includes

cmake_minimum_required (VERSION 3.14)
project (Field_Plotter)

set(FIELDPLOTTER_OUT "${CMAKE_SOURCE_DIR}/out")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FIELDPLOTTER_OUT})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FIELDPLOTTER_OUT}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FIELDPLOTTER_OUT}/libs)

include_directories("${CMAKE_SOURCE_DIR}/include")
link_directories("${CMAKE_SOURCE_DIR}/libs" "${FIELDPLOTTER_OUT}/libs")
message("Found ${CMAKE_SOURCE_DIR}/include and ${FIELDPLOTTER_OUT}/libs")

add_subdirectory(src/libfieldplotter)
add_subdirectory(src/fieldplotter)

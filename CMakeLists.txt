cmake_minimum_required (VERSION 3.16)
project (Field_Plotter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
find_package(GTest REQUIRED)

set(FIELDPLOTTER_OUT "${CMAKE_SOURCE_DIR}/out")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FIELDPLOTTER_OUT})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FIELDPLOTTER_OUT})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FIELDPLOTTER_OUT})

include_directories("${CMAKE_SOURCE_DIR}/include") #"${CMAKE_SOURCE_DIR}/src/libfieldplotter")
link_directories("${CMAKE_SOURCE_DIR}/libs") #"${FIELDPLOTTER_OUT}/libs")

add_subdirectory(src/libfieldplotter)
add_subdirectory(src/testing)

if(WIN32)
    add_subdirectory(src/fieldplotter)
endif()
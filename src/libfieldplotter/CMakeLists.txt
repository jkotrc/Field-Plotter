#Top-level CMakeLists for Field_Plotter
cmake_minimum_required (VERSION 3.14)


#set(FIELDPLOTTER_SOURCES Field_Plotter.cpp Debug.h)
set(LIBFIELDPLOTTER_MODULES computation file graphics gui)


foreach (X IN LISTS LIBFIELDPLOTTER_MODULES)
    file(GLOB MODULE_SOURCES "${X}/*")
    set(LIBFIELDPLOTTER_SOURCES ${LIBFIELDPLOTTER_SOURCES} ${MODULE_SOURCES})
endforeach()


message("Found these sources: ${LIBFIELDPLOTTER_SOURCES}")
message("OUTPUT WILL BE PUT IN ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

add_library (fieldplotter ${LIBFIELDPLOTTER_SOURCES})

#find_package(glfw3 REQUIRED)

if(WIN32)
target_link_libraries(fieldplotter glew32s.lib glfw3.lib opengl32)
ELSE()
target_link_libraries(fieldplotter pthread libGLEW.a GL glfw)
ENDIF()
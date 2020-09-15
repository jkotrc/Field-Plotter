#Top-level CMakeLists for Field_Plotter
cmake_minimum_required (VERSION 3.14)


#set(FIELDPLOTTER_SOURCES Field_Plotter.cpp Debug.h)
set(FIELDPLOTTER_MODULES .)


add_executable (frontend main.cpp)

#find_package(glfw3 REQUIRED)

IF(WIN32)
target_link_libraries(frontend glew32s.lib glfw3.lib fieldplotter)
ELSE()
target_link_libraries(frontend libGLEW.a glfw fieldplotter)
ENDIF()
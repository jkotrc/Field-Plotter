#Top-level CMakeLists for Field_Plotter
cmake_minimum_required (VERSION 3.14)


set(LIBFIELDPLOTTER_HEADERS
    chargesystem.h
    computation.h
    fieldlines.h
    graphics.h
    physicalobject.h
    plottable.h
    plottermath.h
    point_operators.inl
    scene.h
    vectorfield.h
)
set(LIBFIELDPLOTTER_HEADERS ${LIBFIELDPLOTTER_HEADERS})

set(LIBFIELDPLOTTER_SOURCES
    chargesystem.cpp
    Camera.cpp
    computation.cpp
    fieldlines.cpp
    graphics.cpp
    physicalobject.cpp
    scene.cpp
    vectorfield.cpp
    Shaders.h   #this is taken as a source because it won't be copied to out/libs/include
 )
set(LIBFIELDPLOTTER_SOURCES ${LIBFIELDPLOTTER_SOURCES})


#foreach (X IN LISTS LIBFIELDPLOTTER_MODULES)
#    file(GLOB MODULE_SOURCES "${X}/*")
#    set(LIBFIELDPLOTTER_SOURCES ${LIBFIELDPLOTTER_SOURCES} ${MODULE_SOURCES})
#endforeach()


message("Found these sources: ${LIBFIELDPLOTTER_SOURCES} ")
message("OUTPUT WILL BE PUT IN ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

add_library (fieldplotter ${LIBFIELDPLOTTER_SOURCES} ${LIBFIELDPLOTTER_HEADERS})


if(WIN32)
target_link_libraries(fieldplotter glew32s.lib glfw3.lib opengl32)
#add_custom_command(TARGET fieldplotter.lib POST_BUILD COMMAND "cp ${LIBFIELDPLOTTER_HEADERS} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/include")
ELSE()
target_link_libraries(fieldplotter pthread libGLEW.a GL glfw)
#add_custom_command(TARGET fieldplotter.a POST_BUILD COMMAND "cp foo.h ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/include")
ENDIF()


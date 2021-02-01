set(LIBFIELDPLOTTER_HEADERS
    "dynamicobject.h"
    "plottable.h"
    "plottermath.h"
    "point_operators.inl"
    "scene.h"
    "common/readerwriterqueue.h"
)

set(LIBFIELDPLOTTER_SOURCES
    "components/chargesystem.cpp"
    "components/dynamicobject.cpp"
    "components/fieldlines.cpp"
    "components/scene.cpp"
    "components/plottable.cpp"
    "components/debugtriangle.cpp"
    "computation/plottermath.cpp"
    "computation/physics.cpp"
    "graphics/camera.cpp"
    "graphics/graphics.cpp"
    "graphics/bufferobject.cpp"
    "graphics/shaders.h"
    "graphics/sceneuniforms.cpp"
    "graphics/renderer.cpp"
    "graphics/model.cpp"
    "graphics/attribute.h"
)

add_library (fieldplotter ${LIBFIELDPLOTTER_SOURCES})
target_precompile_headers(fieldplotter PUBLIC "fieldplotter_pch.h")
if(WIN32)
    target_link_libraries(fieldplotter ${GTEST_BOTH_LIBRARIES} glew32s.lib opengl32)
else()
    target_link_libraries(fieldplotter ${GTEST_BOTH_LIBRARIES} pthread libGLEW.a GL)
endif()
target_include_directories(fieldplotter PUBLIC "${SOURCE_DIR}")

install(
    TARGETS              "fieldplotter"
    EXPORT               "libfieldplotter"
    LIBRARY DESTINATION  "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libs/"
    INCLUDES DESTINATION "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/include/fieldplotter"
)
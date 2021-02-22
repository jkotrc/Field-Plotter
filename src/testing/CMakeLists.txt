set(TESTING_SOURCES 
        "tests.cpp"
        "attributetest.cpp"
        "modeltest.cpp"
)
if(NOT WIN32)
    find_package(glfw3 REQUIRED)
    add_executable(testing ${TESTING_SOURCES})
    target_link_libraries(testing fieldplotter glfw)
else()
    add_executable(testing ${TESTING_SOURCES})
    target_link_libraries(testing glew32s.lib glfw3.lib fieldplotter)
endif()
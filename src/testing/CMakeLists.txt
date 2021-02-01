if(NOT WIN32)
    find_package(glfw3 REQUIRED)
    set(TESTING_SOURCES 
        "tests.cpp"
        "attributetest.cpp"
        "modeltest.cpp"
    )
    add_executable(testing ${TESTING_SOURCES})
    target_link_libraries(testing fieldplotter glfw)
endif()
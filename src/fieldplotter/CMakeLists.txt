cmake_minimum_required (VERSION 3.14)


set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.0\\msvc2019_64\\lib\\cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(FRONTEND_SOURCES main.cpp mainwindow.cpp mainwindow.ui optionswindow.cpp optionswindow.ui canvas.cpp useroptions.cpp chargebox.cpp)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_WIN32_EXECUTABLE ON)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(frontend ${FRONTEND_SOURCES})

target_link_libraries(frontend Qt5::Widgets fieldplotter)
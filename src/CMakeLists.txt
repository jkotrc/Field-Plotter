#Top-level CMakeLists for Field_Plotter
cmake_minimum_required (VERSION 3.14)

# See Qt5 wiki

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set (CMAKE_PREFIX_PATH "C:\\Qt\\5.15.0\\msvc2019_64")




#Not adding the header file might break this

set(FIELDPLOTTER_SOURCES Field_Plotter.cpp)
add_executable (Field_Plotter ${FIELDPLOTTER_SOURCES})

add_subdirectory(computation)
add_subdirectory(file)
add_subdirectory(graphics)
add_subdirectory(gui)

find_package(Qt5 REQUIRED Widgets Core Gui)
find_package(OpenGL REQUIRED)


target_link_libraries(Field_Plotter Qt5::Widgets Qt5::Core Qt5::Gui glew32s opengl32)

# TODO: Add tests and install targets if needed.
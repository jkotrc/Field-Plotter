project('fieldplotter', 'cpp',
                        version: '2.0',
                        license: 'MIT')


toplevel_inc = include_directories('include')
project_inc = include_directories('src/fieldplotter', 'src/fieldplotter/extern/imgui')
cxx = meson.get_compiler('cpp')

###DEPENDENCIES###
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')
glfw_dep = dependency('glfw3')
glew_dep = subproject('glew').get_variable('glew_dep')
gl_dep = dependency('GL', method: 'auto')
boost_dep = dependency('boost', modules: ['log', 'thread', 'chrono'])

thread_dep = dependency('threads')

subdir('src/fieldplotter')

#TODO package stuff
# pkg_mod = import('pkgconfig')
# pkg_mod.generate(
# libraries: fieldplotter,
# version: '2.0',
# name : 'libfieldplotter',
# filebase: 'what',
# description : 'OpenGL and Physics backend to FieldPlotter'
# )

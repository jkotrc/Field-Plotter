project('fieldplotter', 'cpp',
                        version: '2.0',
                        license: 'MIT')

#add_global_arguments('-DSOME_TOKEN=value', language: 'cpp')

toplevel_inc = include_directories('include')


###DEPENDENCIES###
# gtest_dep = dependency('gtest', main: true, required: true)
# gmock_dep = dependency('gmock', main: true, required: true)

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')

glfw_dep = dependency('glfw3')
glew_dep = dependency('glew')
gl_dep = dependency('gl', main: true, required: true)


# subdir('include')
subdir('src/libfieldplotter')
subdir('test/libfieldplotter')

test('gtest tests', fieldplotter_test)
# pkg_mod = import('pkgconfig')
# pkg_mod.generate(
# libraries: fieldplotter,
# version: '2.0',
# name : 'libfieldplotter',
# filebase: 'what',
# description : 'OpenGL and Physics backend to FieldPlotter'
# )

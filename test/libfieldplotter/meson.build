fieldplotter_test_sources = [
'main.cpp',
'graphics/line.test.cpp',
'graphics/curve.test.cpp',
]

fieldplotter_test = executable('gtest-all',
fieldplotter_test_sources, dependencies: [
                           glew_dep,gl_dep,glfw_dep,gtest_dep,gmock_dep
], include_directories: fp_inc, link_with: [fieldplotter])
test('gtest tests', fieldplotter_test)

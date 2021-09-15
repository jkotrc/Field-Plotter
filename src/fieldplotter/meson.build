fieldplotter_sources = [
                      'fieldplotter.cpp',
                      'glcontext.cpp',
                      'window.cpp',
                      'renderer.cpp'
]

test_sources = [
                      'test.test.cpp',
                      # 'glcontext.test.cpp',
                      'window.test.cpp',
]

fp_deps = [
                      glew_dep,
                      gl_dep,
                      glfw_dep,
                      thread_dep,
                      boost_dep,
]

fieldplotter = executable('fieldplotter',
                          ['main.cpp',fieldplotter_sources],
                          dependencies: fp_deps,
                          include_directories : [toplevel_inc, project_inc]
                         )

fp_test = executable('gtest-all',
                     [fieldplotter_sources,test_sources],
                     dependencies: [fp_deps,gtest_dep],
                    )

test('gtest test', fp_test)

fieldplotter_sources = [
                      'fieldplotter.cpp',
                      'graphics/renderer.cpp',
                      'graphics/graphics.cpp',
                      'window.cpp',
]

fp_deps = [
                      glew_dep,
                      gl_dep,
                      glfw_dep,
                      thread_dep,
                      boost_dep,
]

fieldplotter = executable('fieldplotter',
                          ['./debug/main-mandelbrot.cpp',fieldplotter_sources],
                          dependencies: fp_deps,
                          include_directories : [toplevel_inc, project_inc]
                         )

fp_test = executable('gtest-all',
                     ['test.test.cpp',fieldplotter_sources],
                     dependencies: [fp_deps,gtest_dep],
                    )

test('gtest test', fp_test)

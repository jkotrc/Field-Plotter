fieldplotter_sources = [
                      'fieldplotter.cpp',
                      'window.cpp',
                      'linalg.h',
                      'components/fieldlines.cpp',
                      'graphics/program.cpp',
                      'graphics/shaders.h',
                      # 'graphics/buffer.cpp',
                      # 'graphics/vao.cpp',
                      # 'graphics/lines.cpp',
                      # 'graphics/renderer.cpp',
                      # 'simulation/simulation.cpp',
                      'physics/electrostatics.cpp',
                      'util/vectors.h', #make this a cpp eventually
                      'util/logging.cpp',
                      'thread.cpp',
]

test_sources = [
                      'test.test.cpp',
                      # 'glcontext.test.cpp',
                      # 'window.test.cpp',
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
                      include_directories : [toplevel_inc, project_inc]
                    )

test('gtest test', fp_test)

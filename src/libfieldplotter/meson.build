fieldplotter_sources = [
'graphics/drawable.cpp',
'graphics/line.cpp',
'graphics/curve.cpp',
'rendering/context.h',
'rendering/frame.cpp',
'vendor/graphics/api.h',
'vendor/graphics/opengl/frame.cpp',
]

fieldplotter = library('fieldplotter',
fieldplotter_sources, dependencies: [
                      glew_dep,gl_dep,glfw_dep
]

)

# foolib = shared_library('foo',
#                         foo_sources,
#                         include_directories : inc,
#                         dependencies : glib_dep,
#                         install : true)

fp_inc = include_directories([
'graphics'
])

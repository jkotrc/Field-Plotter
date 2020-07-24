#pragma once

#include <string>


std::string CONE_VERTEXSHADER =
"#version 400 core\n	\
layout(location = 0) in vec3 vertexPosition_modelspace; \
uniform mat4 MVP; \
void main() {	\
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);	\
}";  

std::string CONE_FRAGMENTSHADER =
"#version 400 core\n \
out vec3 color; \
void main() { \
	color = vec3(1, 0, 0); \
}";
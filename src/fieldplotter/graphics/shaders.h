#ifndef SHADERS_H_
#define SHADERS_H_

#include <string>

std::string HEADER = R"LITERAL(
#version 450 core
)LITERAL";

std::string FRAG_BLACK = HEADER + R"LITERAL(
out vec3 color;
void main(){
  color = vec3(0,0,0);
}
)LITERAL";


std::string VERT_PERSPECTIVE = HEADER + R"LITERAL(
layout(location = 0) in vec3 position;
void main(){
  gl_Position.xyz = position;
gl_Position.w = 1.0;
}
)LITERAL";

std::string VERT_2D = HEADER + R"LITERAL(
layout(location = 0) in vec2 position;
void main(){
  gl_Position.xyz = vec3(position.x, position.y, 0.0);
    gl_Position.w = 1.0;
}
)LITERAL";

#endif // SHADERS_H_

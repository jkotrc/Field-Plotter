#pragma once

#include <string>

namespace Shaders {
const std::string ARROW_VERTEXSHADER =
R"LITERAL(
#version 400 core

//uniform mat4 uProjectionMatrix;
//uniform mat4 uModelviewMatrix;

layout (std140) uniform Matrices {
  mat4 projectionMat;
  mat4 viewMat;
  vec3 cameraPosition;  //TODO: extract this from viewMat instead
};


uniform mat4 modelMat;
uniform float lowerBound;
uniform float upperBound;

layout (location = 0) in vec3 ivPosition;
layout (location = 1) in vec3 ivNormal;
layout (location = 2) in vec3 ivInstanceOffset;
layout (location = 3) in vec3 ivInstanceDirection;

out vec3 lightPosition;
out vec3 vfPosition;
out vec3 vfNormal;
out vec3 vfColor;

mat3 matrixFromDirection(vec3 direction) {
  float c = direction.z;
  //float s = length(direction);
  float s = length(direction.xy);

  if (s == 0.0) {
    s = 1.0;
  }
  float x = -direction.y / s;
  float y = direction.x / s;
  mat3 matrix;
  matrix[0][0] = x*x*(1.0-c)+c;
  matrix[0][1] = y*x*(1.0-c);
  matrix[0][2] = -y*s;
  matrix[1][0] = x*y*(1.0-c);
  matrix[1][1] = y*y*(1.0-c)+c;
  matrix[1][2] = x*s;
  matrix[2][0] = y*s;
  matrix[2][1] = -x*s;
  matrix[2][2] = c;
  return matrix;
}

vec3 colormap(vec3 direction) {
    vec3 color_small = vec3(0.0,0.0,1.0);
    vec3 color_big = vec3(1.0,0.0,0.0);
    return mix(color_small, color_big, (length(direction)-lowerBound)/(upperBound-lowerBound));
}

void main(void) {
    mat4 uModelviewMatrix = viewMat*modelMat;
    lightPosition = (uModelviewMatrix * vec4(cameraPosition, 1.0)).xyz;
    float direction_length = length(ivInstanceDirection);
    vfColor = colormap(ivInstanceDirection);
    mat3 instanceMatrix = 1 * matrixFromDirection(ivInstanceDirection/direction_length);
    vfNormal = (uModelviewMatrix * vec4(instanceMatrix*ivNormal, 0.0)).xyz;
    vfPosition = (uModelviewMatrix * vec4(instanceMatrix*ivPosition+ivInstanceOffset, 1.0)).xyz;
    gl_Position = projectionMat * vec4(vfPosition, 1.0);
}
)LITERAL";



const std::string ARROW_FRAGMENTSHADER =
R"LITERAL(
#version 400 core

//V this should come from the vertex shader
//vec3 lightposition = model_view_matrix * glm::vec4(camera_position, 1.0);


out vec4 fo_FragColor;
in vec3 lightPosition;
//uniform vec3 uLightPosition;
in vec3 vfPosition;
in vec3 vfNormal;
in vec3 vfColor;

void main(void) {
  vec3 normal = normalize(vfNormal);
  vec3 lightDirection = normalize(lightPosition-vfPosition);
  vec3 reflectionDirection = normalize(reflect(lightDirection, normal));
  float specular = 0.2*pow(max(0.0, -reflectionDirection.z), 8.0);
  float diffuse = 0.7*max(0.0, dot(normal, lightDirection));
  float ambient = 0.2;
  fo_FragColor = vec4((ambient+diffuse)*vfColor + specular*vec3(1, 1, 1), 1.0);
}
)LITERAL";

const std::string CHARGE_VERTEXSHADER =
R"LITERAL(
#version 400 core
uniform mat4 MVP;

layout (location=4) in vec4 pos;

void main(void) {
  gl_Position =  MVP * pos;
}
)LITERAL";

const std::string CHARGE_FRAGMENTSHADER =
R"LITERAL(
#version 400 core

out vec3 color;

void main(void) {
  color=vec3(1.0f,1.0f,1.0f);
}
)LITERAL";
}
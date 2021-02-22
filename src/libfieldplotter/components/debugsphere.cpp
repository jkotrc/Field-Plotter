#include <GL/glew.h>

#include "debugsphere.h"
#include "../graphics/graphics.h"
#include "../graphics/shaders.h"
#include "../computation/plottermath.h"
using namespace glm;

#include <string>
using namespace std;

string Dvert =
R"LITERAL(
#version 400 core
layout (std140) uniform Matrices {
  mat4 projectionMat;
  mat4 viewMat;
  vec3 cameraPosition;  //TODO: extract this from viewMat instead
};

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

vec3 instance_position = vec3(0,0,0);
float charge = 1.0;

out float o_charge;
out vec3 lightPosition;
out vec3 Position;
out vec3 Normal;
uniform mat4 modelMat;

void main(void) {
  mat4 uModelviewMatrix = viewMat*modelMat;
  lightPosition = (uModelviewMatrix * vec4(cameraPosition, 1.0)).xyz;
  Normal = (uModelviewMatrix * vec4(normal, 0.0)).xyz;
  Position = (uModelviewMatrix * vec4(vertex+instance_position, 1.0)).xyz;
  o_charge=charge;
  gl_Position = projectionMat * vec4(Position, 1.0);
}
)LITERAL";

string Dfrag =
R"LITERAL(
#version 400 core
out vec4 fo_FragColor;
in vec3 lightPosition;
in vec3 Position;
in vec3 Normal;

//location = 4
in float o_charge;

vec3 colormap(float charge) {
  float saturation=5*charge;
  if (saturation > 1.0) {
    saturation=1.0;
  }
  if(charge < 0){
  return vec3(0,0,1.0);
  }
  return vec3(saturation,0,0);
}

void main() {
  
  vec3 Color=colormap(o_charge);
  //vec3 Color=vec3(1,0,0);

  vec3 normal = normalize(Normal);
  vec3 lightDirection = normalize(lightPosition-Position);
  vec3 reflectionDirection = normalize(reflect(lightDirection, normal));
  float specular = 0.2*pow(max(0.0, -reflectionDirection.z), 8.0);
  float diffuse = 0.7*max(0.0, dot(normal, lightDirection));
  float ambient = 0.2;
  fo_FragColor = vec4((ambient+diffuse)*Color + specular*vec3(1, 1, 1), 1.0);
}
)LITERAL";

DebugSphere::DebugSphere() : m_vao(), m_model(&m_vao) {
    loadSphereModel(m_model);
    m_modelMatrix = mat4(1.0f);
    m_programID = loadShadersFromSource(Dvert, Dfrag);
}

void DebugSphere::updateGraphics() {
}


void DebugSphere::draw() {
    m_vao.bind();
    m_model.ib.bind();
    glUseProgram(m_programID);
    m_parent->getUniforms().bind(m_programID, "Matrices");
    glDrawElements(GL_TRIANGLES, 0, 3,nullptr); // Starting from vertex 0; 3 vertices total -> 1 triangle
}
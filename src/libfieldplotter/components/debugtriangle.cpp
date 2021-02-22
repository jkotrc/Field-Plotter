#include <GL/glew.h>

#include "debugtriangle.h"
#include "../graphics/graphics.h"
#include "../graphics/shaders.h"
#include "../computation/plottermath.h"
using namespace glm;

#include <string>
using namespace std;

string triangle_vert = 
R"LITERAL(
#version 400 core
layout (std140) uniform Matrices {
  mat4 projectionMat;
  mat4 viewMat;
  vec3 cameraPosition;  //TODO: extract this from viewMat instead
};

layout(location = 0) in vec3 VP;

void main(){
    //gl_Position = vec4(VP,1);
    mat4 MVP = projectionMat*viewMat;
    gl_Position = MVP*vec4(VP,1);
}
)LITERAL";

string triangle_frag = 
R"LITERAL(
#version 330 core
out vec3 color;
void main(){
  color = vec3(1,0,0);
}
)LITERAL";

DebugTriangle::DebugTriangle() : m_buf{ GL_STATIC_DRAW }, m_vao() {
    std::vector<Point> vert = {
{-1.0f, -1.0f, 0.0f},
{1.0f, -1.0f, 0.0f},
{0.0f,  1.0f, 0.0f}
    };

    m_buf.setAndAllocateData(&vert[0], vert.size(), (size_t)0);
    VertexAttribute positions = VertexAttribute::create<Point>(0, 0, 0);
    m_vao.addAttribute(positions);
    positions.makePointer();
    m_buf.unbind();

    m_modelMatrix = mat4(1.0f);
    m_programID = loadShadersFromSource(triangle_vert, triangle_frag);
}

void DebugTriangle::updateGraphics() {
    
}


void DebugTriangle::draw() {
    m_vao.bind();
    glUseProgram(m_programID);
    m_parent->getUniforms().bind(m_programID,"Matrices");
    m_buf.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
} 
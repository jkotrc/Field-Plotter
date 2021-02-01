#include "sceneuniforms.h"

using namespace glm;

SceneUniforms::SceneUniforms() {
    m_projection = makePerspective({});
    m_camerapos = {1,1,1};
    m_view = lookAt(m_camerapos,{0,0,0},{0,1,0});
    this->makeBuffer();
}
SceneUniforms::SceneUniforms(int width, int height) {
    m_projectionparams = {};
    m_projectionparams.aspect_ratio = ((float)width)/((float)height);
    m_projection = makePerspective(m_projectionparams);
    m_camerapos = {1,1,1};
    m_view = lookAt(m_camerapos,{0,0,0},{0,1,0});
    this->makeBuffer();
}
SceneUniforms::SceneUniforms(mat4 proj, mat4 view, vec3 campos) 
: m_projection(proj), m_view(view), m_camerapos(campos)
{
    this->makeBuffer();
}
void SceneUniforms::makeBuffer() {
    glGenBuffers(1, &m_bufferID);
    glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4) + sizeof(vec3), NULL, GL_STATIC_DRAW);
    this->update();
}
void SceneUniforms::update() {
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_bufferID);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), glm::value_ptr(m_projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), glm::value_ptr(m_view));
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4), sizeof(vec3), glm::value_ptr(m_camerapos));
}

void SceneUniforms::bind(GLuint programID, std::string name) {
    glUniformBlockBinding(programID, glGetUniformBlockIndex(programID, name.c_str()), 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_bufferID);
}
void SceneUniforms::setModelMatrix(GLuint programID, mat4* matrix) {
    glUniformMatrix4fv(glGetUniformLocation(programID, "modelMat"), 1, false, glm::value_ptr(*matrix));
}
void SceneUniforms::resizeProjection(int x, int y) {
    m_projectionparams.aspect_ratio = ((float)x) / ((float)y);
    m_projection = makePerspective(m_projectionparams);
}
mat4& SceneUniforms::getViewMatrix() {
    return m_view;
}
vec3& SceneUniforms::getCameraPosition() {
    return m_camerapos;
}
GLuint SceneUniforms::getBufferID() {
    return m_bufferID;
}
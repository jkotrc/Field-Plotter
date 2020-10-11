#include <fieldplotter/fieldplotter.h>
#include <fieldplotter/graphics.h>
#include <assert.h>

using namespace glm;

Plottable::Plottable(Model mdl):model(mdl),visible(true),thread_bufferoffset(size_t(0)),thread_buffersize(size_t(0)) {}
Plottable::Plottable() : visible(true),thread_bufferoffset(size_t(0)),thread_buffersize(size_t(0)) {}

void Plottable::initGraphics() {
    buffers.resize(3);

    glGenBuffers(1, &buffers[FP_VERTICES]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[FP_VERTICES]);
    glEnableVertexAttribArray(FP_VERTICES);
    glVertexAttribPointer(FP_VERTICES, 3, GL_FLOAT, false, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(vec3), &model.vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &buffers[FP_NORMALS]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[FP_NORMALS]);
    glEnableVertexAttribArray(FP_NORMALS);
    glVertexAttribPointer(FP_NORMALS, 3, GL_FLOAT, false, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(vec3), &model.normals[0], GL_STATIC_DRAW);

    glGenBuffers(1, &buffers[FP_ELEMENTS]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[FP_ELEMENTS]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(unsigned int), &model.indices[0], GL_STATIC_DRAW);
}

void Plottable::setVisible(bool visible) {
    this->visible=visible;
}
void Plottable::setParent(Scene* parent) {
	this->parent=parent;
}
bool Plottable::isVisible() {
    return visible;
}
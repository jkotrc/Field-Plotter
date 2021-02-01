#include "plottable.h"

void Plottable::setParent(Scene* parent) {
    m_parent = parent;
    parent->getUniforms().bind(m_programID,"Matrices");//uhoh magic number
}

void Plottable::updateUniforms() {
    m_parent->getUniforms().bind(m_programID,"Matrices");
}
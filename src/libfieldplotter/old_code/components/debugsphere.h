#pragma once

#include "plottable.h"
#include "scene.h"
#include "../graphics/model.h"
#include "../graphics/attribute.h"
#include "../graphics/buffers.h"
#include <memory>

class DebugSphere : public Plottable {
public:
    DebugSphere();
    void updateGraphics() override;
protected:
    void draw() override;
private:
    Model m_model;
    VertexArray m_vao;
};
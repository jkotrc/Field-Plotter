#pragma once

#include "plottable.h"
#include "scene.h"
#include "../graphics/attribute.h"
#include "../graphics/buffers.h"
#include <memory>

class DebugTriangle : public Plottable {
    public:
        DebugTriangle();
        void updateGraphics() override;
    protected:
        void draw() override;
    private:
        VertexBuffer m_buf;
        VertexArray m_vao;
        //VertexAttribute<Point> m_buf;
};
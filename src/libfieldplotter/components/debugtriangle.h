#pragma once

#include "plottable.h"
#include "scene.h"
#include "../graphics/attribute.h"
#include <memory>

class DebugTriangle : public Plottable {
    public:
        DebugTriangle();
        bool initGraphics() override;
    protected:
        void draw() override;
    private:
        VertexAttribute<Point> m_buf;
        //std::unique_ptr<VectorBuffer> m_buf;
        GLuint trianglebuf;
};
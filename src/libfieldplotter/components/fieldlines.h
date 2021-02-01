#pragma once

#include <computation/plottermath.h>
#include <components/dynamicobject.h>
#include <graphics/attribute.h>

class FieldLines : public DynamicObject {
    public:
        struct FieldLinesConfig {
            float ds;
            float visible_ds;
            float range;
            int line_density;
        };
        FieldLines(FieldLinesConfig configuration);
        FieldLines();
        ~FieldLines();
        bool initGraphics() override;
        std::vector<Point>& getVertices();
        std::vector<int>& getIndices();
        FieldLinesConfig getConfiguration();
    private:
        FieldLinesConfig m_configuration;
        ReaderWriterQueue<int> m_indexqueue;
        size_t m_buffersize;
        std::vector<int> m_indices;
        VertexAttribute<Point> m_vertexbuffer;
        std::vector<Point> m_vertices;
        void dynamicDraw() override;
        void staticDraw() override;
};
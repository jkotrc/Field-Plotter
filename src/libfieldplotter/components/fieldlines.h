#pragma once

#include <computation/plottermath.h>
#include <components/dynamicobject.h>
#include <graphics/attribute.h>

#include <computation/computation.h>

class FieldLines : public DynamicObject {
    template<typename F, typename... Args> friend class Computation;
    public:
        struct Configuration {
            float ds;
            float visible_ds;
            float range;
            int line_density;
        };
        FieldLines(Configuration configuration);
        FieldLines();
        ~FieldLines();
        std::vector<Point>& getVertices();
        std::vector<int>& getIndices();
        Configuration getConfiguration();
        void configure(const Configuration& newconfig);
    protected:
        void finishComputation();
        bool m_computationDone;
    private:        
        Configuration m_config;
        ReaderWriterQueue<Point> m_vertexqueue;
        ReaderWriterQueue<int> m_indexqueue;
        size_t m_buffersize;//
        std::vector<Point> m_vertices;
        std::vector<int> m_indices;
        VertexAttribute<Point> m_vertexbuffer;
        void dynamicDraw() override;
        void staticDraw() override;
};
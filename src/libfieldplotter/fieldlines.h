#pragma once

//TODO: this might not be necessary
#include "dynamicobject.h"
#include "plottermath.h"


class FieldLines : public DynamicObject {
    public:
        static struct FieldLinesConfig {
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
        std::vector<int> m_indices;
        std::vector<Point> m_vertices;
        void dynamicDraw() override;
        void staticDraw() override;
};
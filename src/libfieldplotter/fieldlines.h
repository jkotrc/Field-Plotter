#pragma once
#include "physicalobject.h"
#include "plottermath.h"

class FieldLines : public PhysicalObject {
    private:
        float range;
        float ds;
        int line_density;
        std::vector<Point> vertices;
        size_t vert_size;
        size_t lineindex_size;
        std::vector<int> lines_index;
        void staticDraw() override;
    public:
        FieldLines(float range, float ds, int line_density);
        ~FieldLines();
        void initGraphics() override;
        float getRange();
        float getLineStep();
        int getLineDensity();
        void updateBuffers() override;

        std::vector<Point>& getVertices();
        std::vector<int>& getLinesIndex();
};
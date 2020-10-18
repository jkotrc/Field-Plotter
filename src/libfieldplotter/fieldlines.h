#pragma once
#include "physicalobject.h"
#include "plottermath.h"

class FieldLines : public PhysicalObject {
    private:
        float range;
        float ds;
        float visible_step;
        int line_density;
        std::vector<Point> vertices;
        size_t vert_size;
        size_t lineindex_size;
        std::vector<int> lines_index;
        void staticDraw() override;
    public:
        FieldLines(float range, float visible_step, float ds, int line_density);
        ~FieldLines();
        void initGraphics() override;
        float getRange();
        float getLineStep();
        float getVisibleStep();
        int getLineDensity();
        void updateBuffers() override;
        void finalizeBuffers() override;
        void clearComputation();

        std::vector<Point>& getVertices();
        std::vector<int>& getLinesIndex();
};
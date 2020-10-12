#pragma once
#include <fieldplotter/commonheaders.h>
#include <fieldplotter/plottable.h>

struct Point;
class FieldLines : public Plottable {
    private:
        float range;
        float ds;
        int line_density;
        std::vector<Point> vertices;
        size_t vert_size;
        size_t lineindex_size;
        std::vector<int> lines_index;
    public:
        FieldLines(float range, float ds, int line_density);
        ~FieldLines();
        float getRange();
        float getLineStep();
        int getLineDensity();
        std::vector<Point>& getVertices();
        std::vector<int>& getLinesIndex();
        void draw() override;
        void initGraphics() override;
        void updateBuffer() override;
};
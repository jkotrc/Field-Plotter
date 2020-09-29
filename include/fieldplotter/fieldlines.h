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
    public:
        FieldLines(float range, float ds, int line_density);
        ~FieldLines();
        float getRange();
        float getLineStep();
        int getLineDensity();
        std::vector<Point>& getVertices();
};
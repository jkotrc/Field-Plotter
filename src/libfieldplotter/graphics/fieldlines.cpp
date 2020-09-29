#include <fieldplotter/fieldlines.h>
#include <fieldplotter/computation.h>

#define PI 3.1415926

/*
FieldLines(float range, float ds, int line_density);
        ~FieldLines();
        float getRange();
        float getLineStep();
        int getLineDensity();
        std::vector<Point>& getVertices();
*/
FieldLines::FieldLines(float range, float ds, int line_density)
: range(range),ds(ds),line_density(line_density)
{
    


    



}

float FieldLines::getRange() {
    return range;
}
float FieldLines::getLineStep() {
    return ds;
}
int FieldLines::getLineDensity() {
    return line_density;
}
std::vector<Point>& FieldLines::getVertices() {
    return vertices;
}
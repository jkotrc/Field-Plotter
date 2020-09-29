#pragma once
#include <fieldplotter/commonheaders.h>
#include <fieldplotter/plottable.h>


class Plottable;
struct PointCharge;
class ChargeSystem : public Plottable {
    private:
        std::vector<PointCharge> pointCharges;
    public:
        void initGraphics();
        void draw() override;
        ChargeSystem(int N, PointCharge* charges);
        PointCharge* getCharges();
        int getN();
        void addCharge(PointCharge& charge, int index);
        void removeCharge(int index);
};
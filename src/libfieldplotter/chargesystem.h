#pragma once
#include "physicalobject.h"
#include "computation.h"

class ChargeSystem : public PhysicalObject {
    private:
        int model_size;
        std::vector<PointCharge> pointCharges;
        void staticDraw();
        void updateBuffers() override {}
    public:
        ChargeSystem();
        ChargeSystem(int N, PointCharge* charges);
        void draw() { staticDraw(); }
        void initGraphics() override;
        PointCharge* getCharges();
        int getN();
        void addCharge(PointCharge& charge, int index);
        void removeCharge(int index);
};
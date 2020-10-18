#pragma once
#include "physicalobject.h"
#include "computation.h"

class ChargeSystem : public PhysicalObject {
    private:
        int model_size;
        std::vector<PointCharge> pointCharges;
        void staticDraw();
        void updateBuffers() override {}
        void finalizeBuffers() override {}
        float ball_radius;
    public:
        ChargeSystem();
        ChargeSystem(int N, PointCharge* charges, float ball_radius);
        void draw() { staticDraw(); }
        void initGraphics() override;
        PointCharge* getCharges();
        int getN();
        void addCharge(PointCharge& charge, int index);
        void removeCharge(int index);
        float getBallRadius();
};
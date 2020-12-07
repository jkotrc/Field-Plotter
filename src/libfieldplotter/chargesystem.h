#pragma once
#include "dynamicobject.h"
#include "computation.h"

struct Model;
struct Point;
class ChargeSystem : public Plottable {
    public:
        ChargeSystem(Scene* parent,std::vector<PointCharge> charges);
        ChargeSystem(Scene* parent);
        void draw() override;
        bool initGraphics() override;
        std::vector<PointCharge> getCharges();
        void addCharge(PointCharge const& charge);
        void removeCharge(int index);
        float getRadius();
    private:
        Model m_model;
        std::vector<Point> m_point;
        std::vector<float> m_charge;
        float m_radius;
};
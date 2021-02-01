#pragma once

#include <graphics/graphics.h>
#include <graphics/model.h>
#include <computation/plottermath.h>
#include <components/dynamicobject.h>

#include <graphics/attribute.h>

class Scene;
class ChargeSystem : public Plottable {
    public:
        ChargeSystem(std::vector<PointCharge> const& charges);
        ChargeSystem();
        void draw() override;
        bool initGraphics() override;
        std::vector<PointCharge> getCharges();
        void addCharge(PointCharge const& charge);
        void removeCharge(int index);
        float getRadius();
    private:
        Model m_model;
        static const int point_index = 3;
        static const int charge_index = 4;
        VertexAttribute<Point> m_pointbuffer;
        VertexAttribute<float> m_chargebuffer;
        std::vector<Point> m_points;
        std::vector<float> m_charges;
        float m_radius;
};
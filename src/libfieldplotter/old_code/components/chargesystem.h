#pragma once


#include <graphics/graphics.h>
#include <graphics/model.h>
#include <computation/plottermath.h>
#include <components/dynamicobject.h>

#include <graphics/attribute.h>
#include <graphics/buffers.h>

class Scene;
class ChargeSystem : public Plottable {
    public:
        ChargeSystem(std::vector<PointCharge> const& charges);
        ChargeSystem();
        void draw() override;
        void updateGraphics() override;
        std::vector<PointCharge> getCharges();
        void addCharge(PointCharge const& charge);
        void removeCharge(int index);
        float getRadius();
        void setRadius(float r);
    private:
        Model m_model;
        static const int point_index = 3;
        static const int charge_index = 4;

        VertexBuffer m_instancesbuffer;
        VertexArray m_vao;
        //VertexAttribute<Point> m_pointbuffer;
        //VertexAttribute<float> m_chargebuffer;
        std::vector<Point> m_points;
        std::vector<float> m_charges;
        float m_radius;
};
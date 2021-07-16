#include "curve.h"

#include <algorithm>


Curve::Curve(std::vector<glm::vec3> const& points)
: m_points(points)
{
    m_selection = std::vector<bool>();
    m_selection.resize(m_points.size());
    std::fill(m_selection.begin(), m_selection.end(), false);
}
Curve::~Curve() {
    delete &m_points;
    delete &m_selection;
}
void Curve::update(std::vector<glm::vec3> const& points) {
    m_points = points;
}
void Curve::draw() {

}
void Curve::select(std::vector<bool> const& selection) {
    m_selection = selection;
}

std::vector<glm::vec3> Curve::getPoints() const {
    return m_points;
}
std::vector<bool> Curve::getSelection() const {
   return m_selection;
}

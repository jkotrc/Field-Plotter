#include "line.h"



Line::Line(glm::vec3 const& from, glm::vec3 const& to)
    : m_from(from), m_to(to), m_selection{false,false}
{

}

Line::~Line() {
    delete &m_from;
    delete &m_to;
}


void Line::update(glm::vec3 const& from, glm::vec3 const& to) {
    m_from=from;
    m_to=to;
}

void Line::select(bool from, bool to) {
    m_selection[0] = from;
    m_selection[1] = to;
}

void Line::draw() {
    //TODO implement a middle-layer renderer
}

 std::array<bool, 2> Line::getSelection() const {
     return {m_selection[0], m_selection[1]};
}

std::array<glm::vec3, 2> Line::getPoints() const {
    return {m_from, m_to};
}

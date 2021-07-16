#ifndef __LINE_H_
#define __LINE_H_

#include "drawable.h"
#include <glm/glm.hpp>
#include <array>

/**
 *This is a simple line from point a to point b on the screen
 **/

class Line : public Drawable {
    public:
        Line(glm::vec3 const& from, glm::vec3 const& to);
        ~Line();
        void update(glm::vec3 const& from, glm::vec3 const& to);
        void select(bool from, bool to);
        void draw() override;
        std::array<bool, 2> getSelection() const;
        std::array<glm::vec3, 2> getPoints() const;
    private:
        glm::vec3 m_from;
        glm::vec3 m_to;
        bool m_selection[2];
};

#endif // __LINE_H_

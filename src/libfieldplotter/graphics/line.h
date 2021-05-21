#ifndef __LINE_H_
#define __LINE_H_

#include "drawable.h"
#include <glm/glm.hpp>
/**
 *This is a simple line from point a to point b on the screen
 **/

class Line : public Drawable {
    public:
        Line(glm::vec2 const& from, glm::vec2 const& to);
        ~Line();
        void update(glm::vec2 const& from, glm::vec2 const& to);
        void draw() override;
    private:
        glm::vec2 m_from;
        glm::vec2 m_to;
};

#endif // __LINE_H_

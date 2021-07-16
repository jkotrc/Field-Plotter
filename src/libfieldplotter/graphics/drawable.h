#ifndef __DRAWABLE_H_
#define __DRAWABLE_H_
#include <glm/glm.hpp>
class Drawable {
    public:
        virtual ~Drawable(){}
        virtual void draw() = 0;
    protected:
        glm::mat4 m_model = glm::mat4(1.0f);
};

#endif // __DRAWABLE_H_

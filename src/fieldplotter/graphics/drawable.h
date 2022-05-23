#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <glm/glm.hpp>

namespace fieldplotter {
    class Drawable {
        public:
            virtual ~Drawable();

            virtual void draw() = 0;

            void setPosition(glm::vec3 const& newpos) {
                position = newpos;
            }

        private:
            glm::vec3 position;
    };
}


#endif // DRAWABLE_H_

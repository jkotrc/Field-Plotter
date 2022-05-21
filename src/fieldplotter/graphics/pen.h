#ifndef PEN_H_
#define PEN_H_

#include <glm/vec3.hpp>
#include <vector>

namespace fieldplotter {
    class Pen {
        public:
            Pen();
            void down();
            void up();
            void move(glm::vec3 const & pos);

        private:
            std::vector<std::vector<glm::vec3>> points;
            std::vector<glm::vec3> line;
            bool penDown;
    };
}


#endif // PEN_H_

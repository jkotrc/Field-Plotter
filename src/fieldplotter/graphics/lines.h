#ifndef LINES_H_
#define LINES_H_

#include "vao.h"
#include "buffer.h"
#include <string>
#include <glm/glm.hpp>

namespace fieldplotter {
    class Lines : public VAO {
        public:
            Lines(std::vector<glm::vec2> lines);
            void bind() override;
            void draw() override;
        private:
            Buffer gldata;
            std::vector<glm::vec2> lines;

    };
}

#endif // LINES_H_

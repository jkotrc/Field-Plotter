#include "lines.h"

using namespace fieldplotter;

Lines::Lines(std::vector<glm::vec2> lines) : VAO(), gldata(Buffer(BUFFER_VERTEX, GL_STATIC_DRAW)) {
    gldata.loadVertices(lines.size(), &lines[0]);
}

void Lines::bind() {
    VAO::bind();

}

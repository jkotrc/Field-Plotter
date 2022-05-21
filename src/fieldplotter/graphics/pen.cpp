#include "pen.h"

using namespace fieldplotter;

#include <assert.h>

Pen::Pen() : penDown(false) {
    line.push_back({0.0f,0.0f,0.0f});
}

void Pen::down() {
    penDown = true;
}

void Pen::up() {
    penDown = false;
    glm::vec3 pos = line.back();

    if (line.size() > 1) {
        points.push_back(line);
        line.clear();
    }

    if (line.size() == 0) {
        line.push_back(pos);
    }
}

void Pen::move(glm::vec3 const & pos) {
    if (penDown) {
        line.push_back(pos);
    } else {
        assert (line.size() == 1);
    }
}

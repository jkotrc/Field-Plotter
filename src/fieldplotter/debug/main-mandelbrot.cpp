#include <iostream>

#include "fieldplotter.h"

#include "graphics/glcontext.h"

using namespace fieldplotter;

int main() {
    FieldPlotter instance;
    std::shared_ptr<Graphics> graphics = instance.getGraphics().lock();

    return 0;
}

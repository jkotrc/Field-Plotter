#include <iostream>

#define PI 3.141592653

#include "fieldplotter.h"

using namespace fieldplotter;

bool running = true;

void onEvent(Event const& e) {
    if (e.getName() == "WindowCloseEvent") {
        running = false;
    }
}

//density is 3 globally
int main() {
    FieldPlotter fp;
    return fp.run();
}

#include "fieldplotter.h"

#include <iostream>

using namespace fieldplotter;

FieldPlotter::FieldPlotter() {
    m_running = true;
    m_minimized = false;
}

FieldPlotter::~FieldPlotter() {
    m_running=false;
}

void FieldPlotter::run() {
    std::cout << "There is still an event system needed for a first run\n";
    // Window win;
    // win.show();
    m_running = false;
}

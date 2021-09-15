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

void FieldPlotter::onEvent(Event const& e) {
    //TODO propagate event into its respective layers using a dispatcher
    if (e.getName() == "KeyPressEvent") {
        std::cout << "You have pressed the key with code: " << static_cast<KeyPressEvent const&>(e).key << "\n";
    } else if (e.getName() == "WindowCloseEvent") {
        m_running = false;
    }
}

void FieldPlotter::run() {
    Window win;
    Renderer ren(win.getContext());

    win.setEventCallback(std::bind(&FieldPlotter::onEvent, this, std::placeholders::_1));

    while (m_running) {
        ren.render();
        win.update();
    }
    std::cout << "Goodbye\n";
}

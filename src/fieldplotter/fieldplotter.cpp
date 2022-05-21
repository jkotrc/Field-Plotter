#include "fieldplotter.h"

#include <GL/glew.h>
#include <iostream>

using namespace fieldplotter;

FieldPlotter::FieldPlotter() {
    running = true;
    minimized = false;
    INSTANCE = this;
}

FieldPlotter::~FieldPlotter() {
    running=false;
}

void FieldPlotter::onEvent(Event const& e) {
    //TODO propagate event into its respective layers using a dispatcher
    if (e.getName() == "KeyPressEvent") {
        std::cout << "You have pressed the key with code: " << static_cast<KeyPressEvent const&>(e).key << "\n";
    } else if (e.getName() == "WindowCloseEvent") {
        INSTANCE->running = false;
    } else if (e.getName() == "WindowErrorEvent") {
        WindowErrorEvent* event = (WindowErrorEvent*) &e;
        INSTANCE->running = false;
        std::cout << "Window error occured. Error Code " << event->getErrorCode() << ", message:\n" << event->getDescription();
    }
}

int FieldPlotter::run() {
    Window win;

    // win.setEventCallback(std::bind(&FieldPlotter::onEvent, this, std::placeholders::_1));
    win.setEventCallback(boost::bind(&FieldPlotter::onEvent, boost::placeholders::_1));

    while (running) {
        glClear(GL_COLOR_BUFFER_BIT);

        win.update();
    }

    return 0;
}

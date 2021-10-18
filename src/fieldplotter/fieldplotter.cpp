#include "fieldplotter.h"

#include <iostream>
#include <chrono>

using namespace fieldplotter;
using namespace std::chrono_literals;
using namespace std::chrono;

FieldPlotter::FieldPlotter() /* : m_running(true), m_minimized(false), m_window(800,600), m_context(m_window)*/ {
    m_running = true;
    m_minimized = false;
    m_window = std::unique_ptr<Window>(new Window(800,600));
    m_context = std::unique_ptr<OpenGLContext>(new OpenGLContext(*m_window));
    m_window->setEventCallback(std::bind(&FieldPlotter::onEvent, this, std::placeholders::_1));
    m_window->show();
}

FieldPlotter::~FieldPlotter() {
    m_running=false;
}

void FieldPlotter::run() {
    std::cout << "Starting main loop\n";
    while (m_running) {
        std::shared_ptr<Graphics> graphics = m_context->getGraphics().lock();
        if (graphics)
            graphics->clear();
        update();
    }
    std::cout << "Goodbye...";
}

void FieldPlotter::update() {
    m_window->update();
}

void run(int seconds) {}

void FieldPlotter::onEvent(Event const& e) {
    //TODO propagate event into its respective layers using a dispatcher
    if (e.getName() == "KeyPressEvent") {
        std::cout << "You have pressed the key with code: " << static_cast<KeyPressEvent const&>(e).key << "\n";
    } else if (e.getName() == "WindowCloseEvent") {
        m_running = false;
    }
}

std::weak_ptr<Graphics> FieldPlotter::getGraphics() const {
    return m_context->getGraphics();
}

void FieldPlotter::close() {}
void FieldPlotter::renderToPicture(std::string path) {}

#include "core.h"
#include "event/event.h"
#include "event/windowevent.h"
#include "extern/imgui/backends/imgui_impl_glfw.h"
#include "extern/imgui/imgui.h"
#include "graphics/glgraphics.h"
#include "window.h"

#include <GLFW/glfw3.h>
#include <boost/log/trivial.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <memory>
#include <stdexcept>

using namespace fieldplotter;


void epicCallback(int code, const char* desc) {
        std::cout << "Window Error: Error Code " << code << ", message:\n" << desc;
}

Window::Window() {
    WindowOptions options;
    width = options.width;
    height = options.height;
    title = options.title;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    //(void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable

ImGui::StyleColorsDark();
    if (glfwInit() != GLFW_TRUE) {
        DEBUG_ERR("Failed to create GLFW");
        throw "Failed to create GLFW Instance";
    }

    //this shit does not work
    // boost::function<void(int, const char*)> callback = boost::bind(&Window::errorCallback, this, _1, _2);
    // glfwSetErrorCallback(*callback.target<GLFWerrorfun>());
    glfwSetErrorCallback(epicCallback);

    handle = glfwCreateWindow(width, height, options.title.c_str(), NULL, NULL);

    if (handle == nullptr) {
        DEBUG_ERR("Failed to create window!");
        throw "Failed to create window!";
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 5);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetWindowUserPointer(handle, reinterpret_cast<void*>(this));
// #ifdef debug
    // glfwSetWindowAttrib(handle, GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
// #endif

    glfwSetKeyCallback(handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Window* instance = (Window*) glfwGetWindowUserPointer(window);
        instance->onEvent(KeyPressEvent{key,action,mods});
    });
    glfwSetCursorPosCallback(handle, [](GLFWwindow* window, double xpos, double ypos){
        Window* instance = (Window*) glfwGetWindowUserPointer(window);
        vec2d newpos = {xpos, ypos};
        printf("setpos %f %f\n", xpos, ypos);
        instance->mousevel = newpos - instance->mousepos;
        instance->mousepos = newpos;
        instance->onEvent(MouseMoveEvent(xpos, ypos));
    });
    glfwSetMouseButtonCallback(handle, [](GLFWwindow* window, int button, int action, int mods){
        Window* instance = (Window*) glfwGetWindowUserPointer(window);
        ImGuiIO& io = ImGui::GetIO();
        if (!io.WantCaptureMouse) {
            if (action == GLFW_PRESS) {
                instance->mousebuttons.insert(button);
            } else if (action == GLFW_RELEASE) {
                instance->mousebuttons.erase(button);
            }
            instance->onEvent(MouseButtonEvent(button, action, mods));
        }
    });

    glfwSetWindowCloseCallback(handle, [](GLFWwindow* window) {
        Window* instance = (Window*) glfwGetWindowUserPointer(window);
        instance->onEvent(WindowCloseEvent{});
    });

    glfwMakeContextCurrent(handle);

    glewExperimental = true;

    GLenum status = glewInit();
    if (status != GLEW_OK) {
        DEBUG_ERR("Glew init failed");
        printf("Code: %d\n", status);
        //some sort of crash event?
        throw std::runtime_error("GLEW failed to initalize");
    }
    graphics = std::unique_ptr<OpenGLGraphics>(new OpenGLGraphics());
    ImGui_ImplGlfw_InitForOpenGL(handle, true);
    ImGui_ImplOpenGL3_Init();

}

void Window::onEvent(Event const& event) {
    ImGuiIO& io = ImGui::GetIO();
    bool blockAppEvents = ((io.WantCaptureKeyboard || io.WantTextInput) && (event.getCategories() & KeyboardEvent)) \
                       || (io.WantCaptureMouse && (event.getCategories() & MouseEvent));

    if (!blockAppEvents) { //TODO move check to callbacks
        event_callback(event);
    }
}

void Window::errorCallback(int code, const char* desc) {
        std::cout << "EVENT\n";
        this->onEvent(WindowErrorEvent{code, std::string(desc)});
}

Window::~Window() {
    this->close();
    glfwDestroyWindow(handle);
    glfwTerminate();
}

void Window::show() {
    //TODO onShowEvent
    glfwGetCursorPos(handle, &mousepos[0], &mousepos[1]);
    glfwShowWindow(handle);
}

void Window::hide() {
    //TODO onHideEvent
    glfwHideWindow(handle);
}

void Window::update() {
    glfwPollEvents();
    draw();
}

void Window::close() {
    glfwSetWindowShouldClose(handle, GLFW_TRUE);
}

void Window::draw() {
    graphics->update();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    int w,h;
    glfwGetFramebufferSize(handle, &w, &h);
    glViewport(0, 0, w, h);
    glfwSwapBuffers(handle);
}

int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}

bool Window::isClosed() const {
    return closed;
}

vec2d Window::getMousePosition() const {
    return mousepos;
}
vec2d Window::getMouseVelocity() const {
    return mousevel;
}

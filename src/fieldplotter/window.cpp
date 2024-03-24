#include "core.h"
#include "extern/imgui/backends/imgui_impl_glfw.h"
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
ImGuiIO &io = ImGui::GetIO();
(void)io;
// io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable
// Keyboard Controls io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //
// Enable Gamepad Controls

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
        switch(action) {
            case GLFW_PRESS:
                instance->onEvent(KeyPressEvent{key,mods}); //does KeyPressEvent go out of scope?
                break;
            case GLFW_RELEASE:
                instance->onEvent(KeyReleaseEvent{key,mods});
                break;
            case GLFW_REPEAT:
                instance->onEvent(KeyReleaseEvent{key,mods});
                break;
            default:
                throw "GLFW gave an unknown keycode...";
                break;
        }
    });
    glfwSetCursorPosCallback(handle, [](GLFWwindow* window, double xpos, double ypos){

    });
    glfwSetMouseButtonCallback(handle, [](GLFWwindow* window, int button, int action, int mods){

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
    ImGui_ImplGlfw_InitForOpenGL(handle, false); //TODO false and pass events self
    ImGui_ImplOpenGL3_Init();

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


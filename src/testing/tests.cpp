#include <gtest/gtest.h>

#include <components/scene.h>
#include <components/chargesystem.h>
#include <components/fieldlines.h>
#include <components/debugtriangle.h>
#include <graphics/renderer.h>

#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

#define SENSITIVITY 0.01f

GLFWwindow* window;
Scene* scene;
Renderer* renderer;
bool lmbPressed = false;
bool altPressed = false;
float xHistory;
float yHistory;

#define SCROLL_SENSITIVITY -0.1f

template <typename T> float sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void APIENTRY glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    scene->getCamera().scroll(sgn(yoffset) * SCROLL_SENSITIVITY);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_LEFT_ALT) {
        if (GLFW_PRESS) {
            altPressed = true;
        }
        else if (GLFW_RELEASE) {
            altPressed = false;
        }
    }
    switch (key) {
    case(GLFW_KEY_W):
        scene->getCamera().moveLinear(0.1f, 0.0f, 0.0f);
        break;
    case(GLFW_KEY_S):
        scene->getCamera().moveLinear(-0.1f, -0.0f, 0.0f);
        break;
    case(GLFW_KEY_A):
        scene->getCamera().moveLinear(0.0f, 0.0f, -0.1f);
        break;
    case(GLFW_KEY_D):
        scene->getCamera().moveLinear(0.0f, 0.0f, 0.1f);
        break;
    case(GLFW_KEY_R):
        scene->getCamera().moveLinear(0.0f, -0.1f, 0.0f);
        break;
    case(GLFW_KEY_F):
        scene->getCamera().moveLinear(0.0f, 0.1f, 0.0f);
        break;
    case(GLFW_KEY_UP):
        scene->getCamera().moveCamera(0.0f, 0.1f);
        break;
    case(GLFW_KEY_DOWN):
        scene->getCamera().moveCamera(0.0f, -0.1f);
        break;
    case(GLFW_KEY_LEFT):
        scene->getCamera().moveCamera(0.1f, 0.0f);
        break;
    case(GLFW_KEY_RIGHT):
        scene->getCamera().moveCamera(-0.1f, 0.0f);
        break;
    default:
        break;
    }
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (lmbPressed) {
        const float dx = SENSITIVITY * ((float)xpos - xHistory);
        const float dy = SENSITIVITY * ((float)ypos - yHistory);
        scene->getCamera().moveCamera(-dx, dy);
    }
    xHistory = (float)xpos;
    yHistory = (float)ypos;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        lmbPressed = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        lmbPressed = false;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    renderer->resizeScreen(width, height);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc,argv);

    if (!glfwInit()) {
        cout << "GLFW FAILED TO INITIALIZE\n";
        exit(-1);
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    GLenum glewinitialized = glewInit();
    if (glewinitialized != GLEW_OK) {
        cout << "GLEW FAILED TO INITIALIZE!\n";
    }
    
      
    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    } else {
        std::cout << "Oh shit\n";
    }

    std::vector<PointCharge> sample_charges;
    sample_charges.push_back(PointCharge({1.5f,1.5f,1.5f},-0.1f));
    sample_charges.push_back(PointCharge(Point(0.0f, 0.0f, 0.5f),0.1f));
    sample_charges.push_back(PointCharge(Point(0.0f, 0.0f, -0.5f),-0.1f));
    sample_charges.push_back(PointCharge(Point(0.0f, 0.5f, 0.0f),0.1f));
   
    scene = new Scene(800, 600);
    renderer = new Renderer(scene);
    renderer->initGraphics();
    ChargeSystem* testSphere = new ChargeSystem(sample_charges);
    DebugTriangle* tri = new DebugTriangle();
    testSphere->initGraphics();
    tri->initGraphics();
    tri->setParent(scene);
    testSphere->setParent(scene);


    renderer->addObject(tri);
    renderer->addObject(testSphere);

    
    while (!glfwWindowShouldClose(window)) {
        renderer->render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return RUN_ALL_TESTS();
}
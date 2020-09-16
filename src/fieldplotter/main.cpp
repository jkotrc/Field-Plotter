#include <fieldplotter/fieldplotter.h>

#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

GLFWwindow* window;
Scene* renderer;
VectorField* debug_vectorfield;
bool lmbPressed = false;
bool altPressed = false;
float xHistory;
float yHistory;

#define SCROLL_SENSITIVITY -0.1f

template <typename T> float sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

    renderer->getCamera()->scroll(sgn(yoffset)*SCROLL_SENSITIVITY);
}

float debmove=0.01f;
/*
    singlecharge[0] = PointCharge(Point(0.0f, 0.0f, 0.4f), -1);
    singlecharge[1] = PointCharge(Point(0.4f, 0.0f, 0.0f), -1);
    singlecharge[2] = PointCharge(Point(0.0f, 0.1f, 0.0f), 1);
*/
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
        switch(key) {
            case(GLFW_KEY_W):
            renderer->getCamera()->moveLinear(0.1f,0.0f,0.0f);
            break;
            case(GLFW_KEY_S):
            renderer->getCamera()->moveLinear(-0.1f,-0.0f,0.0f);
            break;
            case(GLFW_KEY_A):
            renderer->getCamera()->moveLinear(0.0f,0.0f,-0.1f);
            break;
            case(GLFW_KEY_D):
            renderer->getCamera()->moveLinear(0.0f,0.0f,0.1f);
            break;
            case(GLFW_KEY_R):
            renderer->getCamera()->moveLinear(0.0f,-0.1f,0.0f);
            break;
            case(GLFW_KEY_F):
            renderer->getCamera()->moveLinear(0.0f,0.1f,0.0f);
            break;
            case(GLFW_KEY_UP):
            renderer->getCamera()->moveCamera(0.0f,0.1f);
            break;
            case(GLFW_KEY_DOWN):
            renderer->getCamera()->moveCamera(0.0f,-0.1f);
            break;
            case(GLFW_KEY_LEFT):
            renderer->getCamera()->moveCamera(0.1f,0.0f);
            break;
            case(GLFW_KEY_RIGHT):
            renderer->getCamera()->moveCamera(-0.1f,0.0f);
            break;
            // case(GLFW_KEY_P):
            // c.charges[2].p.y+=debmove;
            // compute_electric_field(debug_vectorfield, c);
            // renderer->updateVectorField();
            // break;
            default:
            break;
        }
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        lmbPressed=true;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        lmbPressed=false;
    }
}
#define SENSITIVITY 0.01f
void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)  
{
    if (lmbPressed) {
        const float dx = SENSITIVITY*((float)xpos-xHistory);
        const float dy = SENSITIVITY*((float)ypos-yHistory);
        renderer->getCamera()->moveCamera(-dx,dy);
    }
    xHistory=(float)xpos;
    yHistory=(float)ypos;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	renderer->resizeViewport(width,height);
    //glViewport(0, 0, width, height);
}


#define FP_MAINMETHOD
#ifndef FP_MAINMETHOD

#else

const int N = 3;
PointCharge* singlecharge;
int main() {
    cout << "Starting...\n";
    
    cout << "VectorField made\n";
    if (!glfwInit()) {
        cout << "GLFW FAILED TO INITIALIZE\n";
        exit(-1);
    }
    cout << "GLFW Initialized\n";
    glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"Test",NULL,NULL);
    cout << "window made\n";
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glewExperimental=GL_TRUE;
    GLenum glewinitialized = glewInit();
    if (glewinitialized != GLEW_OK) {
        cout << "GLEW FAILED TO INITIALIZE!\n";
    }
    cout << "GLEW initialized.. Instantiating renderer\n";

    debug_vectorfield = new VectorField(0.2f,10);//separation,dimension
    //PhysicsConfiguration c;

    singlecharge = new PointCharge[N];
    singlecharge[0] = PointCharge(Point(0.0f, 0.0f, 0.4f), -1);
    singlecharge[1] = PointCharge(Point(0.4f, 0.0f, 0.0f), -1);
    singlecharge[2] = PointCharge(Point(0.0f, 0.0f, 0.0f), 1);
    //c.charges=singlecharge;
    //c.n_charges = N;

    

    //compute_electric_field(debug_vectorfield, c);
    
    printf("bounds: (%f,%f)\n", debug_vectorfield->getLowerBound(), debug_vectorfield->getUpperBound());
    cout << "Making Scene\n";

    renderer = new Scene(800,600);
    renderer->addPlottable(debug_vectorfield);
    
    cout << "Beginning render loop\n";
    while(!glfwWindowShouldClose(window)){
        renderer->render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}
#endif
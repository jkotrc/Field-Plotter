#define GLEW_STATIC
#include <GL/glew.h>

#include <fieldplotter/scene.h>

#include <fieldplotter/vectorfield.h>
#include <fieldplotter/chargesystem.h>
#include <fieldplotter/fieldlines.h>

#include <QApplication>
#include "mainwindow.h"

#include <iostream>
using namespace std;

Scene* renderer;
VectorField* debug_vectorfield;
bool lmbPressed = false;
bool altPressed = false;
float xHistory;
float yHistory;

//TODO: Set this in the preferences
#define SCROLL_SENSITIVITY -0.1f

const int N = 3;
PointCharge* singlecharge;
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    return app.exec();

    /*if (!glfwInit()) {
        cout << "GLFW FAILED TO INITIALIZE\n";
        exit(-1);
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    GLenum glewinitialized = glewInit();

    singlecharge = new PointCharge[N];
    singlecharge[0] = PointCharge(Point(0.0f, 0.0f, 0.5f), 0.1f);
    singlecharge[1] = PointCharge(Point(0.0f, 0.0f, -0.5f), -0.1f);
    singlecharge[2] = PointCharge(Point(0.0f, 0.5f, 0.0f), 0.1f);

    ChargeSystem* testSphere = new ChargeSystem(N, singlecharge);
    debug_vectorfield = new VectorField(0.2f, 10);//separation,dimension

    FieldLines* testLine = new FieldLines(4.0f, 0.2f, 4);
    
    Computation<FieldLines> comp(*testLine,*testSphere,compute_field_lines);
    std::thread computationThread = comp.spawnThread();

    renderer = new Scene(800, 600);
    renderer->addPlottable(testSphere);
    renderer->addPlottable(testLine);

    while(!glfwWindowShouldClose(window) && !comp.isComplete()) {
        testLine->updateBuffer();
        renderer->render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    testLine->updateBuffer();//catch any potential missing vertices
    computationThread.detach();
    
    while (!glfwWindowShouldClose(window)) {
        renderer->render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }*/

    
}

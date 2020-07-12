#include "GraphicsCanvas.h"

#include "../graphics/Renderer.h"

//For debugging purposes
#include <iostream>

#include <qtimer.h>

using namespace Ui;

//call super constructor QOpenGLWidget(parent)
Canvas::Canvas(QWidget* parent)
	: QOpenGLWidget(parent) 
{
	this->renderer = new Renderer();
	
}

void Canvas::initializeGL() {
	std::cout << "Initializing GLEW\n";
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Failed to initialize GL!\n";
	}
	else {
		std::cout << "GL initialized\n";
	}

	glClearColor(0, 0, 0.2, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	QTimer* aTimer = new QTimer();
	connect(aTimer, SIGNAL(timeout()), SLOT(update()));
	aTimer->start(30);
}
void Canvas::resizeGL(int w, int h) {
	std::cout << "Not yet implemented!\n";
}



void Canvas::paintGL() {
	renderer->tempRender();
}

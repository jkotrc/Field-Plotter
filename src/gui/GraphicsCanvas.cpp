#include "GraphicsCanvas.h"

#include "../graphics/Renderer.h"
#include "../graphics/Camera.h"

//For debugging purposes
#include <iostream>

#include <qevent.h>

using namespace Ui;


#define ROLLSPEED 0.1F	//later set this in preferences


//last time 800 by 500 worked
#define DEBUGWIDTH 1000
#define DEBUGHEIGHT 1000

//call super constructor QOpenGLWidget(parent)
Canvas::Canvas(QWidget* parent)
	: QOpenGLWidget(parent) 
{
	this->renderer = new Renderer();

	//this->camera = new Camera(parent->width(), parent->height(), ROLLSPEED, true, true);
	this->camera = new Camera(DEBUGWIDTH, DEBUGHEIGHT, ROLLSPEED, true, true);
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
	renderer->initGL();

	//Why would the rendering and GUI go on different threads? That's stupid
	//QTimer* aTimer = new QTimer();
	//connect(aTimer, SIGNAL(timeout()), SLOT(update()));
	//aTimer->start(30);
}


void Canvas::resizeGL(int w, int h) {
	std::cout << "Not yet implemented!\n";
}

void Canvas::paintGL() {
	renderer->tempRender();
}

#include <stdio.h>
void print(glm::mat4 matrix) {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++)
			printf("%+02.2f ", matrix[i][j]);
		printf("\n");
	}
}


void Ui::Canvas::mousePressEvent(QMouseEvent* event)
{
	const int x = event->x();
	const int y = event->y();

	printf("MOUSEPRESSEVENT: \n");
	
	prevModel = *renderer->getModel();
	prevView = *renderer->getView();
	printf("PREVVIEW: \n");
	print(prevView);

	camera->setPrevPos(camera->toScreenCoord(x, y));
	update();
}

void Ui::Canvas::mouseReleaseEvent(QMouseEvent* event)
{
	camera->setPrevPos(camera->getCurrentPos());
	update();
}

void Ui::Canvas::mouseMoveEvent(QMouseEvent* event)
{
	const int x = event->x();
	const int y = event->y();
	vec3 coords = camera->toScreenCoord(x, y);
	camera->setCurrentPos(coords);
	
	mat4 rotation = camera->createViewRotationMatrix();
	mat4 view = prevView * rotation;
	mat4 model = prevModel * camera->createModelRotationMatrix(prevModel);

	renderer->setModel(model);
	renderer->setView(view);
	update();
}



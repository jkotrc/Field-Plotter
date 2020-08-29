#include "GraphicsCanvas.h"
#include "../Debug.h"

#include <qevent.h>

using namespace Ui;

Canvas::Canvas(QWidget* parent)
	: 
	QOpenGLWidget(parent)
{

}

void Canvas::initializeGL() {
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		Debug::debugString("GraphicsCanvas","Failed to initialize GL!");
	}
	else {
		Debug::debugString("GraphicsCanvas", "GL initialized");
	}

	glClearColor(0, 0, 0.2, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	renderer = new Renderer();
}


void Canvas::resizeGL(int w, int h) {
	Debug::debugString("GraphicsCanvas", "Resizing not yet implemented!");
}

void Canvas::paintGL() {
	renderer->render();
}


void Ui::Canvas::mousePressEvent(QMouseEvent* event)
{
	const int x = event->x();
	const int y = event->y();
	renderer->getCamera()->grabCamera(x, y);
	update();
}

void Ui::Canvas::mouseMoveEvent(QMouseEvent* event)
{
	const int x = event->x();
	const int y = event->y();
	renderer->getCamera()->moveCamera(x, y);
	update();
}

void Ui::Canvas::mouseReleaseEvent(QMouseEvent* event)
{
	renderer->getCamera()->releaseCamera();
	update();
}
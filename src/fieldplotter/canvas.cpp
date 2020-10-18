#define GLEW_STATIC
#include <GL/glew.h>
#include "canvas.h"

#include <libfieldplotter/scene.h>
#include <libfieldplotter/physicalobject.h>


#include <iostream>


Canvas::Canvas(QWidget* parent)
	: QOpenGLWidget(parent), lmbPressed(false)
{
	this->setMouseTracking(true);
	this->setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);
	assert(this->hasMouseTracking());
}

Scene* Canvas::getScene() {
	return renderer;
}


void Canvas::initializeGL() {
	QOpenGLWidget::initializeGL();
	this->renderer = new Scene(width(), height());
	emit glReady();
}


void Canvas::resizeGL(int w, int h) {
	renderer->resizeViewport(w, h);
}
void Canvas::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		lmbPressed = true;
	}
	update();
}
#define SENSITIVITY 0.01f
void Canvas::wheelEvent(QWheelEvent* event) {
	int i_delta = 0;
	i_delta = event->delta();
	float delta = 0.1f * SENSITIVITY * i_delta;
	renderer -> scroll(-delta);
	update();
}
void Canvas::mouseMoveEvent(QMouseEvent* event) {
	int x = 0;
	int y = 0;
	x = event->x();
	y = event->y();
	float xpos = (float)x;
	float ypos = (float)y;
	if (lmbPressed) {
		float dx = SENSITIVITY * (xpos - xHistory);
		float dy = SENSITIVITY * (ypos - yHistory);
		renderer->moveCamera(-dx, dy);
	}
	xHistory = xpos;
	yHistory = ypos;
	update();
}
void Canvas::mouseReleaseEvent(QMouseEvent* event) {
	lmbPressed = false;
	update();
}
void Canvas::paintGL() {
	renderer->draw();
	this->update();
}
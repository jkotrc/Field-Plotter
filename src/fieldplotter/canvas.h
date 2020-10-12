#pragma once

#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QWidget>
#include <QMouseEvent>

#include <fieldplotter/physicalobject.h>
#include <fieldplotter/computation.h>
class Scene;
class Canvas : public QOpenGLWidget {
protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
private:
	Scene* renderer;
	bool lmbPressed;
	float xHistory;
	float yHistory;
	std::vector<PhysicalObject*> plottables;
	std::vector<int> visible;
	std::vector<int> running;

public:
	Canvas(QWidget* parent = 0);
	template <typename T> void startComputation(Computation<T>& comp);
};
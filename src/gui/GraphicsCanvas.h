#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QWidget>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>

#include "../graphics/Renderer.h"
#include "../graphics/Camera.h"


namespace Ui {
	using namespace glm;
	class Canvas : public QOpenGLWidget {
	public:
		Canvas(QWidget* parent = 0);
		Renderer* renderer;
		Camera* camera;
		mat4 prevModel;
		mat4 prevView;
	protected:
		void initializeGL() override;
		void resizeGL(int w, int h) override;
		void paintGL() override;

		void mousePressEvent(QMouseEvent* event) override;
		void mouseReleaseEvent(QMouseEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;
	};
}
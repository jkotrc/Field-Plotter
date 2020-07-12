#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/GLU.h>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QWidget>

namespace Ui {
	class Canvas : public QOpenGLWidget {
	public:
		Canvas(QWidget* parent = 0);
		//~Canvas();
	protected:
		void initializeGL() override;
		void resizeGL(int w, int h) override;
		void paintGL() override;
	};
}
#pragma once
#include "scene.h"
#define GLEW_STATIC
#include <gl/glew.h>
#include <vector>

class Plottable {
public:
	static enum ModelBufferDesc {
		FP_VERTICES = 0,
		FP_NORMALS,
		FP_ELEMENTS
	};
	virtual bool initGraphics() = 0;
	virtual void draw() = 0;
	void setParent(Scene* parent) { m_parent = parent; }
protected:
	bool m_graphicsInitialized{false};
	Scene* m_parent;
	glm::mat4 m_modelMatrix{1.0f};
	std::vector<GLuint> m_buffers;
	GLuint m_programID;
};
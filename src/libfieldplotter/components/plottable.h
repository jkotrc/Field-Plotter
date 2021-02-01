#pragma once
#include "scene.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <map>

#include <graphics/attribute.h>

class Plottable {
public:
	virtual bool initGraphics() = 0;
	virtual void draw() = 0;
	void setParent(Scene* parent);
protected:
	void updateUniforms();
	bool m_graphicsInitialized{false};
	Scene* m_parent;
	glm::mat4 m_modelMatrix;
	GLuint m_programID;
};
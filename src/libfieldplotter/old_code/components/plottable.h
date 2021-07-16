#pragma once
#include "scene.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <map>

#include <graphics/attribute.h>

class Plottable {
public:
	virtual void updateGraphics() = 0;
	virtual void draw() = 0;
	void setParent(Scene* parent);
protected:
	Scene* m_parent;
	glm::mat4 m_modelMatrix{ 1.0f };
	GLuint m_programID;
};
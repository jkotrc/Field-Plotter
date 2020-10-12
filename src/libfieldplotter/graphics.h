#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "plottermath.h"
#include <vector>
#include <string>

struct Model {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
};

enum Plottable_Buffers {
	FP_VERTICES=0,
	FP_NORMALS,
	FP_ELEMENTS,
};

GLuint loadShadersFromSource(std::string vertex_source, std::string fragment_source);
Model loadArrowModel();
Model loadSphereModel();
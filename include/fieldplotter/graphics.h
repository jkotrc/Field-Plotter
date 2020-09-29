#pragma once
#include <fieldplotter/commonheaders.h>

GLuint loadShadersFromSource(std::string vertex_source, std::string fragment_source);


struct Model {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
};


Model loadArrowModel();
Model loadSphereModel();

enum Plottable_Buffers {
	FP_VERTICES=0,
	FP_NORMALS,
	FP_ELEMENTS,
};
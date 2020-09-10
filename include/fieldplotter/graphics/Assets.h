#pragma once
//Utility file for loading shaders and models
#include <GL/glew.h>

#include <vector>
#include <string> 
#include <fstream>
#include <sstream>

typedef struct Model {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
} Model;


GLuint loadShadersFromSource(std::string vertex_source, std::string fragment_source);


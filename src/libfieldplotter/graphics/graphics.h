#pragma once

#include <GL/glew.h>

#include <computation/plottermath.h>
#include <vector>
#include <string>

template <typename Type>
struct GLTypeOf;

template<>
struct GLTypeOf<float>
{
	static const uint32_t size = 1;
	static const GLenum type = GL_FLOAT;
};

template<>
struct GLTypeOf<Point>
{
	static const uint32_t size = 3;
	static const GLenum type = GL_FLOAT;
};

template<>
struct GLTypeOf<glm::vec3>
{
	static const uint32_t size = 3;
	static const GLenum type = GL_FLOAT;
};

template<>
struct GLTypeOf<uint32_t>
{
	uint32_t size = 1;
	GLenum type = GL_UNSIGNED_INT;
};

enum Plottable_Buffers {
	FP_VERTICES=0,
	FP_NORMALS,
	FP_ELEMENTS,
};

GLuint loadShadersFromSource(std::string vertex_source, std::string fragment_source);
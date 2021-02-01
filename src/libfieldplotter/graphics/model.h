#pragma once
#include "graphics.h"
#include "attribute.h"

struct Model {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<uint32_t> indices;
	VertexAttribute<glm::vec3> vertexbuffer{false, 0};
	VertexAttribute<glm::vec3> normalbuffer{false, 1};
	GLuint indexbuffer;
	void bind() {
		vertexbuffer.bind();
		normalbuffer.bind();
	}
	void loadGL() {
		/*
		glGenBuffers(1, &buffers[0]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		*/
        this->bind();
        vertexbuffer.setData(vertices);
        normalbuffer.setData(normals);

/*
		glGenBuffers(1, &buffers[1]);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, nullptr);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
*/
		glGenBuffers(1, &indexbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}

	inline size_t size() const { return indices.size(); }
};
Model loadArrowModel();
void loadSphereModel(Model& model);
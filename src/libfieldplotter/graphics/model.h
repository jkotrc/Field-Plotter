#pragma once
#include "graphics.h"
#include "attribute.h"
#include "buffers.h"

struct Model {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<uint32_t> indices;
	VertexArray* vao;

	VertexBuffer vb;
	IndexBuffer ib;
	//VertexAttribute<glm::vec3> vertexbuffer{false, 0};
	//VertexAttribute<glm::vec3> normalbuffer{false, 1};
	Model(VertexArray* vao) : vao(vao), vb(GL_STATIC_DRAW), ib(GL_STATIC_DRAW) {
		//glGenBuffers(1, &indexbuffer);
	}


	void update() {
		vao->bind();
		vb.resize(vertices.size()*sizeof(glm::vec3) + normals.size() * sizeof(glm::vec3));

		vb.setData(&vertices[0], (int)vertices.size(), (size_t)0);
		vb.setData(&normals[0], (int)normals.size(), vertices.size()*sizeof(glm::vec3));
		
		ib.setAndAllocateData(&indices[0], (int)indices.size(), (size_t)0);
		
		VertexAttribute positions = VertexAttribute::create<glm::vec3>(0, 0, 0);
		VertexAttribute normals = VertexAttribute::create<glm::vec3>(1, vertices.size() * sizeof(glm::vec3), 0);
		//setData already binds the array buffer
		positions.makePointer();
		normals.makePointer();

		vao->addAttribute(positions);
		vao->addAttribute(normals);
		//vertexbuffer.setData(vertices);
        //normalbuffer.setData(normals);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}

	inline size_t size() const { return indices.size(); }
};
Model loadArrowModel();
void loadSphereModel(Model& model, float radius=0.3f);
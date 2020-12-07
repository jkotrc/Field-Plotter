#include "chargesystem.h"
#include "computation.h"

#include "graphics.h"

#include "Shaders.h"

#include <stdlib.h>

using namespace glm;

ChargeSystem::ChargeSystem(Scene* parent,std::vector<PointCharge> charges) {
	this->m_parent = parent;
	for (const auto& charge : charges) {
		m_point.push_back(charge.p);
		m_charge.push_back(charge.charge);
	}
}
ChargeSystem::ChargeSystem(Scene* parent) {
	this->m_parent = parent;
}

bool ChargeSystem::initGraphics() {
	if (m_graphicsInitialized) return true;

	m_model = loadSphereModel();

	m_buffers.resize(5);

	glGenBuffers(1, &m_buffers[FP_VERTICES]);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[FP_VERTICES]);
	glEnableVertexAttribArray(FP_VERTICES);
	glVertexAttribPointer(FP_VERTICES, 3, GL_FLOAT, false, 0, nullptr);
	glBufferData(GL_ARRAY_BUFFER, m_model.vertices.size() * sizeof(vec3), &m_model.vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_buffers[FP_NORMALS]);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[FP_NORMALS]);
	glEnableVertexAttribArray(FP_NORMALS);
	glVertexAttribPointer(FP_NORMALS, 3, GL_FLOAT, false, 0, nullptr);
	glBufferData(GL_ARRAY_BUFFER, m_model.normals.size() * sizeof(vec3), &m_model.normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_buffers[FP_ELEMENTS]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[FP_ELEMENTS]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model.indices.size() * sizeof(unsigned int), &m_model.indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_buffers[3]);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[3]);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, 0, nullptr);
	glVertexAttribDivisor(3,1);
	glBufferData(GL_ARRAY_BUFFER, m_point.size() * sizeof(Point), &m_point[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_buffers[4]);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[4]);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4,1,GL_FLOAT,false,0,nullptr);
	glVertexAttribDivisor(4,1);
	glBufferData(GL_ARRAY_BUFFER, m_charge.size()*sizeof(float), &m_charge[0], GL_STATIC_DRAW);

    m_programID = loadShadersFromSource(Shaders::CHARGE_VERTEXSHADER, Shaders::CHARGE_FRAGMENTSHADER);

	glUniformBlockBinding(m_programID, glGetUniformBlockIndex(m_programID, "Matrices"), 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_parent->getSceneMatrices());
	glUniformMatrix4fv(glGetUniformLocation(m_programID, "modelMat"), 1, false, glm::value_ptr(m_modelMatrix));
	
	glUseProgram(m_programID);

	m_graphicsInitialized = true;
}

void ChargeSystem::draw() {
	glUseProgram(m_programID);

	glUniformBlockBinding(m_programID, glGetUniformBlockIndex(m_programID, "Matrices"), 0);
	glUniformMatrix4fv(glGetUniformLocation(m_programID, "modelMat"),1,false,glm::value_ptr(m_modelMatrix));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[FP_ELEMENTS]);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[FP_VERTICES]);
	glVertexAttribPointer(FP_VERTICES, 3, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[FP_NORMALS]);
	glVertexAttribPointer(FP_NORMALS, 3, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[3]);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[4]);
	glVertexAttribPointer(4, 1, GL_FLOAT, false, 0, nullptr);
	
	glDrawElementsInstanced(GL_TRIANGLES,m_model.size(),GL_UNSIGNED_INT,(void*)0,m_charge.size());
}


void ChargeSystem::addCharge(PointCharge const& charge) {
	m_point.push_back(charge.p);
	m_charge.push_back(charge.charge);
}
void ChargeSystem::removeCharge(int index) {
	m_point.erase(m_point.begin()+index);
	m_charge.erase(m_charge.begin()+index);
}
float ChargeSystem::getRadius() {
	return m_radius;
}
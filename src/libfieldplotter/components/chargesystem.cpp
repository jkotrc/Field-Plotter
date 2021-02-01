#include "chargesystem.h"

#include <graphics/shaders.h>

#include <stdlib.h>
#include <string>

using namespace glm;

ChargeSystem::ChargeSystem(std::vector<PointCharge> const& charges) : ChargeSystem() {
	for (const auto& charge : charges) {
		m_charges.push_back(charge.charge);
		m_points.push_back(charge.p);
	}
}
ChargeSystem::ChargeSystem() : m_pointbuffer({true, point_index}),m_chargebuffer({true, charge_index}) {}

bool ChargeSystem::initGraphics() {
	if (m_graphicsInitialized) return true;
	m_modelMatrix=mat4(1.0f);
	loadSphereModel(m_model);

	m_pointbuffer.setData(m_points);
	m_chargebuffer.setData(m_charges);
	
    m_programID = loadShadersFromSource(Shaders::CHARGE_VERTEXSHADER, Shaders::CHARGE_FRAGMENTSHADER);
	m_graphicsInitialized = true;
	return true;
}

void ChargeSystem::draw() {	
	glUseProgram(m_programID);
	glUniformMatrix4fv(glGetUniformLocation(m_programID,"modelMat"),1,GL_FALSE,glm::value_ptr(m_modelMatrix));
	m_parent->getUniforms().bind(m_programID,"Matrices");
	m_model.bind();
	m_pointbuffer.bind();
	m_chargebuffer.bind();
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model.indexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, m_model.indexbuffer);
	//glVertexAttribPointer(FP_VERTICES, 3, GL_FLOAT, false, 0, nullptr);

	//glBindBuffer(GL_ARRAY_BUFFER, m_model.buffers[FP_NORMALS]);
	//glVertexAttribPointer(FP_NORMALS, 3, GL_FLOAT, false, 0, nullptr);

	//glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
	//glVertexAttribPointer(3, 3, GL_FLOAT, false, 0, nullptr);

	//glBindBuffer(GL_ARRAY_BUFFER, m_buffers[1]);
	//glVertexAttribPointer(4, 1, GL_FLOAT, false, 0, nullptr);

	glDrawElementsInstanced(GL_TRIANGLES,m_model.size(),GL_UNSIGNED_INT,nullptr,(int)m_charges.size());
}


void ChargeSystem::addCharge(PointCharge const& charge) {
	m_points.push_back(charge.p);
	m_charges.push_back(charge.charge);
}
void ChargeSystem::removeCharge(int index) {
	m_points.erase(m_points.begin()+index);
	m_charges.erase(m_charges.begin()+index);
}
float ChargeSystem::getRadius() {
	return m_radius;
}
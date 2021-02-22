#include "chargesystem.h"

#include <graphics/shaders.h>

using namespace glm;

ChargeSystem::ChargeSystem(std::vector<PointCharge> const& charges) : ChargeSystem() {
	for (const auto& charge : charges) {
		m_charges.push_back(charge.charge);
		m_points.push_back(charge.p);
	}
	updateGraphics();
}
ChargeSystem::ChargeSystem() : m_instancesbuffer(GL_DYNAMIC_DRAW), m_model(&m_vao) {
	loadSphereModel(m_model);
	m_programID = loadShadersFromSource(Shaders::CHARGE_VERTEXSHADER, Shaders::CHARGE_FRAGMENTSHADER);
}

void ChargeSystem::updateGraphics() {
	m_instancesbuffer.resize(m_points.size() * sizeof(Point) + m_charges.size() * sizeof(float));
	m_instancesbuffer.setData(&m_points[0], m_points.size(), (size_t)0);
	m_instancesbuffer.setData(&m_charges[0], m_charges.size(), m_points.size() * sizeof(Point));
	VertexAttribute instance_positions = VertexAttribute::create<Point>(point_index,0,0,true);
	VertexAttribute instance_charges = VertexAttribute::create<float>(charge_index, m_points.size()*sizeof(Point), 0, true);
	instance_positions.makePointer();
	instance_charges.makePointer();
	m_vao.addAttribute(instance_positions);
	m_vao.addAttribute(instance_charges);
}

void ChargeSystem::draw() {
	m_vao.bind();
	glUseProgram(m_programID);
	glUniformMatrix4fv(glGetUniformLocation(m_programID,"modelMat"),1,GL_FALSE,glm::value_ptr(m_modelMatrix));
	m_parent->getUniforms().bind(m_programID,"Matrices");

	//m_model.bind();
	//m_pointbuffer.bind();
	//m_chargebuffer.bind();
	m_model.ib.bind();
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

void ChargeSystem::setRadius(float r) {
	loadSphereModel(m_model, r);
}

float ChargeSystem::getRadius() {
	return m_radius;
}
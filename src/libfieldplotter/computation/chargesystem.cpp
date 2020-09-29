#include <fieldplotter/fieldplotter.h>
#include "../graphics/Shaders.h"
#include <stdlib.h>
using namespace glm;

ChargeSystem::ChargeSystem(int N, PointCharge* charges) : Plottable(loadSphereModel()) {
	pointCharges.resize(N);
	memcpy(&pointCharges[0], &charges[0], N*sizeof(PointCharge));
}

void ChargeSystem::initGraphics() {
    Plottable::initGraphics();
	assert(buffers.size() == size_t(3));
	modelMatrix=mat4(1.0f);

	float instance_positions[3*pointCharges.size()];
	for (int i = 0; i < pointCharges.size();i++) {
		instance_positions[3*i] = pointCharges[i].p.x;
		instance_positions[3*i+1] = pointCharges[i].p.y;
		instance_positions[3*i+2] = pointCharges[i].p.z;
	}
	
	buffers.push_back(0);
	glGenBuffers(1, &buffers[3]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, 0, nullptr);
	glVertexAttribDivisor(3,1);
	glBufferData(GL_ARRAY_BUFFER, pointCharges.size() * sizeof(float)*3, instance_positions, GL_STATIC_DRAW);

    programID = loadShadersFromSource(Shaders::CHARGE_VERTEXSHADER, Shaders::CHARGE_FRAGMENTSHADER);
	glUseProgram(programID);

	glUniformBlockBinding(programID, glGetUniformBlockIndex(programID, "Matrices"), 0);
	glBindBufferBase(GL_UNIFORM_BUFFER,0,parent->getSceneMatrices());
	glUniformMatrix4fv(glGetUniformLocation(programID, "modelMat"),1,false,glm::value_ptr(modelMatrix)); //TODO: Check this if fail
}

void ChargeSystem::draw() {
	glUseProgram(programID);
	glUniformBlockBinding(programID, glGetUniformBlockIndex(programID, "Matrices"), 0);
	glUniformMatrix4fv(glGetUniformLocation(programID, "modelMat"),1,false,glm::value_ptr(modelMatrix)); //TODO: Check this if fail
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[FP_ELEMENTS]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[FP_VERTICES]);
	glVertexAttribPointer(FP_VERTICES, 3, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[FP_NORMALS]);
	glVertexAttribPointer(FP_NORMALS, 3, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
	glVertexAttribPointer(3, 3, GL_FLOAT, false, 0, nullptr);
	glDrawElementsInstanced(GL_TRIANGLES,model.indices.size(),GL_UNSIGNED_INT,(void*)0,pointCharges.size());
}


void ChargeSystem::addCharge(PointCharge& charge,int index) {
	pointCharges.insert(pointCharges.begin()+index,charge);
}
void ChargeSystem::removeCharge(int index) {
	pointCharges.erase(pointCharges.begin()+index);
}
int ChargeSystem::getN() {
	return pointCharges.size();
}
PointCharge* ChargeSystem::getCharges() {
	return &pointCharges[0];
}
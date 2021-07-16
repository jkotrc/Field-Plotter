#include "model.h"
#define SPHERE_DEFINITION 10
#define PI 3.1415926f

#include <vector>
#include "../computation/plottermath.h"
using namespace glm;

void loadSphereModel(Model& model, float radius) {
	std::vector<vec3>& vertices = model.vertices;
	std::vector<vec3>& normals = model.normals;
	std::vector<uint32_t>& indices = model.indices;
	vertices.clear();
	normals.clear();
	indices.clear();
	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal

	float sectorStep = 2 * PI / SPHERE_DEFINITION;
	float stackStep = PI / SPHERE_DEFINITION;
	float sectorAngle, stackAngle;


	for(int i = 0; i <= SPHERE_DEFINITION; ++i) {
		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);

		// add (SPHERE_DEFINITION+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for(int j = 0; j <= SPHERE_DEFINITION; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
			vertices.push_back({x,y,z});

			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			normals.push_back({nx,ny,nz});
		}
		int k1, k2;
		for(int i = 0; i < SPHERE_DEFINITION; ++i) {
			k1 = i * (SPHERE_DEFINITION + 1);     // beginning of current stack
			k2 = k1 + SPHERE_DEFINITION + 1;      // beginning of next stack

			for(int j = 0; j < SPHERE_DEFINITION; ++j, ++k1, ++k2) {
				// 2 triangles per sector excluding first and last stacks
				// k1 => k2 => k1+1
				if(i != 0)
				{
					indices.push_back(k1);
					indices.push_back(k2);
					indices.push_back(k1 + 1);
				}

				// k1+1 => k2 => k2+1
				if(i != (SPHERE_DEFINITION-1))
				{
					indices.push_back(k1 + 1);
					indices.push_back(k2);
					indices.push_back(k2 + 1);
				}
			}
		}
	}
	model.update();
}

#define SCALE 0.6f
#define LEVEL_OF_DETAIL 10
#define Z_OFFSET (CYLINDER_HEIGHT - CONE_HEIGHT) / 2
#define CONE_HEIGHT 0.06*SCALE
#define CYLINDER_HEIGHT 0.15*SCALE
#define CYLINDER_RADIUS 0.004*SCALE
#define CONE_RADIUS 0.01*SCALE
Model loadArrowModel(Model& model) {
	int i;
	const glm::vec3 baseNormal = { 0, 0, -1 };
	float l = sqrt(CONE_RADIUS * CONE_RADIUS + CONE_HEIGHT * CONE_HEIGHT);
	float f1 = CONE_RADIUS / l;
	float f2 = CYLINDER_HEIGHT / l;
	model.vertices.reserve(LEVEL_OF_DETAIL * 5);
	model.normals.reserve(LEVEL_OF_DETAIL * 5);
	model.vertices.push_back({ 0, 0, Z_OFFSET + CONE_HEIGHT });
	model.normals.push_back({ 0, 0, 0 });
	for (i = 0; i < LEVEL_OF_DETAIL; i++) {
		float alpha = 2 * PI * i / LEVEL_OF_DETAIL;
		model.vertices.push_back({ CONE_RADIUS * cos(alpha), CONE_RADIUS * sin(alpha), Z_OFFSET });
		model.normals.push_back({ f2 * cos(alpha), f2 * sin(alpha), f1 });
	}
	for (i = 0; i < LEVEL_OF_DETAIL; i++) {
		float alpha = 2 * PI * i / LEVEL_OF_DETAIL;
		model.vertices.push_back({ CONE_RADIUS * cos(alpha), CONE_RADIUS * sin(alpha), Z_OFFSET });
		model.normals.push_back(baseNormal);
	}
	for (i = 0; i < LEVEL_OF_DETAIL; i++) {
		float alpha = 2 * PI * i / LEVEL_OF_DETAIL;
		model.vertices.push_back({ CYLINDER_RADIUS * cos(alpha), CYLINDER_RADIUS * sin(alpha), Z_OFFSET - CYLINDER_HEIGHT });
		model.normals.push_back(baseNormal);
	}
	for (i = 0; i < LEVEL_OF_DETAIL; i++) {
		float alpha = 2 * PI * i / LEVEL_OF_DETAIL;
		model.vertices.push_back({ CYLINDER_RADIUS * cos(alpha), CYLINDER_RADIUS * sin(alpha), Z_OFFSET - CYLINDER_HEIGHT });
		model.normals.push_back({ cos(alpha), sin(alpha), 0 });
	}
	for (i = 0; i < LEVEL_OF_DETAIL; i++) {
		float alpha = 2 * PI * i / LEVEL_OF_DETAIL;
		model.vertices.push_back({ CYLINDER_RADIUS * cos(alpha), CYLINDER_RADIUS * sin(alpha), Z_OFFSET });
		model.normals.push_back({ cos(alpha), sin(alpha), 0 });
	}
	model.indices.reserve(LEVEL_OF_DETAIL * 15);
	for (i = 0; i < LEVEL_OF_DETAIL; i++) {
		model.indices.push_back(1 + i);
		model.indices.push_back(1 + (i + 1) % LEVEL_OF_DETAIL);
		model.indices.push_back(0);
	}
	for (i = 0; i < LEVEL_OF_DETAIL; i++) {
		model.indices.push_back(LEVEL_OF_DETAIL + 1);
		model.indices.push_back(LEVEL_OF_DETAIL + 1 + (i + 1) % LEVEL_OF_DETAIL);
		model.indices.push_back(LEVEL_OF_DETAIL + 1 + i);
	}
	for (i = 0; i < LEVEL_OF_DETAIL; i++) {
		model.indices.push_back(LEVEL_OF_DETAIL * 2 + 1);
		model.indices.push_back(LEVEL_OF_DETAIL * 2 + 1 + (i + 1) % LEVEL_OF_DETAIL);
		model.indices.push_back(LEVEL_OF_DETAIL * 2 + 1 + i);
	}
	for (i = 0; i < LEVEL_OF_DETAIL; i++) {
		model.indices.push_back(LEVEL_OF_DETAIL * 3 + 1 + i);
		model.indices.push_back(LEVEL_OF_DETAIL * 3 + 1 + (i + 1) % LEVEL_OF_DETAIL);
		model.indices.push_back(LEVEL_OF_DETAIL * 4 + 1 + i);
		model.indices.push_back(LEVEL_OF_DETAIL * 4 + 1 + i);
		model.indices.push_back(LEVEL_OF_DETAIL * 3 + 1 + (i + 1) % LEVEL_OF_DETAIL);
		model.indices.push_back(LEVEL_OF_DETAIL * 4 + 1 + (i + 1) % LEVEL_OF_DETAIL);
	}
	return model;
}

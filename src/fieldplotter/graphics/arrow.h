#ifndef ARROW_H_
#define ARROW_H_

#include <vector>
#include <glm/glm.hpp>

#define SCALE 4
#define LEVEL_OF_DETAIL 6
#define Z_OFFSET (CYLINDER_HEIGHT - CONE_HEIGHT) / 2
#define CONE_HEIGHT 0.06*SCALE
#define CYLINDER_HEIGHT 0.08*SCALE
#define CYLINDER_RADIUS 0.005*SCALE
#define CONE_RADIUS 0.03*SCALE
#define PI 3.1415926

void loadArrowModel(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<unsigned int>& indices) {
		int i;
		const glm::vec3 baseNormal = { 0, 0, -1 };
		float l = sqrt(CONE_RADIUS * CONE_RADIUS + CONE_HEIGHT * CONE_HEIGHT);
		float f1 = CONE_RADIUS / l;
		float f2 = CYLINDER_HEIGHT / l;
		positions.reserve(LEVEL_OF_DETAIL * 5);
		normals.reserve(LEVEL_OF_DETAIL * 5);
		positions.push_back({ 0, 0, Z_OFFSET + CONE_HEIGHT });
		normals.push_back({ 0, 0, 0 });
		for (i = 0; i < LEVEL_OF_DETAIL; i++) {
			float alpha = 2 * PI * i / LEVEL_OF_DETAIL;
			positions.push_back({ CONE_RADIUS * cos(alpha), CONE_RADIUS * sin(alpha), Z_OFFSET });
			normals.push_back({ f2 * cos(alpha), f2 * sin(alpha), f1 });
		}
		for (i = 0; i < LEVEL_OF_DETAIL; i++) {
			float alpha = 2 * PI * i / LEVEL_OF_DETAIL;
			positions.push_back({ CONE_RADIUS * cos(alpha), CONE_RADIUS * sin(alpha), Z_OFFSET });
			normals.push_back(baseNormal);
		}
		for (i = 0; i < LEVEL_OF_DETAIL; i++) {
			float alpha = 2 * PI * i / LEVEL_OF_DETAIL;
			positions.push_back({ CYLINDER_RADIUS * cos(alpha), CYLINDER_RADIUS * sin(alpha), Z_OFFSET - CYLINDER_HEIGHT });
			normals.push_back(baseNormal);
		}
		for (i = 0; i < LEVEL_OF_DETAIL; i++) {
			float alpha = 2 * PI * i / LEVEL_OF_DETAIL;
			positions.push_back({ CYLINDER_RADIUS * cos(alpha), CYLINDER_RADIUS * sin(alpha), Z_OFFSET - CYLINDER_HEIGHT });
			normals.push_back({ cos(alpha), sin(alpha), 0 });
		}
		for (i = 0; i < LEVEL_OF_DETAIL; i++) {
			float alpha = 2 * PI * i / LEVEL_OF_DETAIL;
			positions.push_back({ CYLINDER_RADIUS * cos(alpha), CYLINDER_RADIUS * sin(alpha), Z_OFFSET });
			normals.push_back({ cos(alpha), sin(alpha), 0 });
		}
		indices.reserve(LEVEL_OF_DETAIL * 15);
		for (i = 0; i < LEVEL_OF_DETAIL; i++) {
			indices.push_back(1 + i);
			indices.push_back(1 + (i + 1) % LEVEL_OF_DETAIL);
			indices.push_back(0);
		}
		for (i = 0; i < LEVEL_OF_DETAIL; i++) {
			indices.push_back(LEVEL_OF_DETAIL + 1);
			indices.push_back(LEVEL_OF_DETAIL + 1 + (i + 1) % LEVEL_OF_DETAIL);
			indices.push_back(LEVEL_OF_DETAIL + 1 + i);
		}
		for (i = 0; i < LEVEL_OF_DETAIL; i++) {
			indices.push_back(LEVEL_OF_DETAIL * 2 + 1);
			indices.push_back(LEVEL_OF_DETAIL * 2 + 1 + (i + 1) % LEVEL_OF_DETAIL);
			indices.push_back(LEVEL_OF_DETAIL * 2 + 1 + i);
		}
		for (i = 0; i < LEVEL_OF_DETAIL; i++) {
			indices.push_back(LEVEL_OF_DETAIL * 3 + 1 + i);
			indices.push_back(LEVEL_OF_DETAIL * 3 + 1 + (i + 1) % LEVEL_OF_DETAIL);
			indices.push_back(LEVEL_OF_DETAIL * 4 + 1 + i);
			indices.push_back(LEVEL_OF_DETAIL * 4 + 1 + i);
			indices.push_back(LEVEL_OF_DETAIL * 3 + 1 + (i + 1) % LEVEL_OF_DETAIL);
			indices.push_back(LEVEL_OF_DETAIL * 4 + 1 + (i + 1) % LEVEL_OF_DETAIL);
		}
	}

#endif // ARROW_H_

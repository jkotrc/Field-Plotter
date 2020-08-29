#pragma once

#include <stdio.h>
#include <string>
#include <glm/glm.hpp>

#include "computation/vectorfield.h"
#include "graphics/Assets.h"

#define TAG(t) "["+t+"] "


using namespace std;
using namespace glm;
namespace Debug {
	
	inline void printvec3(const char* tag, const char* message, vec3 vector) {
		printf("[%s] %s (%f, %f, %f)\n", tag, message, vector.x, vector.y, vector.z);
	}
	inline void debugString(const char* tag, const char* message) {
		printf("[%s] %s\n", tag, message);
	}

	inline void printModel(const char* tag, Model* model) {
		printf("[%s] printing model...\n",tag);
		printf("Vertices: ");
		for (auto i : model->vertices) {
			printf("(%f,%f,%f),", i.x, i.y, i.z);
		}
		printf("\nIndices: ");
		for (auto i : model->indices) {
			printf("%u,", i);
		}
		printf("\nNormals: ");
		for (auto i : model->normals) {
			printf("(%f,%f,%f),", i.x, i.y, i.z);
		}
		printf("\n");
	}
}
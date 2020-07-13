#pragma once


//class Simulation;

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>
using namespace glm;
class Renderer {
	private:
		bool drawFieldLines;
		bool drawEquipotentials;

		mat4 Projection;
		mat4 Model;
		mat4 View;


		float angle;
	public:
		Renderer();
		void tempRender();
		void multModel(mat4 matrix, bool fromRight);
		void multView(mat4 view, bool fromRight);
		mat4* getModel();
		mat4* getView();
		void setModel(mat4 model);
		void setView(mat4 view);
};
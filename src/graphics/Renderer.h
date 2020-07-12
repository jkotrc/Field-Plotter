#pragma once


//class Simulation;
class Camera;

/*
	
*/
class Renderer {
	private:
		bool drawFieldLines;
		bool drawEquipotentials;
		Camera* cam;

		float angle;
	public:
		Renderer();
		void tempRender();
};
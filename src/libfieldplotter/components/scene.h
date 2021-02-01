#pragma once

#include <graphics/camera.h>
#include <graphics/sceneuniforms.h>
#include <computation/plottermath.h>

#include <memory>
#include <vector>

class Scene {
	public:
		Scene(int width, int height);
		Scene(const Scene& sc);
		Camera& getCamera();
		SceneUniforms& getUniforms();
		void update();
	private:
		Camera m_camera;
		SceneUniforms* m_uniforms;
};
#include "scene.h"
#include <components/dynamicobject.h>

using namespace glm;

/*
std140 specification:
layout (std140) uniform Block{
                     // base alignment  // aligned offset
    float value;     // 4               // 0 
    vec3 vector;     // 16              // 16  (offset must be multiple of 16 so 4->16)
    mat4 matrix;     // 16              // 32  (column 0)
                     // 16              // 48  (column 1)
                     // 16              // 64  (column 2)
                     // 16              // 80  (column 3)
    float values[3]; // 16              // 96  (values[0])
                     // 16              // 112 (values[1])
                     // 16              // 128 (values[2])
    bool boolean;    // 4               // 144
    int integer;     // 4               // 148
};
*/

Scene::Scene(int width, int height) : m_camera({}) {
	m_uniforms = new SceneUniforms(width,height);
	this->update();
}

Scene::Scene(const Scene& sc) {
    std::cout << "nothing yet\n";
    //m_camera = sc.m_camera;
    //m_uniforms = sc.m_uniforms;
}

void Scene::update() {
    m_uniforms->getViewMatrix() = m_camera.getViewMatrix();
	m_uniforms->getCameraPosition() = m_camera.getPos();
    m_uniforms->update();
}

Camera& Scene::getCamera() {
	return m_camera;
}

SceneUniforms& Scene::getUniforms() {
	return *m_uniforms;
}
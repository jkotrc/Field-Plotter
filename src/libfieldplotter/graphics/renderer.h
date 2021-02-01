#pragma once

#include "graphics.h"
#include "components/scene.h"
#include <vector>

class Plottable;
class Renderer {
    public:
        Renderer(Scene* scene);
        Renderer();
		void initGraphics();
		void render();
        void addObject(Plottable* plottable);
        void removeObject(Plottable* plottable);
        void resizeScreen(int w, int h);
    private:
        Scene* m_scene;
        std::vector<Plottable*> m_plottables;
        int m_width;
        int m_height;
        GLuint m_vao;
};

/*class Scene {
	public:
		Scene(int width, int height);
		void render();
		void initGraphics();
		void resizeViewport(int w, int h);
		void addPlottable(Plottable* plottable);
		void removePlottable(Plottable* plottable);
		GLuint getSceneMatrices();
		Camera& getCamera();
	private:
		std::vector<Plottable*> m_plottables;
		Camera m_camera;
		GLuint m_vao;
		GLuint m_uniformbuffer;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;	
};*/
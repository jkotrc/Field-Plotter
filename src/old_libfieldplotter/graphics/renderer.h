#pragma once

#include "graphics.h"
#include "components/scene.h"
#include <vector>

class Plottable;
class Renderer {
    public:
        Renderer();
		void initGraphics();
		void render();
        void setScene(Scene* scene);
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
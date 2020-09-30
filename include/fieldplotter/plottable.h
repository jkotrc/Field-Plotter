#pragma once
#include <fieldplotter/commonheaders.h>
#include <fieldplotter/graphics.h>

//struct Model;
class Scene;
class Plottable {
	protected:
		Model model;
		Scene* parent;
		std::vector<GLuint> buffers;
		GLuint programID;
		glm::mat4 modelMatrix;
		bool visible;
    public:
		Plottable(Model mdl);
		Plottable();
		virtual void draw(){}//TODO: maybe don't make this abstract
		virtual void initGraphics();
		void setParent(Scene* parent);
		void setVisible(bool visible);
		bool isVisible();
};
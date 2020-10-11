#pragma once
#include <fieldplotter/commonheaders.h>
#include <fieldplotter/graphics.h>
#include <queue>

//struct Model;
class Scene;
class Plottable {
	protected:
		Model model;
		Scene* parent;
		std::vector<GLuint> buffers;
		
		size_t thread_buffersize;
		size_t thread_bufferoffset;

		GLuint programID;
		glm::mat4 modelMatrix;
		bool visible;
    public:
		Plottable(Model mdl);
		Plottable();
		virtual void draw(){}//TODO: maybe don't make this abstract
		virtual void initGraphics();
		virtual void updateBuffer(){}//TODO: implement this for all Plottables

		void setParent(Scene* parent);
		void setVisible(bool visible);
		bool isVisible();
};
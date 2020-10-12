#pragma once
#include <fieldplotter/commonheaders.h>
#include <fieldplotter/graphics.h>

struct Model;
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
		virtual void draw(){}
		virtual void initGraphics();
		virtual void updateBuffer(){}

		void setParent(Scene* parent);
		void setVisible(bool visible);
		bool isVisible();
};
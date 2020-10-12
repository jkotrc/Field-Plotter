#pragma once
#include "plottable.h"
#include "scene.h"
#include <functional>

class PhysicalObject : public Plottable {
	protected:
		Scene* parent;
		int parent_index;
		size_t thread_buffersize;
		size_t thread_bufferoffset;
		GLuint programID;
		glm::mat4 modelMatrix;
		void (PhysicalObject::*draw_callback)();
		virtual void staticDraw() = 0;
		virtual void dynamicDraw() = 0;
    public:
		virtual void initGraphics() = 0;
		void setParent(Scene* parent, int index);
		void detach();
		//TODO: this might cause a bug
		virtual void draw() override;
		void setComputationalState(bool state);
};
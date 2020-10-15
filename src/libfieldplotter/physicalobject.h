#pragma once
#include "plottable.h"
#include "scene.h"
#include <functional>

class PhysicalObject : public Plottable {
	protected:
		Scene* parent=NULL;
		int parent_index;
		size_t thread_buffersize=size_t(0);
		size_t thread_bufferoffset=size_t(0);
		GLuint programID;
		glm::mat4 modelMatrix;
		void (PhysicalObject::*draw_callback)();
		virtual void staticDraw() = 0;
		void dynamicDraw();
		bool computed = false;
    public:
		virtual void updateBuffers() = 0;
		void setParent(Scene* parent, int index);
		void detach();
		virtual void draw() override;
		void setComputationalState(bool state);
		bool isComputed();
		void setComputed(bool comp);
};
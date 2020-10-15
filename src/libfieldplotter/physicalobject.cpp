#include "physicalobject.h"


void PhysicalObject::setParent(Scene* parent, int index){
 this->parent = parent;
 this->parent_index = index;
}

void PhysicalObject::detach() {
	if (parent == NULL)return;
	parent->removeComponent(parent_index);//TODO: address this issue
	parent = nullptr;
}

void PhysicalObject::dynamicDraw() {
	updateBuffers();
	staticDraw();
}

void PhysicalObject::draw() {
	PhysicalObject& a = *this;
	(a.*(a.draw_callback))();
}

void PhysicalObject::setComputationalState(bool state) {
	if (state == true) {
		draw_callback = &PhysicalObject::dynamicDraw;
		return;
	}
	draw_callback = &PhysicalObject::staticDraw;
}

bool PhysicalObject::isComputed() {
	return computed;
}
void PhysicalObject::setComputed(bool comp) {
	computed = comp;
}
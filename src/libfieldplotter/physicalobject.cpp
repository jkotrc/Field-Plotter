#include "physicalobject.h"


void PhysicalObject::setParent(Scene* parent, int index){
 this->parent = parent;
 this->parent_index = index;
}

void PhysicalObject::detach() {
	parent->removeComponent(parent_index);//TODO: address this issue
	parent = nullptr;
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
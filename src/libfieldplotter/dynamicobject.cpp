#include "dynamicobject.h"
#include "concurrentqueue.h"
#include <iostream>

void DynamicObject::setComputationQueue(ConcurrentQueue* q) {
	m_computationqueue = q;
}

void DynamicObject::draw() {
	DynamicObject& a = *this;
	(a.*(a.m_drawcallback))();
}

/*void DynamicObject::setComputationState(bool state) {
	if (state == true) {
		m_drawcallback = &DynamicObject::dynamicDraw;
		return;
	}
	m_drawcallback = &DynamicObject::staticDraw;
}*/

void DynamicObject::beginDynamic() {
	if (m_computationqueue) {
		if (!m_computationqueue->isFinished()) {
			m_drawcallback = &DynamicObject::dynamicDraw;
			return;
		}
	}
	std::cout << "Could not begin dynamic for object! ConcurrentQueue either null or finished\n";
}
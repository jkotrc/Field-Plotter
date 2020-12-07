#pragma once
#include "plottable.h"
#include <functional>

class ConcurrentQueue;
class DynamicObject : public Plottable {
	public:
		virtual void draw() override;
		void setComputationQueue(ConcurrentQueue* queue);
		void beginDynamic();
	protected:
		bool m_computationDone{false};
		ConcurrentQueue* m_computationqueue;
		void (DynamicObject::* m_drawcallback)();
		virtual void dynamicDraw() = 0;
		virtual void staticDraw() = 0;
};
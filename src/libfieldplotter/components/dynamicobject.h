#pragma once

#include "plottable.h"

#include "../common/readerwriterqueue.h"
using moodycamel::ReaderWriterQueue;

#include <future>
#include <functional>

class DynamicObject : public Plottable {
	public:
		~DynamicObject();
		void draw() override;
		void finishComputation();
		template <typename Function, typename... Args>
		static void run_computation(Function&& f, Args&&... args);
	protected:
		ReaderWriterQueue<Point> m_compqueue;
		bool m_computationDone;
		void (DynamicObject::* m_drawcallback)();
		virtual void dynamicDraw() = 0;
		virtual void staticDraw() = 0;
};
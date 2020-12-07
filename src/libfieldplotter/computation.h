#pragma once

#include "plottermath.h"
#include <thread>

//TODO: implement fully
class PhysicalObject;
template<typename T, typename std::enable_if<std::is_base_of<PhysicalObject, T>::value>::type* = nullptr>
class Computation {
	public:
		Computation(auto func) : m_computefunc(func) {}
		~Computation() { if (m_workerThread.joinable())m_workerThread.join(); }

		std::shared_ptr<ConcurrentQueue> compute(ChargeSystem* system, T* object) {
			m_workerThread = std::thread(m_computefunc, system, object, m_pointbuffer);
		}
	private:
		std::thread m_workerThread;
		std::shared_ptr<ConcurrentQueue> m_pointbuffer;
		void (*m_computefunc)(ChargeSystem* system, T* object, ConcurrentQueue* queue);
};


//void compute_electric_field(DynamicObject* vf, ChargeSystem& system);
//void compute_field_lines(DynamicObject* lines, ChargeSystem& system);
//Point electrical_force_at(Point r,ChargeSystem& system);
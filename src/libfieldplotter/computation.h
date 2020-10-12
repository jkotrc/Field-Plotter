#pragma once
#include "fieldlines.h"
#include "vectorfield.h"
#include "plottermath.h"
#include <thread>

class ChargeSystem;
template <typename T>
class Computation {
	private:
		T& component;
		ChargeSystem& charge_system;
		bool completed;
		void (*compute_function)(T& object, ChargeSystem& system);
		void run();
	protected:
		virtual void onFinalize(){}
	public:
		Computation(T& comp,ChargeSystem& charge_system, void (*func)(T& object, ChargeSystem& system));
		T& getComponent();
		void spawnThread();
		bool isComplete();
};

//compute functions not contained within any class so that they may be more easily provided through other interfaces in the future (CUDA, Fortran, MATLAB,....)
void compute_electric_field(VectorField& vf, ChargeSystem& system);
void compute_field_lines(FieldLines& lines, ChargeSystem& system);
Point electrical_force_at(Point r,ChargeSystem& system);
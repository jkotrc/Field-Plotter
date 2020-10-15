#pragma once
#include "fieldlines.h"
#include "vectorfield.h"
#include "plottermath.h"
#include <thread>

class ChargeSystem;


class Computation {
private:
	PhysicalObject* component;
	ChargeSystem& charge_system;
	bool completed;
	void (*compute_function)(PhysicalObject* object, ChargeSystem& system);
	void run();
protected:
	virtual void onFinalize() {}
public:
	Computation(PhysicalObject* comp, ChargeSystem& charge_system, void (*func)(PhysicalObject* object, ChargeSystem& system));
	PhysicalObject* getComponent();
	void spawnThread();
	bool isComplete();
	static std::vector<std::thread> active_threads;
};

//compute functions not contained within any class so that they may be more easily provided through other interfaces in the future (CUDA, Fortran, MATLAB,....)
void compute_electric_field(PhysicalObject* vf, ChargeSystem& system);
void compute_field_lines(PhysicalObject* lines, ChargeSystem& system);
Point electrical_force_at(Point r,ChargeSystem& system);




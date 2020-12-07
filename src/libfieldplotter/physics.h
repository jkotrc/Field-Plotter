#pragma once


class FieldLines;
class ChargeSystem;
class ConcurrentQueue;
//void compute_electric_field(DynamicObject* p_vf, ChargeSystem& system);
void compute_field_lines(ChargeSystem* system, FieldLines* p_lines, ConcurrentQueue* queue);
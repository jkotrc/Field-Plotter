#pragma once

#include "../common/readerwriterqueue.h"
#include "plottermath.h"

using moodycamel::ReaderWriterQueue;

constexpr float permittivity = 8.8541878128f;
constexpr float pi = 3.141592653f;
constexpr float factor = 1 / (4 * pi * permittivity);

class ChargeSystem;
class FieldLines;
void compute_field_lines(ChargeSystem* system, FieldLines* p_lines, ReaderWriterQueue<Point>* point_queue, ReaderWriterQueue<int>* index_queue);
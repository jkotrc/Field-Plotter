#pragma once

#include "../common/readerwriterqueue.h"
#include "plottermath.h"

#include <fieldplotter_pch.h>

using moodycamel::ReaderWriterQueue;

constexpr float permittivity = 8.8541878128f;
constexpr float pi = 3.141592653f;
constexpr float factor = 1 / (4 * pi * permittivity);

void compute_field_lines(FieldLines::Configuration const& config, std::vector<PointCharge> const& charges, ReaderWriterQueue<Point>* point_queue, ReaderWriterQueue<int>* index_queue);
//void compute_field_lines(ChargeSystem* system, FieldLines* p_lines, ReaderWriterQueue<Point>* point_queue, ReaderWriterQueue<int>* index_queue);
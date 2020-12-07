#pragma once

#include <atomic>
#include <mutex>
#include <utility>

using line_vector = std::pair<std::vector<Point>, std::vector<int>>;

struct Point;
class ConcurrentQueue {
	public:
		ConcurrentQueue();
		void enqueue_point(Point const& point);
		void enqueue_index(const int index);
		line_vector dequeue_available();
		void finish();
		bool isFinished();
	private:
		std::mutex m_mutex;
		std::vector<Point> m_points;
		std::vector<int> m_indices;
		std::atomic_int m_pointsread;
		std::atomic_int m_indicesread;
		std::atomic_int m_write;
		std::atomic_bool m_finished;
};
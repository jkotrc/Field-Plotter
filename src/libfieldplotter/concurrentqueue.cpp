#include "concurrentqueue.h"



ConcurrentQueue::ConcurrentQueue() {

}
void ConcurrentQueue::enqueue_point(Point const& point) {
	m_points.push_back(point);
	m_pointsread++;
}
void ConcurrentQueue::enqueue_index(const int index) {
	m_indices.push_back(index);
	m_indicesread++;
}
line_vector ConcurrentQueue::dequeue_available() {
	line_vector ret;
	//TODO: finish. lock guard this

}
void ConcurrentQueue::finish() {
	m_finished.store(true);
}
bool ConcurrentQueue::isFinished() {
	return m_finished.load();
}
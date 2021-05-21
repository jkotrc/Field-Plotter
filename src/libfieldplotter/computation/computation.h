#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <common/readerwriterqueue.h>
#include "plottermath.h"

using moodycamel::ReaderWriterQueue;

constexpr float permittivity = 8.8541878128f;
constexpr float pi = 3.141592653f;
constexpr float factor = 1 / (4 * pi * permittivity);


/*
Gotta compute the field lines on a separate thread

FieldLines <- Computation <- Task
*/

template <typename... Args>
class Task {
public:
    template <typename... T> using FuncT = std::function<void(T...)>;
        
private:
    FuncT<Args...> m_func;
};


class DynamicContainer {
    public:
        public DynamicContainer(std::vector<Point>* vertexptr, std::vector<int> indexptr) : m_vertices(vertexptr), m_indices(indexptr) {}
        void addVertex(Point const& vertex) {
            m_vertices->push_back(vertex);
            m_vertexSize++;
        }
        void addIndex(int index) {
            m_indices->push_back(index);
            m_indexSize++;
        }
        int currentIndexCount() {
            return m_indexSize.load();
        }
        int currentVertexCount() {
            return m_vertexSize.load();
        }
    private:
        std::atomic_int m_indexSize{ 0 };
        std::atomic_int m_vertexSize{ 0 };
        std::vector<int>* m_indices;
        std::vector<Point>* m_vertices;
};

class Computation {
public:
    Computation(DynamicContainer const& container) : m_container(container) {}
    ~Computation();
    template <typename Args...>
    void begin(Task<Args...> const& task) {
        if (m_running) {

        }

    }
private:
    std::thread m_thread;
    bool m_running;
    DynamicContainer m_container;
};

//void compute_field_lines(FieldLines::Configuration const& config, std::vector<PointCharge> const& charges, ReaderWriterQueue<Point>* point_queue, ReaderWriterQueue<int>* index_queue);
/*
class Computation {
    public:
        void compute(ChargeSystem& system);

    private:
        std::thread m_thread;
};*/

/*template<typename F, typename... Args>
class Computation {
    public:
        void begin(F function, Args... arguments) {
            m_thread = std::thread(computeFunction, std::forward<F>(function), std::forward<Args>(arguments)...);
        }
        void complete() {
            if (m_thread.joinable())
                m_thread.join();
        }
    private:
        void computeFunction(F function, Args... arguments) {
            function(arguments...);
            m_fieldlines->finishComputation();
        }
        FieldLines* m_fieldlines;
        std::thread m_thread;
};*/
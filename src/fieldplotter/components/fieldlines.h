#ifndef FIELDLINES_H_
#define FIELDLINES_H_

#include <glm/glm.hpp>
#include "charge.h"
#include <vector>
#include <iostream>

#include <boost/thread/thread.hpp>
#include <boost/thread/concurrent_queues/sync_queue.hpp>

//remove these later
glm::vec2 forceAt(glm::vec2 const& point, std::vector<fieldplotter::Charge> const& charges);
void printVec(const char* msg, glm::vec2 val);
/*
** TODO abstract integrator into its own thing
*/
namespace fieldplotter {
    using Line = std::vector<glm::vec2>;
    struct Segment {
        int line;
        glm::vec2 segment;
    };

    class FieldLines;
    class Lyne {
        public:
            Lyne(FieldLines* parent, glm::vec2 const& initial);

            ~Lyne() = default;

            //dequeue next available segment
            bool popSegment(glm::vec2* dest);

            void append(glm::vec2 num);

            void compute();

            bool isFinished();

            void finish();

        private:
            bool finished;
            float dt;
            float step;
            boost::sync_queue<glm::vec2>* line_queue;
            std::vector<glm::vec2> line;
            std::vector<Charge> charges;
    };
        //TODO use some sort of thread pool

    class FieldLines {
        public:
            friend class Lyne;
            FieldLines(float dt, float step, int density);
            ~FieldLines();

            //asynchronous. Begins data stream
            void compute(std::vector<Charge> const& charges);

            bool getSegment(int n, glm::vec2* result);

        private:
            struct Worker {
                boost::thread* thread;
                boost::sync_queue<glm::vec2>* queue;
            };
            std::vector<Worker> workers;
            std::vector<Lyne*> lines;
            int density;
            float dt;
            float step;
            bool initialized;
            std::vector<Charge> charges;
    };
}

#endif // FIELDLINES_H_

#include "fieldlines.h"
#include <stdio.h>

using namespace fieldplotter;
using namespace glm;

#define PI 3.14159

Lyne::Lyne(FieldLines* parent, vec2 const& initial) {
    line_queue = new boost::sync_queue<glm::vec2>;
    line_queue->push(initial);
    line.push_back(initial);
    dt = parent->dt;
    step = parent->step;
    charges = parent->charges;
}

bool Lyne::popSegment(vec2* dest) {
    if (!finished || !line_queue->empty()) {
        vec2 val;
        line_queue->wait_pull(val);
        line.push_back(val);
        dest->x = val.x;
        dest->y = val.y;
        return true;
    }
    return false;
}

void Lyne::append(vec2 num) {
    line_queue->push(num);
    line.push_back(num);
}

void Lyne::compute() {
    std::vector<Charge> sinks;
    for (Charge c : charges) {
        if (c.q < 0.0f) {
            printf("Sink at: %f %f\n", c.pos.x, c.pos.y);
            sinks.push_back(c);
        }
    }

    vec2 pos = line.at(0);

    bool inBounds = true;
    float t = 0.0f;

    float cumulator = 0.0f;

    int i = 0;
    int stuck = 0;
    while (inBounds && !finished && stuck < 1000) {
        i++;
        if (abs(glm::length(pos)) > 10.0f) {
            inBounds = false;
            printf("Leaving bounds\n");
        }
        for (Charge s : sinks) {
            if (glm::length(s.pos - pos) <= s.size) {
                inBounds = false;
                printf("Entered sink\n");
            }
        }

        vec2 dF1 = forceAt(pos, charges) * dt;
        vec2 dF2 = forceAt(pos + dF1 * (dt / 2), charges) * dt;
        vec2 dF3 = forceAt(pos + dF2 * (dt / 2), charges) * dt;
        vec2 dF4 = forceAt(pos + dF3 * (dt), charges) * dt;
        vec2 dF = dF1 + 2.0f * dF2 + 2.0f * dF3 + dF4;

        // vel += force*dt;
        pos += dF;
        t += dt;

        cumulator += glm::length(dF);
        // printf("Cum: %f\nT: %f,%f\n",cumulator,pos.x, pos.y);
        if (cumulator > step) {
            line_queue->wait_push(pos);
            cumulator = 0.0f;
            stuck = 0;
        }
        stuck++;

    }
        finished = true;
}

bool Lyne::isFinished() {
    return finished;
}
void Lyne::finish() {
    finished = true;
}


FieldLines::FieldLines(float dt, float step, int dord) : dt(dt), step(step), initialized(false), density(dord) {}

FieldLines::~FieldLines() {
    for (int i = 0; i < workers.size(); i++) {
        lines[i]->finish();
        workers[i].thread->join();
        workers[i].thread->detach();
    }

}

void FieldLines::compute(std::vector<Charge> const& charges) {
    this->charges = charges;
    std::vector<Charge> sources;

    for (const Charge& charge : charges) {
        if (charge.q > 0.0f) {
            sources.push_back(charge);
            for (int i = 0; i < density; i++) {
                float theta = i* 2*PI / density;
                vec2 pos;
                pos.x = charge.size*cos(theta) + charge.pos.x;
                pos.y = charge.size*sin(theta) + charge.pos.y;

                workers.push_back({});
                int idx = workers.size()-1;
                workers[idx].queue = new boost::sync_queue<vec2>;
                lines.push_back(new Lyne{this, pos});
                workers[idx].thread = new boost::thread(boost::bind(&Lyne::compute, lines.at(lines.size()-1)));
                // workers.push_back();
            }
        }

    }
}

bool FieldLines::getSegment(int n, vec2* result) {
    return lines.at(n)->popSegment(result);
}

#include "fieldlines.h"
#include <stdio.h>

using namespace fieldplotter;
using namespace glm;

#define PI 3.14159
#define CONST 4*PI

//how many segments to compute at once
#define BATCH 2
//permittivity = 8.854*10^-12

float magnitude(vec2 x) {
    return glm::length(x);
}

float magnitude2(vec2 x) {
    return magnitude(x) * magnitude(x);
}

void printVec(const char* msg, vec2 val) {
    printf("%s {%f,%f}\n", msg, val);
}

// #define CAP 1000.0f
vec2 forceAt(vec2 const& point, std::vector<Charge> const& charges) {
    vec2 force = {0.0f,0.0f};
    for (const auto charge : charges) {
        vec2 direction = point - charge.pos;
        float mag3 = magnitude2(direction) * magnitude(direction);
        force += (charge.q / mag3) * direction;
    }
    return force;
}

Lyne::Lyne(FieldLines* parent, vec2 const& initial) {
    line_queue = new boost::sync_queue<glm::vec2>;
    line_queue->push(initial);
    line.push_back(initial);
    // printf("INITIAL: %f;%f", line.at(0).x, line.at(0).y);
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
        // printf("VAL: %f %f", dest->x, dest->y);
        return true;
    }
    return false;
}

void Lyne::append(vec2 num) {
    line_queue->push(num);
    line.push_back(num);
}

#include <assert.h>
void Lyne::compute() {
    std::vector<Charge> sinks;
    for (Charge c : charges) {
        if (c.q < 0.0f) {
            printf("Sink at: %f %f\n", c.pos.x, c.pos.y);
            sinks.push_back(c);
        }
    }

    // printf("INITIAL FROM THREAD: %f;%f\n", line.at(0).x, line.at(0).y);
    vec2 pos = line.at(0);
    // vec2 vel = vec2(0.0f, 0.0f);

    bool inBounds = true;
    float t = 0.0f;

    float cumulator = 0.0f;

    int i = 0;
    int stuck = 0;
    while (inBounds && !finished && stuck < 1000) {
        i++;
        // printf("Iteration %d:\n-----\npos={%f,%f}\nvel={%f,%f}\n",i,pos.x,pos.y,vel.x,vel.y);
        if (abs(magnitude(pos)) > 10.0f) {
            inBounds = false;
            printf("Leaving bounds\n");
        }
        for (Charge s : sinks) {
            if (magnitude(s.pos - pos) <= s.size) {
                inBounds = false;
                printf("Entered sink\n");
            }
        }

        // vec2 force = forceAt(pos,charges);
        // printf("Force: %f,%f", force.x, force.y);
        vec2 dF1 = forceAt(pos, charges) * dt;
        vec2 dF2 = forceAt(pos + dF1 * (dt / 2), charges) * dt;
        vec2 dF3 = forceAt(pos + dF2 * (dt / 2), charges) * dt;
        vec2 dF4 = forceAt(pos + dF3 * (dt), charges) * dt;
        vec2 dF = dF1 + 2.0f * dF2 + 2.0f * dF3 + dF4;

        // vel += force*dt;
        pos += dF;
        t += dt;

        cumulator += magnitude(dF);
        // printf("Cum: %f\nT: %f,%f\n",cumulator,pos.x, pos.y);
        if (cumulator > step) {
            line_queue->push(pos);
            cumulator = 0.0f;
            stuck = 0;
        }
        stuck++;

    }
        finished = true;
        printf("Finished. Pushed %d vertices\n", i);
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

#include <assert.h>
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

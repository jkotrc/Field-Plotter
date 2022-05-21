#include <iostream>

#define PI 3.141592653
#define GLEW_STATIC
#include <GL/glew.h>

#include <window.h>
#include <graphics/program.h>
#include <graphics/shaders.h>

#include <components/fieldlines.h>
#include <components/charge.h>
#include <vector>

#include <glm/glm.hpp>


using namespace glm;
using namespace fieldplotter;

bool running = true;

void onEvent(Event const& e) {
    if (e.getName() == "WindowCloseEvent") {
        running = false;
    }
}

// int main() {
//     int dord = 4;
//     float step = 0.01;
//     float dt = 0.01;


//     FieldLines fl(dt, step, dord);

//     std::vector<Charge> charges;
//     charges.push_back({1.0f, {-1.0f,0.5f}, 0.2f});
//     charges.push_back({-1.0f, {1.0f,0.0f}, 0.2f});

//     fl.compute(charges);

//     bool status = true;
//     vec2 coord = vec2(0.1f,0.1f);
//     while (status) {
//     for (int i = 0; i < dord-1; i++) {
//             if (fl.getSegment(i, &coord)) {
//                 printf("%d Got %f %f\n",i, coord.x, coord.y);
//             } else {
//                 printf("Ran out\n");
//                 status = false;
//             }
//         }
//     }

//     return 0;
// }

//density is 3 globally
int main() {
    Window win;
    win.setEventCallback(onEvent);

    int dord = 20;
    float step = 0.05;
    float dt = 0.001;


    FieldLines fl(dt, step, dord);
    std::vector<Charge> charges;
    charges.push_back({1.7f, {0.6f,0.0f}, 0.2f});
    charges.push_back({-0.7f, {-0.6f,0.0f}, 0.2f});

    GLuint buf;
    GLuint vao;

    Program shader(VERT_2D, FRAG_BLACK);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glPointSize(10.0f);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*200*dord, nullptr, GL_DYNAMIC_DRAW);


    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    fl.compute(charges);

    std::vector<int> sizes;
    sizes.resize(dord);


    while(running) {
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        shader.bind();

        for (int i = 0; i < dord; i++) {
            vec2 coord;
            if (sizes[i] < 200) {
                if (fl.getSegment(i, &coord)) {
                    coord /= 10;
                    glBufferSubData(GL_ARRAY_BUFFER, (200*i+sizes[i])*sizeof(vec2), sizeof(vec2), &coord);
                    sizes[i]++;
                }
            }
            glBindBuffer(GL_ARRAY_BUFFER, buf);
            glDrawArrays(GL_LINE_STRIP, 200*i, sizes[i]);
        }

        win.update();
    }

    return 0;
}


// int main() {

//     return 0;
// }

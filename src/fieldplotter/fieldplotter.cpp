#include "fieldplotter.h"
#include "extern/imgui/backends/imgui_impl_opengl3.h"
#include "extern/imgui/imgui.h"

#include <physics/electrostatics.h>
#include <components/fieldlines.h>

#include <iostream>
#include <vector>
#include <functional>

using namespace fieldplotter;
using namespace glm;

FieldPlotter::FieldPlotter() {
    running = true;
    minimized = false;
    win = new Window();
}

FieldPlotter::~FieldPlotter() {
    running=false;
    delete win;
}

void FieldPlotter::onEvent(Event const& e) {
    //TODO propagate event into its respective layers using a dispatcher
    if (e.getName() == "KeyPressEvent") {
        auto ev = static_cast<KeyPressEvent const&>(e);
        std::cout << "You have pressed the key with code: " << ev.key << "\n";
        switch(ev.key) {
            case GLFW_KEY_W:
                win->getGraphics().camera.moveCamera(0.1, 0);
                break;
            case GLFW_KEY_A:
                win->getGraphics().camera.moveCamera(0,-0.1);
                break;
            case GLFW_KEY_S:
                win->getGraphics().camera.moveCamera(-0.1, 0);
                break;
            case GLFW_KEY_D:
                win->getGraphics().camera.moveCamera(0,0.1);
            default:
                break;
        }

    } else if (e.getName() == "WindowCloseEvent") {
        running = false;
    } else if (e.getName() == "WindowErrorEvent") {
        WindowErrorEvent* event = (WindowErrorEvent*) &e;
        running = false;
        std::cout << "Window error occured. Error Code " << event->getErrorCode() << ", message:\n" << event->getDescription();
    }
}

int FieldPlotter::run() {
    win->setEventCallback(std::bind(&FieldPlotter::onEvent, this, std::placeholders::_1));

    win->show();
    Graphics& g = win->getGraphics();
    g.drawPoint({{0,0.1,0},{0.5,0,0},{0,0.5,0},{0,0,0.5}});
     g.drawPoint({{0.6, -0.5, 0}});


    bool open = true;
    while (running) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(&open);

        char buf[1024];
        float f;
ImGui::Text("Hello, world %d", 123);
if (ImGui::Button("Save")){

}
ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        win->update();
    }

    // GLuint buf;
    // GLuint vao;
    // Program shader(shaders::VERT_2D, shaders::FRAG_BLACK);

    // int dord = 12;
    // float step = 0.1;
    // float dt = 0.001;
    // int N = 7;
    // float size = 5.0f;
    // int positive = 0;
    // std::vector<Charge> charges;
    // FieldLines fl(dt, step, dord);

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         int sgn = (N*i+j) % 3 == 0 ? 1 : -1;
    //         printf("%d sign for {%d,%d}, %d\n",sgn,i,j, N*i+j);
    //         if (sgn == 1) positive++;
    //         charges.push_back({sgn*1.0f, {-size+(2*size)*j/(N-1),-size+(2*size)*i/(N-1)}, 0.2f});
    //     }
    // }
    // dord *= positive; //NUMBER OF POSITIVE CHARGES


    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // glGenBuffers(1, &buf);
    // glBindBuffer(GL_ARRAY_BUFFER, buf);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*200*dord, nullptr, GL_DYNAMIC_DRAW);

    // std::vector<int> sizes;
    // sizes.resize(dord);

    // fl.compute(charges);
        // glClear(GL_COLOR_BUFFER_BIT);
        // glBindVertexArray(vao);
        // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        // shader.bind();


        // for (int i = 0; i < dord; i++) {
        //     vec2 coord;
        //     if (sizes[i] < 200) {
        //         if (fl.getSegment(i, &coord)) {
        //             coord /= 10;
        //             glBufferSubData(GL_ARRAY_BUFFER, (200*i+sizes[i])*sizeof(vec2), sizeof(vec2), &coord);
        //             sizes[i]++;
        //         }
        //     }
        //     glBindBuffer(GL_ARRAY_BUFFER, buf);
        //     glDrawArrays(GL_LINE_STRIP, 200*i, sizes[i]);
        // }

        // win->update();

    return 0;
}

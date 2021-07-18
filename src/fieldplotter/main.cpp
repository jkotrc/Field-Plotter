#include <iostream>

#include "fieldplotter.h"
#include <boost/log/trivial.hpp>

using namespace std;

// int main(int argc, char *argv[]) {
//     fieldplotter::Window* win = new fieldplotter::Window(800, 600, "Debug");
//     fieldplotter::OpenGLContext* ctx = new fieldplotter::OpenGLContext({4,6});
//     win->setOpenGLVersion(ctx->getVersion());
//     if (!win->create()) {
//         cout << "window didn't create\n";
//         return 1;
//     }
//     if (!ctx->initialize()) {
//         cout << "OpenGL context didn't create\n";
//         return 1;
//     }

//     while (!win->shouldClose()) {
//         win->update();
//     }
//     delete win;

//     cout << "Build system works\n";
//     return 0;
// }

int main() {
    fieldplotter::FieldPlotter* fp = new fieldplotter::FieldPlotter(800,600);
    return fp->begin();
}

#include "window.h"
#include "renderer.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace fieldplotter;

TEST(WindowTest, CreatesSuccessfully) {
    Window win;
    ASSERT_NO_THROW(win.show());
}

TEST(WindowTest, DimensionsAreCorrect) {
    Window win(800, 600);
    ASSERT_EQ(win.getWidth(), 800);
    ASSERT_EQ(win.getHeight(), 600);
}

TEST(WindowTest, WindowCloses) {
    Window win;
    win.close();
    ASSERT_TRUE(win.isClosed());
}

//TODO Version setting does not work so far
// TEST(WindowTest, OpenGLVersionSet) {
//     Window::WindowOptions winopt;
//     winopt.openGLVersion.first = 2;
//     winopt.openGLVersion.second = 6;
//     Window win(winopt, 800, 600);
//     OpenGLContext ctx = win.getContext();
//     ASSERT_EQ(ctx.getVersion().first, 2);
//     ASSERT_EQ(ctx.getVersion().second, 6);
// }

// TODO Worry about profiles later
// TEST(WindowTest, OpenGLProfileSet) {
//     Window::WindowOptions winopt;
//     winopt.openGLProfile = Window::CORE_PROFILE;
//     Window win(winopt, 800, 600);
//     OpenGLContext ctx = win.getContext();
//     ASSERT_E
// }

TEST(WindowTest, ValidRenderingSurface) {
    Window win;
    Renderer ren(win.getContext());
    ren.render();
    win.update();
}

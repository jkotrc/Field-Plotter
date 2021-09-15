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

//TODO Integration test
TEST(WindowTest, ValidRenderingSurface) {
    Window win;
    Renderer ren(win.getContext());
    ren.render();
    win.update();
}

/*
** Event system:
** The window needs to have its onEvent callback set. This will be done by the application.
** The onEvent callback will point to a function that handles every single possible event
** in the program.
**
** This function takes events and spawns an event dispatcher to give it to the layers.
**
** Actual window callbacks create events and spawn OnEvent() with them.
**
** TODO implement an event queue that will be processed in another thread
*/


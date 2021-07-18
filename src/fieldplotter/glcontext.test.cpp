#include <gtest/gtest.h>
#include "glcontext.h"
#include "window.h"

using namespace fieldplotter;

class GLContextTest : public ::testing::Test {
    protected:
        void SetUp() override {
             ctx = new OpenGLContext({4,6});
             win = new Window(800,600,"gtest");
             win->setOpenGLVersion(ctx->getVersion());
        }
        void TearDown() override {
            delete win;
            delete ctx;
        }
        OpenGLContext* ctx;
        Window* win;
};

TEST_F(GLContextTest, GLVersionReceived) {
    fieldplotter::GLVersion ver = ctx->getVersion();
    ASSERT_EQ(ver.major, 4);
    ASSERT_EQ(ver.minor, 6);
}

TEST_F(GLContextTest, WindowCreatesCorrectly) {
    ASSERT_TRUE(win->create());
}

TEST_F(GLContextTest, WindowAndContext) {
    ASSERT_TRUE(win->create());
    ASSERT_TRUE(ctx->initialize());
}

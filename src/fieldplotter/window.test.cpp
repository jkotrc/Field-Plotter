#include "window.h"
#include <gtest/gtest.h>

class WindowTest : public ::testing::Test {
    protected:
        void SetUp() override {
            win = new fieldplotter::Window(300, 200, "test");
        }
        void TearDown() override {
            delete win;
        }

        fieldplotter::Window* win;

};

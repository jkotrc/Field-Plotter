#include "line.h"
#include <gtest/gtest.h>

class LineTest: public ::testing::Test {
    public:
        Line* line;
        virtual void SetUp() {
            std::vector<glm::vec3> points = {{0,0,0}, {1,0,0}};
            line = new Line(points[0],points[1]);
        }
        virtual void TearDown() {
            //free() invalid pointer???
            //delete line;
        }
};

TEST_F(LineTest, SelectionFalse) {
    auto selection = line->getSelection();
    ASSERT_EQ(false, selection[0]);
    ASSERT_EQ(false, selection[1]);
}

TEST_F(LineTest, PointsCorrect) {
    auto points = line->getPoints();
    ASSERT_EQ(glm::vec3(0,0,0), points[0]);
    ASSERT_EQ(glm::vec3(1,0,0), points[1]);
}

TEST_F(LineTest, SelectingThings) {
    line->select(true, false);
    auto selection = line->getSelection();
    ASSERT_EQ(true, selection[0]);
    ASSERT_EQ(false, selection[1]);
}

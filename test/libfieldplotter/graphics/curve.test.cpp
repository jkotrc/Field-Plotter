#include "curve.h"
#include <gtest/gtest.h>

class CurveTest : public testing::Test {
    public:
        Curve* curve;
        virtual void SetUp() {
            std::vector<glm::vec3> points = {{0,0,0}, {0,1,0}};
            curve = new Curve(std::move(points));
        }
        virtual void TearDown() {

        }
};

TEST_F(CurveTest, SelectionFalse) {
    auto selection = curve->getSelection();
    ASSERT_EQ(false, selection[0]);
    ASSERT_EQ(false, selection[1]);
}

TEST_F(CurveTest, PointsCorrect) {
    auto points = curve->getPoints();
    ASSERT_EQ(glm::vec3(0,0,0), points[0]);
    ASSERT_EQ(glm::vec3(0,1,0), points[1]);
}

TEST_F(CurveTest, SelectingThings) {
    curve->select(std::vector<bool>{true,false});
    auto selection = curve->getSelection();
    ASSERT_EQ(true, selection[0]);
    ASSERT_EQ(false, selection[1]);
}

#include <gtest/gtest.h>
#include <graphics/attribute.h>
#include <computation/plottermath.h>

#include <vector>

class AttributeTest : public ::testing::Test {
    //public:
    //virtual void SetUpTestCase(){}
    //virtual void TearDownTestCase(){}
    protected:
        AttributeTest() : charges({1.1f,3.2f,1.0f}),points({{1.0f,3.0f,2.0f},{0.2f,0.1f,0.8f}}){}
        VertexAttribute<Point> v1{false,0};
        VertexAttribute<float> v2{false,1};
        std::vector<float> charges;
        std::vector<Point> points;
};

TEST_F(AttributeTest, VectorSizeRight) {
    ASSERT_EQ((int)charges.size(), 3);
    ASSERT_EQ((int)points.size(), 2);
}
TEST_F(AttributeTest,Float3CopiesToBuffer) {
    v1.setData(points);
    v1.bind();
    Point* raw_mem = (Point*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    Point* dat = new Point[2];
    std::copy(raw_mem, raw_mem+2,dat);
    ASSERT_FLOAT_EQ(dat[0].x,1.0f);
    ASSERT_FLOAT_EQ(dat[0].y,3.0f);
    ASSERT_FLOAT_EQ(dat[0].z,2.0f);
    ASSERT_FLOAT_EQ(dat[1].x,0.2f);
    ASSERT_FLOAT_EQ(dat[1].y,0.1f);
    ASSERT_FLOAT_EQ(dat[1].z,0.8f);
    delete[] dat;
}
TEST_F(AttributeTest,FloatCopiesToBuffer) {
    v2.setData(charges);
    v2.bind();
    float* raw_mem = (float*)glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);
    float* dat = new float[3];
    std::copy(raw_mem,raw_mem+3,dat);
    ASSERT_FLOAT_EQ(dat[0],1.1f);
    ASSERT_FLOAT_EQ(dat[1],3.2f);
    ASSERT_FLOAT_EQ(dat[2],1.0f);
}
TEST_F(AttributeTest,RanksCorrect) {
    ASSERT_EQ(v1.getRank(),3);
    ASSERT_EQ(v2.getRank(),1);
}
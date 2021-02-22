#include <gtest/gtest.h>
#include <graphics/attribute.h>
#include <computation/plottermath.h>

#include <vector>

class AttributeTest : public ::testing::Test {
    //public:
    //virtual void SetUpTestCase(){}
    //virtual void TearDownTestCase(){}
    protected:
        AttributeTest() : charges({1.1f,3.2f,1.0f}),points({{1.0f,3.0f,2.0f},{0.2f,0.1f,0.8f}}) {
            v1 = VertexAttribute::create<Point>(0, 0, 0);
            v2 = VertexAttribute::create<float>(0, points.size() * sizeof(Point), 0);
        }
        VertexBuffer buffer;
        VertexAttribute v1;
        VertexAttribute v2;
        std::vector<float> charges;
        std::vector<Point> points;
};

TEST_F(AttributeTest, VectorSizeRight) {
    ASSERT_EQ((int)charges.size(), 3);
    ASSERT_EQ((int)points.size(), 2);
}
TEST_F(AttributeTest,Float3CopiesToBuffer) {
    buffer.setAndAllocateData(&points[0], points.size(), (size_t)0);
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
TEST_F(AttributeTest, Offsetswork) {
    buffer.resize(points.size() * sizeof(Point) + charges.size() * sizeof(float));
    buffer.setData(&points[0], points.size(), (size_t)0);
    buffer.setData(&charges[0], charges.size(), points.size() * sizeof(Point));
    float* raw_mem = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    float* new_charges = new float[3];
    Point* new_points = new Point[3];
    std::copy(raw_mem, raw_mem + 2 * 3, (float*)new_points);         //there are 2 points
    std::copy(raw_mem + 6, raw_mem + 9, new_charges);
    ASSERT_FLOAT_EQ(new_charges[0], 1.1f);
    ASSERT_FLOAT_EQ(new_charges[1], 3.2f);
    ASSERT_FLOAT_EQ(new_charges[2], 1.0f);

    ASSERT_FLOAT_EQ(1.0f,new_points[0].x);
    ASSERT_FLOAT_EQ(3.0f,new_points[0].y);
    ASSERT_FLOAT_EQ(2.0f,new_points[0].z);
    ASSERT_FLOAT_EQ(0.2f,new_points[1].x);
    ASSERT_FLOAT_EQ(0.1f,new_points[1].y);
    ASSERT_FLOAT_EQ(0.8f,new_points[1].z);
    delete[] new_charges;
    delete[] new_points;
    glUnmapBuffer(GL_ARRAY_BUFFER);
}
TEST_F(AttributeTest,FloatCopiesToBuffer) {
    buffer.setAndAllocateData(&charges[0], charges.size(), (size_t)0);
    float* raw_mem = (float*)glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);
    float* dat = new float[3];
    std::copy(raw_mem,raw_mem+3,dat);
    ASSERT_FLOAT_EQ(dat[0],1.1f);
    ASSERT_FLOAT_EQ(dat[1],3.2f);
    ASSERT_FLOAT_EQ(dat[2],1.0f);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    delete[] dat;
}
TEST_F(AttributeTest,RanksCorrect) {
    ASSERT_EQ(v1.getRank(),3);
    ASSERT_EQ(v2.getRank(),1);
}
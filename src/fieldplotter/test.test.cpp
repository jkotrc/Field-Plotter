#include <gtest/gtest.h>


TEST(BuildSystem, TestSetupCorrectly) {
    ASSERT_EQ(1,1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

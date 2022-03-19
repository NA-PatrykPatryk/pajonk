#include "gtest/gtest.h"



TEST(SampleTest, shouldPass) 
{
    EXPECT_EQ(0, 0);
}

TEST(SampleTest, shouldNotPass) 
{
    EXPECT_EQ(1, 0);
}

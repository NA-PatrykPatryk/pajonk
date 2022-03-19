#include "gtest/gtest.h"
#include "Board.hpp"



TEST(boardTest, whenBoardIsInitializedItsSizeShouldBe20) 
{
    Board sut;
    EXPECT_EQ(sut.size(), 20);
}

TEST(boardTest, whenBoardIsInitializedWith5ItsSizeShouldBe5) 
{
    Board sut(5);
    EXPECT_EQ(sut.size(), 5);
}
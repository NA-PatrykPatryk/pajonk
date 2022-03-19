#include "gtest/gtest.h"
#include "Board.hpp"


struct boardTest :public ::testing::Test
{
    Board boardSut;
};


TEST_F(boardTest, whenBoardIsInitializedItsSizeShouldBe20) 
{
    EXPECT_EQ(boardSut.size(), 20);
}

TEST_F(boardTest, whenBoardIsInitializedWith5ItsSizeShouldBe5) 
{
    Board sut(5);
    EXPECT_EQ(sut.size(), 5);
}

TEST_F(boardTest, whenBoardIsInitializedItShouldContainDots) 
{
    EXPECT_EQ(boardSut.at(0,0), '.');
}

TEST_F(playerTest, WhenInitThenPlayerPositionIsStart)
{
	std::vector<int> startPosition{0, 0};
	Player sut{startPosition};
	EXPECT_EQ(sut.position(), startPosition);
}

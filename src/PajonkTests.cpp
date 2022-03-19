#include "gtest/gtest.h"
#include "Board.hpp"
#include<vector>

using Position = std::vector<int>;

struct Player {
	Player(Position startPosition) : m_position(startPosition) {}
	Position getPosition() {return m_position;}
	private:
	Position m_position;
};

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

TEST(playerTest, WhenInitThenPlayerPositionIsStart)
{
	Position startPosition{0, 0};
	Player sut{startPosition};
	EXPECT_EQ(sut.getPosition(), startPosition);
}

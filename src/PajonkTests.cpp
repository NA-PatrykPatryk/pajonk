#include "gtest/gtest.h"
#include "Board.hpp"
#include "Player.hpp"

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

TEST_F(boardTest, whenBoardHasSize2ReturnCorrectBoard)
{
    Board sut{ 2 };
    std::string field{ "..\n"
                       "..\n" };
    EXPECT_EQ(sut.getBoard(), field);
}

// ----------------------------------------------

TEST(playerTest, WhenInitThenPlayerPositionIsStart)
{
	Position startPosition{0, 0};
	Player sut{startPosition};
	EXPECT_EQ(sut.getPosition(), startPosition);
}

// TEST(playerTest, WhenMoveUPThenPositionChanges)
// {
// 	Position startPosition{0, 0};
// 	Player sut{startPosition};

// 	sut.moveUp();

// 	Position endPosition{0, 1};
// 	EXPECT_EQ(sut.getPosition(), endPosition);
// }

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
    EXPECT_EQ(boardSut.at(0,0), SYMBOL::EMPTY);
}

TEST_F(boardTest, whenBoardHasSize2ReturnCorrectBoard)
{
    Board sut{ 2 };
    std::string field{ "..\n"
                       "..\n" };
    EXPECT_EQ(sut.getBoard(), field);
}

TEST_F(boardTest, whenInputtedMarkAt00ItIsStoredCorrectly)
{
    Board sut{ 2 };
    std::string field{ "..\n"
                       "O.\n" };
    sut.at(0, 0) = SYMBOL::HEAD;
    EXPECT_EQ(sut.getBoard(), field);
}

TEST_F(boardTest, whenRequestedTurnsTailIntoBodyIn1By1Board)
{
    Board sut{ 1 };
    sut.at(0, 0) = SYMBOL::TAIL;
    sut.makePermanent();
    EXPECT_EQ(sut.at(0, 0), SYMBOL::BODY);
}

TEST_F(boardTest, whenRequestedTurnsTailIntoBodyIn3By3Board)
{
    Board sut{ 3 };
    sut.at(0, 0) = SYMBOL::TAIL;
    sut.at(1, 0) = SYMBOL::TAIL;
    sut.at(2, 0) = SYMBOL::TAIL;
    sut.at(2, 1) = SYMBOL::TAIL;
    sut.makePermanent();
    std::string field{ "...\n"
                       "..X\n"
                       "XXX\n" };
    EXPECT_EQ(sut.getBoard(), field);
}

TEST_F(boardTest, whenFillIsCalledItFillsEmptyTileSurroundedByBody)
{
    Board sut{ 3 };
    sut.at(0, 0) = SYMBOL::BODY;
    sut.at(0, 1) = SYMBOL::BODY;
    sut.at(0, 2) = SYMBOL::BODY;
    sut.at(1, 0) = SYMBOL::BODY;
    sut.at(1, 2) = SYMBOL::BODY;
    sut.at(2, 0) = SYMBOL::BODY;
    sut.at(2, 1) = SYMBOL::BODY;
    sut.at(2, 2) = SYMBOL::BODY;
    sut.fill(1, 1);
    std::string field{ "XXX\n"
                       "XXX\n"
                       "XXX\n" };
    EXPECT_EQ(sut.getBoard(), field);
}

TEST_F(boardTest, whenFillIsCalledItFillsEmptyTilesSurroundedByBody)
{
    Board sut{ 5 };
    sut.at(0, 0) = SYMBOL::BODY;
    sut.at(1, 0) = SYMBOL::BODY;
    sut.at(2, 0) = SYMBOL::BODY;
    sut.at(3, 0) = SYMBOL::BODY;
    sut.at(4, 0) = SYMBOL::BODY;
    sut.at(0, 1) = SYMBOL::BODY;
    sut.at(4, 1) = SYMBOL::BODY;
    sut.at(0, 2) = SYMBOL::BODY;
    sut.at(4, 2) = SYMBOL::BODY;
    sut.at(0, 3) = SYMBOL::BODY;
    sut.at(1, 3) = SYMBOL::BODY;
    sut.at(2, 3) = SYMBOL::BODY;
    sut.at(3, 3) = SYMBOL::BODY;
    sut.at(4, 3) = SYMBOL::BODY;
    std::string field1{ ".....\n"
                        "XXXXX\n"
                        "X...X\n"
                        "X...X\n"
                        "XXXXX\n" };
    EXPECT_EQ(sut.getBoard(), field1);
    sut.fill(1, 1);
    std::string field2{ ".....\n"
                        "XXXXX\n"
                        "XXXXX\n"
                        "XXXXX\n"
                        "XXXXX\n" };
    EXPECT_EQ(sut.getBoard(), field2);
}

TEST_F(boardTest, whenFieldIsSourroundedByBodyElementsReturnTrue)
{
    Board sut{ 3 };
    sut.at(0, 0) = SYMBOL::BODY;
    sut.at(0, 1) = SYMBOL::BODY;
    sut.at(0, 2) = SYMBOL::BODY;
    sut.at(1, 0) = SYMBOL::BODY;
    sut.at(1, 2) = SYMBOL::BODY;
    sut.at(2, 0) = SYMBOL::BODY;
    sut.at(2, 1) = SYMBOL::BODY;
    sut.at(2, 2) = SYMBOL::BODY;

    EXPECT_TRUE(sut.isSurrounded(1, 1));
}

TEST_F(boardTest, whenFieldIsNotSourroundedByBodyElementsReturnFalse)
{
    Board sut{ 5 };
    sut.at(0, 0) = SYMBOL::BODY;
    sut.at(1, 0) = SYMBOL::BODY;
    sut.at(2, 0) = SYMBOL::BODY;
    sut.at(3, 0) = SYMBOL::BODY;
    sut.at(4, 0) = SYMBOL::BODY;
    sut.at(0, 1) = SYMBOL::BODY;
    sut.at(4, 1) = SYMBOL::BODY;
    sut.at(0, 2) = SYMBOL::BODY;
    sut.at(4, 2) = SYMBOL::BODY;
    sut.at(0, 3) = SYMBOL::BODY;
    sut.at(1, 3) = SYMBOL::BODY;
    sut.at(2, 3) = SYMBOL::BODY;
    sut.at(3, 3) = SYMBOL::BODY;
    sut.at(4, 3) = SYMBOL::BODY;

    std::string field1{ ".....\n"
                        "XXXXX\n"
                        "X...X\n"
                        "X...X\n"
                        "XXXXX\n" };
    EXPECT_EQ(sut.getBoard(), field1);

    EXPECT_FALSE(sut.isSurrounded(1, 4));
    EXPECT_TRUE(sut.isSurrounded(1, 1));
}

TEST_F(boardTest, whenFieldIsNotSourroundedByBodyElements)
{
    Board sut{ 5 };
    sut.at(1, 0) = SYMBOL::BODY;
    sut.at(2, 0) = SYMBOL::BODY;
    sut.at(3, 0) = SYMBOL::BODY;

    sut.at(0, 1) = SYMBOL::BODY;
    sut.at(4, 1) = SYMBOL::BODY;

    sut.at(0, 2) = SYMBOL::BODY;
    sut.at(4, 2) = SYMBOL::BODY;

    sut.at(1, 3) = SYMBOL::BODY;
    sut.at(2, 3) = SYMBOL::BODY;
    sut.at(3, 3) = SYMBOL::BODY;

    std::string field1{ ".....\n"
                        ".XXX.\n"
                        "X...X\n"
                        "X...X\n"
                        ".XXX.\n" };
    EXPECT_EQ(sut.getBoard(), field1);

    EXPECT_TRUE(sut.isSurrounded(1, 1));
}

// ----------------------------------------------

TEST(playerTest, WhenInitThenPlayerPositionIsStart)
{
	Position startPosition{0, 0};
	Player sut{startPosition};
	EXPECT_EQ(sut.getPosition(), startPosition);
}

TEST(playerTest, WhenMoveUPThenPositionChanges)
{
	Position startPosition{0, 0};
	Player sut{startPosition};

	sut.setDirection(DIRECTION::UP);
    sut.move();

	Position endPosition{0, 1};
	EXPECT_EQ(sut.getPosition(), endPosition);
}

TEST(playerTest, WhenMoveUPRightDownLeftThenBackToStartPosition)
{
	Position startPosition{0, 0};
	Player sut{startPosition};

    sut.setDirection(DIRECTION::UP);
    sut.move();
    sut.setDirection(DIRECTION::RIGHT);
    sut.move();
    sut.setDirection(DIRECTION::DOWN);
    sut.move();
    sut.setDirection(DIRECTION::LEFT);
    sut.move();

	EXPECT_EQ(sut.getPosition(), startPosition);
}

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../include/Board.hpp"
#include "../include/Player.hpp"


/*
 * Tests for Board start here
 */

struct boardTest :public ::testing::Test
{
    Board boardSut;
};


TEST_F(boardTest, whenBoardIsInitializedItsSizeShouldBe10) 
{
    EXPECT_EQ(boardSut.size(), 10);
}

TEST_F(boardTest, whenBoardIsInitializedWith5ItsSizeShouldBe5) 
{
    Board sut(5);
    EXPECT_EQ(sut.size(), 5);
}

TEST_F(boardTest, whenBoardIsInitializedItShouldContainDots) 
{
    EXPECT_EQ(boardSut.at(0,0).m_symbol, SYMBOL::EMPTY);
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

TEST_F(boardTest, whenConstructorWithFieldStateInStringIsCalledCorrectBoardIsCreated)
{
    std::string field{ ".....\n"
                       ".XX..\n"
                       "X....\n"
                       "X....\n"
                       ".XX..\n" };
    Board sut(field);
    EXPECT_EQ(sut.getBoard(), field);
}

TEST_F(boardTest, whenRequestedTurnsTailIntoBodyIn1By1BoardUsingFillMethod)
{
    Board sut{ 1 };
    sut.at(0, 0) = SYMBOL::TAIL;
    sut.fill(COLOR::WHITE);
    EXPECT_EQ(sut.at(0, 0).m_symbol, SYMBOL::BODY);
}

TEST_F(boardTest, whenRequestedTurnsTailIntoBodyUsingFillMethod)
{
    std::string field1{ "...\n"
                        "..o\n"
                        "ooo\n" };
    Board sut{ field1 };

    sut.fill(COLOR::WHITE);
    std::string field2{ "...\n"
                        "..X\n"
                        "XXX\n" };
    EXPECT_EQ(sut.getBoard(), field2);
}

TEST_F(boardTest, whenFillIsCalledItFillsEmptyTileSurroundedByBody)
{
    std::string field1{ "XXX\n"
                        "X.X\n"
                        "XXX\n" };
    Board sut{ field1 };

    sut.fill(COLOR::WHITE);
    std::string field2{ "XXX\n"
                        "XXX\n"
                        "XXX\n" };
    EXPECT_EQ(sut.getBoard(), field2);
}

TEST_F(boardTest, whenFillIsCalledItFillsEmptyTilesSurroundedByBody)
{
    std::string field1{ ".....\n"
                        "XXXXX\n"
                        "X...X\n"
                        "X...X\n"
                        "XXXXX\n" };
    Board sut(field1);

    sut.fill(COLOR::WHITE);
    std::string field2{ ".....\n"
                        "XXXXX\n"
                        "XXXXX\n"
                        "XXXXX\n"
                        "XXXXX\n" };
    EXPECT_EQ(sut.getBoard(), field2);
}

TEST_F(boardTest, whenFillIsCalledItWillDetectAndFillAllEnclosedSpaces)
{
    std::string field1{ ".....\n"
                        ".XXX.\n"
                        "X...X\n"
                        "X...X\n"
                        ".XXX.\n" };
    Board sut(field1);

    sut.fill(COLOR::WHITE);
    std::string field2{ ".....\n"
                        ".XXX.\n"
                        "XXXXX\n"
                        "XXXXX\n"
                        ".XXX.\n" };

    EXPECT_EQ(sut.getBoard(), field2);
}

TEST_F(boardTest, whenUsingFillItMakesTailPermamentAndFillsAllSurroundedBlocks)
{
    Board sut(".....\n"
              ".XXX.\n"
              "X...o\n"
              "X...o\n"
              ".XXX.\n");

    sut.fill(COLOR::WHITE);

    std::string field2{ ".....\n"
                        ".XXX.\n"
                        "XXXXX\n"
                        "XXXXX\n"
                        ".XXX.\n" };
    EXPECT_EQ(sut.getBoard(), field2);
}

TEST_F(boardTest, whenBorderIsInNotMatchingColorsItWillNotBeFilled)
{
    std::string field{ ".....\n"
                       ".XXX.\n"
                       "X...X\n"
                       "X...X\n"
                       ".XXX.\n" };
    Board sut(field);

    sut.at(0, 1) = {SYMBOL::BODY, COLOR::RED};

    sut.fill(COLOR::WHITE);
    EXPECT_EQ(sut.getBoard(), field);
}

TEST_F(boardTest, whenBorderIsInMatchingColorsItWillBeFilled)
{
    std::string field1{ ".....\n"
                       ".XXX.\n"
                       "X...X\n"
                       "X...X\n"
                       ".XXX.\n" };
    Board sut(field1);
    
    sut.fill(COLOR::WHITE);

    std::string field2{ ".....\n"
                       ".XXX.\n"
                       "XXXXX\n"
                       "XXXXX\n"
                       ".XXX.\n" };
    EXPECT_EQ(sut.getBoard(), field2);
}

TEST_F(boardTest, whenPopulateIsCalledItWillMake3By3SquareWithGivenCordsAsCentre)
{
    std::string field1{ "...\n"
                        "...\n"
                        "...\n" };
    Board sut(field1);

    sut.populate(1, 1, COLOR::WHITE);
    std::string field2{ "XXX\n"
                        "XXX\n"
                        "XXX\n" };
    EXPECT_EQ(sut.getBoard(), field2);
}

/*
 * Tests for Board end here
 * Tests for Player start here
 */

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

TEST(playerTest, whenPlayerMovesItRemembersItsPreviousPosition)
{
	Position startPosition{0, 0};
	Player sut{startPosition};

    sut.setDirection(DIRECTION::UP);
    sut.move();
	EXPECT_EQ(sut.getPrevPosition(), startPosition);
}

TEST(playerTest, whenInitializedPlayerIsAssignedColorWhiteByDefault)
{
    Player sut({0, 0});
	EXPECT_EQ(sut.getColor(), COLOR::WHITE);
}

TEST(playerTest, whenAssignedPlayerRememberItsColor)
{
    Player sut({0, 0}, COLOR::RED);
	EXPECT_EQ(sut.getColor(), COLOR::RED);
}

/*
 * Tests for Player end here
 * Tests for Game start here
 */

// TEST(GameTest, whenGameIsSetupWithDefaultsItCreatesGivenField)
// {

// }

/////////

/*
// struct Input
// {
//     MOCK_METHOD(char, getInput, (), ());
// }

// TEST(someTest, whenStartPositionIs00AndDirectionIsUPAnd2MovesElapsedAndInputWasEMPTYANDRIGHTThenPositionIs02)
// {
//     Player sut({0, 0});
//     Input input;
//     sut.setDirection(DIRECTION::UP);
//     EXPECT_CALL(input, getInput)
//         .WillOnce().Return 0
//         .WillOnce().Return 'r';
//     sut.checkDirectionBasedOnInput(input);
//     sut.move();

//     sut.checkDirectionBasedOnInput(input);
//     sut.move();

//     Position endPos{1, 1};
//     EXPECT_EQ(sut.getPosition(), endPos);
// }
*/
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Board.hpp"
#include "Player.hpp"

#define DISPLAY 1

struct InputInterface {
	virtual char directionChange() = 0;
};

struct InputMock : InputInterface {
	MOCK_METHOD(char, directionChange, (), (override));
};

struct Tail {
	void addPosition(Position position);
	bool isCycle() {
		size_t maxSteps{m_positions.size() - 1};
		size_t steps = maxSteps;
		for(size_t i{0}; i < maxSteps; ++i) {
			if(m_positions.at(i) == m_positions.back()) {
				steps = i;
				break;
			}
		}
		return steps < maxSteps;
	}
	std::vector<Position> m_positions{};
};

struct Display {
	static constexpr size_t m_size = 6;
	static constexpr size_t m_allSize = m_size * m_size;
	static constexpr size_t m_allSizePlus = m_allSize + 1;
	Display() {clear();}
	void clear() {memset(m_pxl, '.', m_allSize); m_pxl[m_allSize] = 0;}
	void mark(Position element){
		m_pxl[element.m_y * m_size + element.m_x] = 'X';
	}
#ifdef DISPLAY
	void drawCurrent() {
		char frame[m_size + 3];
		memset(frame, '_', m_size + 2); frame[m_size + 2] = 0;
		std::cout << frame << std::endl;

		char tmp = m_pxl[m_allSize];
		m_pxl[m_allSize] = 0;
		for(size_t i{0}, rowStart{m_allSize - m_size}; i < m_size; ++i, rowStart -= m_size) {
			std::cout << '|' << &(m_pxl[rowStart]) << '|' << std::endl;
			m_pxl[rowStart + m_size] = tmp;
			tmp = m_pxl[rowStart];
			m_pxl[rowStart] = 0;
		}
		m_pxl[0] = tmp;

		memset(frame, '-', m_size + 2); frame[m_size + 2] = 0;
		std::cout << frame << std::endl;
	};
#else
	void drawCurrent() {}
#endif
	void mark(Tail) {}
	char m_pxl[m_allSizePlus];
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

TEST(playerTest, WhenPlayerInputDoesNotChangeDirectionThenDirectionDoesNotChange)
{
	Position startPosition{0, 0};
	Player sut{startPosition};
    sut.setDirection(DIRECTION::UP);

	char doNotChangeDirection = 0;
	InputMock input;
	EXPECT_CALL(input, directionChange())
		.WillOnce(testing::Return(doNotChangeDirection))
		.WillOnce(testing::Return(doNotChangeDirection));

	input.directionChange();
	sut.move();

    sut.setDirection(DIRECTION::RIGHT);
	input.directionChange();
	sut.move();

	Position endPositionExpected{1, 1};
	EXPECT_EQ(sut.getPosition(), endPositionExpected);
}

TEST(playerTest, WhenPlayerInputDoesChangeDirectionToRightWhenDirectionIsUpThenDirectionIsRight)
{
	Position startPosition{0, 0};
	Player sut{startPosition};
    sut.setDirection(DIRECTION::UP);

	InputMock input;
	char doChangeDirectionToRight = 'R';
	EXPECT_CALL(input, directionChange())
		.WillOnce(testing::Return(doChangeDirectionToRight));

	sut.move();

	sut.setDirectionBasedOnChange(input.directionChange());
	sut.move();

	Position endPositionExpected{1, 1};
	EXPECT_EQ(sut.getPosition(), endPositionExpected);
}

TEST(playerTest, RecognizeCycle) {
	Tail sut;
	sut.m_positions.push_back({0, 0});
	sut.m_positions.push_back({0, 1});
	sut.m_positions.push_back({0, 2});
	sut.m_positions.push_back({0, 3});
	sut.m_positions.push_back({1, 3});
	sut.m_positions.push_back({2, 3});
	sut.m_positions.push_back({2, 2});
	sut.m_positions.push_back({2, 1});
	sut.m_positions.push_back({1, 1});
	sut.m_positions.push_back({0, 1});

	EXPECT_TRUE(sut.isCycle());
}

TEST(playerTest, WhenThereIsNoCycleThenTailIsCycleReturnsFalse) {
	Tail sut;
	sut.m_positions.push_back({0, 0});
	sut.m_positions.push_back({0, 1});
	sut.m_positions.push_back({0, 2});
	sut.m_positions.push_back({0, 3});
	sut.m_positions.push_back({1, 3});
	sut.m_positions.push_back({2, 3});
	sut.m_positions.push_back({2, 2});
	sut.m_positions.push_back({2, 1});
	sut.m_positions.push_back({1, 1});

	EXPECT_FALSE(sut.isCycle());
}

TEST(playerTest, WhenPlayerMeetsHisTailThenHeDies)
{
	Display dspl;

	Position startPosition{0, 0};
	Player sut{startPosition};
	sut.setDirection(DIRECTION::UP);

	Tail tail;
	tail.m_positions.push_back(startPosition);
	dspl.mark(sut.getPosition()); dspl.drawCurrent();

	char doNotChangeDirection = 0;
	char doChangeDirectionToRight = 'R';
	char doChangeDirectionToDown = 'D';
	char doChangeDirectionToLeft = 'L';
	InputMock input;
	EXPECT_CALL(input, directionChange())
		.WillOnce(testing::Return(doNotChangeDirection))
		.WillOnce(testing::Return(doNotChangeDirection))
		.WillOnce(testing::Return(doNotChangeDirection))
		.WillOnce(testing::Return(doNotChangeDirection))
			.WillOnce(testing::Return(doChangeDirectionToRight))
		.WillOnce(testing::Return(doNotChangeDirection))
			.WillOnce(testing::Return(doChangeDirectionToDown))
		.WillOnce(testing::Return(doNotChangeDirection))
			.WillOnce(testing::Return(doChangeDirectionToLeft))
		.WillOnce(testing::Return(doNotChangeDirection));


	for(size_t i{0}; i < 9; ++i) {
		sut.setDirectionBasedOnChange(input.directionChange());
		sut.move();
		tail.m_positions.push_back(sut.getPosition());
		dspl.mark(sut.getPosition()); dspl.drawCurrent();
		EXPECT_FALSE(tail.isCycle());
	}

	sut.setDirectionBasedOnChange(input.directionChange());
	sut.move();
	tail.m_positions.push_back(sut.getPosition());
	dspl.mark(sut.getPosition()); dspl.drawCurrent();
	EXPECT_TRUE(tail.isCycle());
}

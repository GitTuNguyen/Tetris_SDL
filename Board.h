#pragma once
#include "ConstValue.h"
#include <cstdlib>
#include <ctime>

enum CellType {
	I = 1,
	L = 2,
	J = 3,
	S = 4,
	Z = 5,
	T = 6,
	O = 7,
	NONE,
	WALL
};
enum MoveType {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum GameResult {
	RUNING,
	END
};

struct Shape {
	CellType type;
	bool matrix[SIZE_SHAPE][SIZE_SHAPE];
	int x;
	int y;
	int size_Pixel;
};

class Board {
public:
	Board();
	void Reset();
	CellType** getBoardData();
	Shape getCurrentShape();
	GameResult getGameResult();
	void ConvertShape();
	bool CheckMoveValid(Shape i_currentShape, MoveType i_move);
	void Move(MoveType i_move);
	void UpdateBoard();
	void UpdateGameResult();
private:
	Shape m_currentShape;
	Shape m_nextShape;
	CellType** m_boardData;
	GameResult m_gameResult;
	Shape CreateNewShape();
	Shape Rotate(Shape i_shape);
	bool CheckRowFull(int i_row);
	int CollumsCollide(Shape i_shape);
	Shape m_shape[7] = {
			{CellType::I,
			{{1,1,1,1}
			,{0,0,0,0}
			,{0,0,0,0}
			,{0,0,0,0}},
			START_X , START_Y, SIZE_CELL},
			{CellType::L,
			{{1,0,0,0}
			,{1,0,0,0}
			,{1,1,0,0}
			,{0,0,0,0}},
			START_X, START_Y, SIZE_CELL},
			{CellType::J,
			{{0,1,0,0}
			,{0,1,0,0}
			,{1,1,0,0}
			,{0,0,0,0}},
			START_X, START_Y, SIZE_CELL},
			{CellType::S,
			{{0,1,1,0}
			,{1,1,0,0}
			,{0,0,0,0}
			,{0,0,0,0}},
			START_X, START_Y, SIZE_CELL},
			{CellType::Z,
			{{1,1,0,0}
			,{0,1,1,0}
			,{0,0,0,0}
			,{0,0,0,0}},
			START_X, START_Y, SIZE_CELL},
			{CellType::T,
			{{1,1,1,0}
			,{0,1,0,0}
			,{0,0,0,0}
			,{0,0,0,0}},
			START_X, START_Y, SIZE_CELL},
			{CellType::O,
			{{1,1,0,0}
			,{1,1,0,0}
			,{0,0,0,0}
			,{0,0,0,0}},
			START_X, START_Y, SIZE_CELL}
	};
};
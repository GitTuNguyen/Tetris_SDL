#pragma once
#include "GameDefinition.h"
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
	bool matrix[SHAPE_MATRIX_SIZE][SHAPE_MATRIX_SIZE];
	int x;
	int y;
	int height;
	int width;
};

class Board {
public:
	Board();
	~Board();
	void Reset();
	CellType** getBoardData();
	Shape getCurrentShape();
	Shape getNextShape();
	GameResult getGameResult();
	int getScore();
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
	int m_score;
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
			SHAPE_START_X , SHAPE_START_Y, 1, 4},
			{CellType::L,
			{{1,0,0,0}
			,{1,0,0,0}
			,{1,1,0,0}
			,{0,0,0,0}},
			SHAPE_START_X, SHAPE_START_Y, 3, 2},
			{CellType::J,
			{{0,1,0,0}
			,{0,1,0,0}
			,{1,1,0,0}
			,{0,0,0,0}},
			SHAPE_START_X, SHAPE_START_Y, 3, 2},
			{CellType::S,
			{{0,1,1,0}
			,{1,1,0,0}
			,{0,0,0,0}
			,{0,0,0,0}},
			SHAPE_START_X, SHAPE_START_Y, 2, 3},
			{CellType::Z,
			{{1,1,0,0}
			,{0,1,1,0}
			,{0,0,0,0}
			,{0,0,0,0}},
			SHAPE_START_X, SHAPE_START_Y, 2, 3},
			{CellType::T,
			{{1,1,1,0}
			,{0,1,0,0}
			,{0,0,0,0}
			,{0,0,0,0}},
			SHAPE_START_X, SHAPE_START_Y, 2, 3},
			{CellType::O,
			{{1,1,0,0}
			,{1,1,0,0}
			,{0,0,0,0}
			,{0,0,0,0}},
			SHAPE_START_X, SHAPE_START_Y, 2, 2}
	};
};
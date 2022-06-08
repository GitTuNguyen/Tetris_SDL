#include "Board.h"

Board::Board()
{
    Reset();
}

void Board::Reset()
{
    srand(time(NULL));
    m_boardData = (CellType**)malloc(sizeof(CellType*) * BOARD_RENDERER_ROW);
    for (int i = 0; i < BOARD_RENDERER_ROW; i++) {
        m_boardData[i] = (CellType*)malloc(sizeof(CellType) * BOARD_RENDERER_COL);
    }
    for (int x = 0; x < BOARD_RENDERER_ROW; x++)
    {
        for (int y = 0; y < BOARD_RENDERER_COL; y++)
        {
            if (x == 0 || x == BOARD_RENDERER_ROW - 1 || y == 0 || y == BOARD_RENDERER_COL - 1)
            {
                m_boardData[x][y] = CellType::WALL;
            }
            else {
                m_boardData[x][y] = CellType::NONE;
            }
        }
    }
    m_score = 0;
    m_gameResult = GameResult::RUNING;
    m_nextShape = CreateNewShape();
    ConvertShape();
}

Shape Board::CreateNewShape()
{
    Shape temp;
    temp = m_shape[rand() % 7];
    return temp;
}

void Board::ConvertShape()
{
    m_currentShape = m_nextShape;
    m_nextShape = CreateNewShape();
}

CellType** Board::getBoardData()
{
    return m_boardData;
}

Shape Board::getCurrentShape()
{
    return m_currentShape;
}

int Board::CollumsCollide(Shape i_shape)
{
    int count = 0;
    if (i_shape.y < 0) count += (0 - i_shape.y);
    if (i_shape.y + SIZE_SHAPE > BOARD_RENDERER_COL - 1) count += (i_shape.y + SIZE_SHAPE) - (BOARD_RENDERER_COL - 1);
    for (int i = 0; i < SIZE_SHAPE; i++)
    {
        for (int j = 0; j < SIZE_SHAPE; j++)
        {
            if (i_shape.matrix[i][j] != 0 && m_boardData[i + i_shape.x][j + i_shape.y] != CellType::NONE)
            {
                count++;
                break;
            }
        }
    }
    if (i_shape.y < 0) count += (0 - i_shape.y);
    if (i_shape.y + SIZE_SHAPE > BOARD_RENDERER_COL - 1) count += (i_shape.y + SIZE_SHAPE) - (BOARD_RENDERER_COL - 1);
    return count;
}
Shape Board::Rotate(Shape i_shape)
{
    if (i_shape.type == CellType::O) return i_shape;
    Shape temp = i_shape;
    for (int i = 0; i < SIZE_SHAPE; i++) {
        for (int j = 0; j < SIZE_SHAPE; j++) {
            temp.matrix[i][j] = i_shape.matrix[SIZE_SHAPE - j - 1][i];
        }
    }
    int collumsCollide = CollumsCollide(temp);
    int currentY = temp.y;
    temp.y = currentY - collumsCollide;
    if (CollumsCollide(temp))
    {
        temp.y = currentY + collumsCollide;
        if (CollumsCollide(temp))
        {
            return i_shape;
        }
        else {
            return temp;
        }
    }
    else {
        return temp;
    }
}
bool Board::CheckMoveValid(Shape i_currentShape, MoveType i_move)
{
    Shape temp = i_currentShape;
    if (i_move == MoveType::LEFT)
    {
        temp.y--; 
    }
    else if (i_move == MoveType::RIGHT)
    {
        temp.y++;
    }
    else if (i_move == MoveType::DOWN)
    {
        temp.x++;
    }
    for (int i = 0; i < SIZE_SHAPE; i++) {
        for (int j = 0; j < SIZE_SHAPE; j++) {
            if (temp.matrix[i][j] != 0 && m_boardData[i + temp.x][j + temp.y] != CellType::NONE)
            {
                return false;
            }
        }
    }
    return true;
}
void Board::Move(MoveType i_move)
{
    switch (i_move)
    {
    case MoveType::UP:
        m_currentShape = Rotate(m_currentShape);
            break;
    case MoveType::LEFT:
        if (CheckMoveValid(m_currentShape, i_move))
        {
            m_currentShape.y--;
        }
        break;
    case MoveType::RIGHT:
        if (CheckMoveValid(m_currentShape, i_move))
        {
            m_currentShape.y++;
        }
        break;
    case MoveType::DOWN:
        if (CheckMoveValid(m_currentShape, i_move))
        {
            m_currentShape.x++;
        }
        break;
    default:
        break;
    }
}

int Board::getScore()
{
    return m_score;
}

Shape Board::getNextShape()
{
    return m_nextShape;
}

GameResult Board::getGameResult()
{
    return m_gameResult;
}

bool Board::CheckRowFull(int i_row)
{
    for (int i = 1; i < BOARD_RENDERER_COL - 1; i++)
    {
        if (m_boardData[i_row][i] == CellType::NONE)
        {
            return false;
        }
    }
    return true;
}

void Board::UpdateBoard()
{
    for (int i = 0; i < SIZE_SHAPE; i++)
    {
        for (int j = 0; j < SIZE_SHAPE; j++)
        {
            if (m_currentShape.matrix[i][j] != 0)
            {
                m_boardData[m_currentShape.x + i][m_currentShape.y + j] = m_currentShape.type;
            }
        }
    }
    for (int i = 1; i < BOARD_RENDERER_ROW - 1; i++)
    {
        if (CheckRowFull(i))
        {
            m_score += 200;
            for (int j = 1; j < BOARD_RENDERER_COL - 1; j++)
            {
                m_boardData[i][j] = CellType::NONE;
            }
            if (i > 1)
            {
                for (int x = i; x > 1; x--)
                {
                    for (int y = 1; y < BOARD_RENDERER_COL - 1; y++)
                    {
                        m_boardData[x][y] = m_boardData[x - 1][y];
                    }
                }
            }
        }
    }
}

void Board::UpdateGameResult()
{
    for (int i = 0; i < SIZE_SHAPE; i++) {
        for (int j = 0; j < SIZE_SHAPE; j++) {
            if (m_nextShape.matrix[i][j] != 0 && m_boardData[i + START_X][j + START_Y] != CellType::NONE)
            {
                m_gameResult = GameResult::END;
                break;
            }
        }
    }
}
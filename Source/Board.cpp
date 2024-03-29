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
    m_gameResult = GameResult::START;
    m_nextShape = CreateNewShape();
}

void Board::StartGame()
{
    m_gameResult = GameResult::RUNNING;
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

bool Board::CheckShapeCollide(Shape i_shape)
{    
    for (int i = 0; i < SHAPE_MATRIX_SIZE; i++)
    {
        for (int j = 0; j < SHAPE_MATRIX_SIZE; j++)
        {
            if (i + i_shape.x <= BOARD_RENDERER_ROW && j + i_shape.y <= BOARD_RENDERER_COL)
            {
                if (i_shape.matrix[i][j] != 0 && m_boardData[i + i_shape.x][j + i_shape.y] != CellType::NONE)
                {
                    return true;
                }
            }
            else {
                return true;
            }
        }
    }
    return false;
}
Shape Board::Rotate(Shape i_shape)
{
    if (i_shape.type == CellType::O) return i_shape;
    Shape tempShape = i_shape;
    for (int i = 0; i < SHAPE_MATRIX_SIZE; i++) {
        for (int j = 0; j < SHAPE_MATRIX_SIZE; j++) {
            tempShape.matrix[i][j] = i_shape.matrix[SHAPE_MATRIX_SIZE - j - 1][i];
        }
    }
    tempShape.height = i_shape.width;
    tempShape.width = i_shape.height;
    tempShape.spaceLeft = i_shape.spaceBelow;
    tempShape.spaceRight = i_shape.spaceAbove;
    tempShape.spaceAbove = i_shape.spaceLeft;
    tempShape.spaceBelow = i_shape.spaceRight;
    int currentTempShapeX = tempShape.x;
    int currentTempShapeY = tempShape.y;
    if (CheckShapeCollide(tempShape))
    {
        for (int i = 1; i <= tempShape.spaceLeft + tempShape.width || i <= tempShape.spaceRight + tempShape.width || i <= tempShape.spaceBelow + tempShape.height; i++)
        {
            tempShape.x = currentTempShapeX;
            tempShape.y = currentTempShapeY - i;
            if (!CheckShapeCollide(tempShape))
            {
                return tempShape;
            }
            tempShape.x = currentTempShapeX;
            tempShape.y = currentTempShapeY + i;
            if (!CheckShapeCollide(tempShape))
            {
                return tempShape;
            }
            tempShape.x = currentTempShapeX - i;
            tempShape.y = currentTempShapeY;
            if (!CheckShapeCollide(tempShape))
            {
                return tempShape;
            }
        }
        return i_shape;        
    }
    else {
        return tempShape;
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
    for (int i = 0; i < SHAPE_MATRIX_SIZE; i++) {
        for (int j = 0; j < SHAPE_MATRIX_SIZE; j++) {
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
    for (int i = 0; i < SHAPE_MATRIX_SIZE; i++)
    {
        for (int j = 0; j < SHAPE_MATRIX_SIZE; j++)
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
    for (int i = 0; i < SHAPE_MATRIX_SIZE; i++) {
        for (int j = 0; j < SHAPE_MATRIX_SIZE; j++) {
            if (m_nextShape.matrix[i][j] != 0 && m_boardData[i + SHAPE_START_X][j + SHAPE_START_Y] != CellType::NONE)
            {
                m_gameResult = GameResult::END;
                break;
            }
        }
    }
}

Board::~Board()
{
    for (int i = 0; i < BOARD_RENDERER_ROW; i++)
    {
        delete m_boardData[i];
    }
}
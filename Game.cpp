#pragma once
#include "Game.h"
#include "Board.h"

Game::Game()
{
	m_board = new Board();
	m_renderer = new Renderer();
	m_isPlayerWantExit = false;
	LoadPicture();
}

void Game::LoadPicture()
{
	std::string file_name[8] = { "I", "L", "J", "S", "Z", "T", "O", "WALL"};
	for (int i = 0; i < sizeof(file_name) / sizeof(std::string); i++)
	{
		m_renderer->LoadTexture(file_name[i]);
	}
}

void Game::CreateNewMatch()
{
	m_board->Reset();
}
void Game::Rematch()
{
	char inputPlayer;
	std::cout << "Play again? (Y to play again, another key to quit): ";
	std::cin >> inputPlayer;
	if (inputPlayer == 'Y' || inputPlayer == 'y')
	{
		CreateNewMatch();
	}
	else {
		m_isPlayerWantExit = true;
	}
}
void Game::DrawBoard()
{
	CellType** boardData = m_board->getBoardData();
	for (int i = 0; i < BOARD_RENDERER_ROW; i++)
	{
		for (int j = 0; j < BOARD_RENDERER_COL; j++)
		{
			if (boardData[i][j] != CellType::NONE)
			{
				m_renderer->DrawCell(boardData[i][j], i, j);
			}
		}
	}
}

void Game::DrawNextShape()
{
	Shape nextShape = m_board->getNextShape();
	nextShape.x = Y_NEXT_SHAPE/SIZE_CELL + 1;
	nextShape.y = X_NEXT_SHAPE/SIZE_CELL;
	switch (nextShape.type)
	{
	case CellType::I:
		nextShape.y--;
		nextShape.x++;
		break;
	case CellType::Z:
		nextShape.y--;
		break;
	case CellType::T:
		nextShape.y--;
		break;
	default:
		break;
	}
	m_renderer->DrawShape(nextShape);
}

void Game::DrawScore()
{
	std::string scores_temp = std::to_string(m_board->getScore());
	std::string scores = "";
	for (int i = 0; i < 7 - scores_temp.length(); i++)
	{
		scores += "0";
	}
	scores += scores_temp;
	m_renderer->DrawText(scores, SIZE_NUMBER, X_SCORE, Y_SCORE , SCORE_HEIGHT, SCORE_WIDTH);
}

void Game::Update()
{
	Uint32 before = SDL_GetTicks(), after;
	while (!m_isPlayerWantExit)
	{
		m_renderer->PreRendering();
		DrawScore();
		DrawNextShape();
		GameResult gameResult = m_board->getGameResult();
		if (gameResult == GameResult::RUNING)
		{
			while (SDL_PollEvent(&mainEvent))
			{
				switch (mainEvent.type)
				{
				case SDL_QUIT:
				{
					m_isPlayerWantExit = true;
					break;
				}
				case SDL_KEYDOWN:
				{
					switch (mainEvent.key.keysym.sym)
					{
					case SDLK_UP:
					{
						m_board->Move(MoveType::UP);
						break;
					}
					case SDLK_DOWN:
					{
						m_board->Move(MoveType::DOWN);
						break;
					}
					case SDLK_LEFT:
					{
						m_board->Move(MoveType::LEFT);
						break;
					}
					case SDLK_RIGHT:
					{
						m_board->Move(MoveType::RIGHT);
						break;
					}
					default:
						break;
					}
				}
				default:
				{
					break;
				}
				}
			}
			after = SDL_GetTicks();
			if (after - before >= 500)
			{
				before = after;
				if (!m_board->CheckMoveValid(m_board->getCurrentShape(),MoveType::DOWN))
				{
					m_board->UpdateBoard();
					m_board->UpdateGameResult();
					m_board->ConvertShape();
				}
				else {
					m_board->Move(MoveType::DOWN);
				}
			}
			m_renderer->DrawShape(m_board->getCurrentShape());
			DrawBoard();
		}
		else {
			Rematch();
		}
		m_renderer->PostFrame();
	}
	m_renderer->CleanUp();
}
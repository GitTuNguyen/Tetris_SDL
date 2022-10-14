#pragma once
#include "Game.h"

Game::Game()
{
	m_board = new Board();
	m_renderer = new Renderer();
	m_inputManager = new InputManager();
	m_isPlayerWantExit = false;
	LoadPicture();
}

void Game::LoadPicture()
{
	std::vector<std::string> gameTextures = { "I", "L", "J", "S", "Z", "T", "O", "Wall", "YES", "NO"};
	for (int i = 0; i < gameTextures.size(); i++)
	{
		m_renderer->LoadTexture(gameTextures[i]);
	}
}

void Game::CreateNewGame()
{
	m_board->Reset();
	m_renderer->PreRendering();
	m_renderer->DrawScoreBoard();
	m_renderer->DrawNextShapeBoard();
	m_renderer->DrawCurrentShape(m_board->getCurrentShape());
	DrawScore();
	DrawNextShape();
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
				m_renderer->DrawCell(boardData[i][j], j * SIZE_CELL, i * SIZE_CELL);
			}
		}
	}
}

void Game::DrawNextShape()
{
	Shape nextShape = m_board->getNextShape();
	
	int nextShapePixelX = (X_NEXT_SHAPE_BOARD + (NEXT_SHAPE_BOARD_WIDTH - nextShape.width * SIZE_CELL * (float)(NEXT_SHAPE_SCALE)) / 2);
	int nextShapePixelY = (Y_NEXT_SHAPE_BOARD + (NEXT_SHAPE_BOARD_HEIGHT - nextShape.height * SIZE_CELL * (float)(NEXT_SHAPE_SCALE)) / 2); 
	for (int i = 0; i < SHAPE_MATRIX_SIZE; i++)
	{
		for (int j = 0; j < SHAPE_MATRIX_SIZE; j++)
		{
			if (nextShape.matrix[i][j] != 0)
			{
#ifdef  __ANDROID__
				m_renderer->DrawCell(nextShape.type, j * SIZE_CELL + nextShapePixelX, i * SIZE_CELL + nextShapePixelY, (float)NEXT_SHAPE_SCALE, i, j);
#else
				m_renderer->DrawCell(nextShape.type, j * SIZE_CELL + nextShapePixelX, i * SIZE_CELL + nextShapePixelY, (float)NEXT_SHAPE_SCALE);
#endif //  __ANDROID__
			}
		}
	}
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
		m_inputManager->UpdateInput();
		DrawBoard();
		m_renderer->DrawScoreBoard();
		m_renderer->DrawNextShapeBoard();
		m_renderer->DrawCurrentShape(m_board->getCurrentShape());
		DrawScore();
		DrawNextShape();
		m_isPlayerWantExit = m_inputManager->IsGoingToQuit();
		GameResult gameResult = m_board->getGameResult();
		if (gameResult == GameResult::START)
		{
			if (m_inputManager->IsMouseUp())
			{
				m_board->StartGame();
				m_board->ConvertShape();
			}
		}
		else if (gameResult == GameResult::RUNNING)
		{	
#ifndef __ANDROID__

			if (m_inputManager->IsKeyUpUp())
			{
				m_board->Move(MoveType::UP);
			}
			if (m_inputManager->IsKeyDownDown())
			{
				m_board->Move(MoveType::DOWN);
			}
			if (m_inputManager->IsKeyLeftDown())
			{
				m_board->Move(MoveType::LEFT);
			}
			if (m_inputManager->IsKeyRightDown())
			{
				m_board->Move(MoveType::RIGHT);
			}

#else
			if (m_inputManager->IsTap())
			{
				m_board->Move(MoveType::UP);
			}
			if (m_inputManager->IsSwipeToDown())
			{
				m_board->Move(MoveType::DOWN);
			}
			if (m_inputManager->IsSwipeToLeft())
			{
				m_board->Move(MoveType::LEFT);
			}
			if (m_inputManager->IsSwipeToRight())
			{
				m_board->Move(MoveType::RIGHT);
			}

#endif // !__ANDROID__						
			after = SDL_GetTicks();
			if (after - before >= 500)
			{
				before = after;
				if (!m_board->CheckMoveValid(m_board->getCurrentShape(),MoveType::DOWN))
				{
					m_board->UpdateBoard();
					m_board->UpdateGameResult();
					if (m_board->getGameResult() == GameResult::RUNNING)
					{
						m_board->ConvertShape();
					}					
				}
				else {
					m_board->Move(MoveType::DOWN);
				}
			}			
		}
		else {
			m_renderer->DrawGameOverPopup();
			int yesButtonX = (WINDOW_WIDTH - GAME_OVER_POPUP_WIDTH * SIZE_CELL) / 2 + SIZE_CELL * 2;
			int yesButtonY = (WINDOW_HEIGHT - GAME_OVER_POPUP_HEIGHT * SIZE_CELL) / 2 + SIZE_CELL * 3 + SIZE_CELL / 2;
			int noButtonX = yesButtonX + SIZE_CELL * 2;
			int noButtonY = yesButtonY;
			if (m_inputManager->IsMouseUp())
			{
				int mouseX = m_inputManager->GetMouseX();
				int mouseY = m_inputManager->GetMouseY();
				
				if (mouseX >= yesButtonX && mouseX <= yesButtonX + YES_BUTTON_WIDTH * SIZE_CELL && mouseY >= yesButtonY && mouseY <= yesButtonY + YES_BUTTON_HEIGHT * SIZE_CELL)
				{
					CreateNewGame();
				}
				else if (mouseX >= noButtonX && mouseX <= noButtonX + NO_BUTTON_WIDTH * SIZE_CELL && mouseY >= noButtonY && mouseY <= noButtonY + NO_BUTTON_HEIGHT * SIZE_CELL) 
				{
					m_isPlayerWantExit = true;
				}
			}
		}		
		m_renderer->PostFrame();
	}
	m_renderer->CleanUp();
}

Game::~Game()
{
	delete m_board;
	delete m_renderer;
	delete m_inputManager;
}
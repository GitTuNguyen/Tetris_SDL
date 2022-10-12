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
	std::vector<std::string> gameTextures = { "I", "L", "J", "S", "Z", "T", "O", "WALL", "YES", "NO"};
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
	m_renderer->DrawShape(m_board->getCurrentShape());
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
				m_renderer->DrawCell(boardData[i][j], i, j);
			}
		}
	}
}

void Game::DrawNextShape()
{
	Shape nextShape = m_board->getNextShape();
	
	nextShape.x = (Y_NEXT_SHAPE_BOARD / SIZE_CELL + (NEXT_SHAPE_BOARD_HEIGHT / SIZE_CELL - nextShape.height) / 2);
	nextShape.y = (X_NEXT_SHAPE_BOARD / SIZE_CELL + (NEXT_SHAPE_BOARD_WIDTH / SIZE_CELL - nextShape.width) / 2);
	
	m_renderer->DrawShape(nextShape, NEXT_SHAPE_SCALE);
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
		m_isPlayerWantExit = m_inputManager->IsGoingToQuit();
		DrawBoard();
		m_renderer->DrawScoreBoard();
		m_renderer->DrawNextShapeBoard();
		m_renderer->DrawShape(m_board->getCurrentShape());
		DrawScore();
		DrawNextShape();
		GameResult gameResult = m_board->getGameResult();
		if (gameResult == GameResult::RUNING)
		{			
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
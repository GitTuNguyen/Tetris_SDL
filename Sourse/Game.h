#pragma once
#include "Board.h"
#include "Renderer.h"
#include "InputManager.h"
#include <iostream>
class Game {
public:
	Game();
	void Update();
	~Game();
private:
	void LoadPicture();
	void DrawBoard();
	void DrawNextShape();
	void DrawScore();
	void CreateNewMatch();
	void Rematch();
	Board* m_board;
	Renderer* m_renderer;
	InputManager* m_inputManager;
	bool m_isPlayerWantExit;
	SDL_Event mainEvent;
};
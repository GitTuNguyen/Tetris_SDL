#pragma once
#include "Board.h"
#include "Renderer.h"
#include <iostream>
class Game {
public:
	Game();
	void Update();
private:
	void LoadPicture();
	void DrawBoard();
	void CreateNewMatch();
	void Rematch();
	Board* m_board;
	Renderer* m_renderer;
	bool m_isPlayerWantExit;
	SDL_Event mainEvent;
};
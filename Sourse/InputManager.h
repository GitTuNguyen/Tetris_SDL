#pragma once
#include "SDL.h"

class InputManager
{
public:
	InputManager();
	void UpdateInput();
	int GetMouseX();
	int GetMouseY();
	bool IsGoingToQuit();
	bool IsMouseUp();
	bool IsKeyDownDown();
	bool IsKeyUpUp();
	bool IsKeyLeftDown();
	bool IsKeyRightDown();
private:
	int m_mouseX;
	int m_mouseY;
	bool m_isGoingToQuit;
	bool m_isMouseUp;
	bool m_isKeyDownDown;
	bool m_isKeyUpUp;
	bool m_isKeyLeftDown;
	bool m_isKeyRightDown;
};
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
#ifndef __ANDROID__
	bool IsKeyDownDown();
	bool IsKeyUpUp();
	bool IsKeyLeftDown();
	bool IsKeyRightDown();
#else	
	bool IsTap();
	bool IsSwipeToLeft();
	bool IsSwipeToRight();
	bool IsSwipeToDown();
#endif // __ANDROID__

private:
	int m_mouseX;
	int m_mouseY;
	bool m_isGoingToQuit;
	bool m_isMouseUp;
#ifndef __ANDROID__
	bool m_isKeyDownDown;
	bool m_isKeyUpUp;
	bool m_isKeyLeftDown;
	bool m_isKeyRightDown;
#else
	bool m_isMouseDown;
	bool m_isTap;
	bool m_isSwipeToLeft;
	bool m_isSwipeToRight;
	bool m_isSwipeToDown;	
	int m_startSwipeX;
	int m_startSwipeY;
	int m_endSwipeX;
	int m_endSwipeY;
	int m_mouseDownX;
	int m_mouseDownY;
	int m_mouseUpX;
	int m_mouseUpY;	
#endif

};
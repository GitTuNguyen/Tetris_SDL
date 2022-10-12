#include "InputManager.h"

InputManager::InputManager()
{
	m_mouseX = 0;
	m_mouseY = 0;
	m_isGoingToQuit = false;
	m_isMouseUp = false;
	m_isKeyDownDown = false;
	m_isKeyUpUp = false;
	m_isKeyLeftDown = false;
	m_isKeyRightDown = false;
}

void InputManager::UpdateInput()
{
	m_isMouseUp = false;
	m_isKeyDownDown = false;
	m_isKeyUpUp = false;
	m_isKeyLeftDown = false;
	m_isKeyRightDown = false;
	SDL_Event mainEvent;
	m_mouseX = 0;
	m_mouseY = 0;
	while (SDL_PollEvent(&mainEvent))
	{
		switch (mainEvent.type)
		{
			case SDL_QUIT:
			{
				m_isGoingToQuit = true;
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				m_isMouseUp = false;
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				m_isMouseUp = true;
				m_mouseX = mainEvent.motion.x;
				m_mouseY = mainEvent.motion.y;
				break;
			}
			case SDL_KEYDOWN:
			{
				switch (mainEvent.key.keysym.sym)
				{
				case SDLK_DOWN:
				{
					m_isKeyDownDown = true;
					break;
				}
				case SDLK_UP:
				{
					m_isKeyUpUp = false;
					break;
				}
				case SDLK_LEFT:
				{
					m_isKeyLeftDown = true;
					break;
				}
				case SDLK_RIGHT:
				{
					m_isKeyRightDown = true;
					break;
				}
				default:
					break;
				}
			break;			
			}
			case SDL_KEYUP:
			{
				switch (mainEvent.key.keysym.sym)
				{
					case SDLK_UP:
					{
						m_isKeyUpUp = true;
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
}

int InputManager::GetMouseX()
{
	return m_mouseX;
}

int InputManager::GetMouseY()
{
	return m_mouseY;
}

bool InputManager::IsGoingToQuit()
{
	return m_isGoingToQuit;
}

bool InputManager::IsMouseUp()
{
	return m_isMouseUp;
}

bool InputManager::IsKeyDownDown()
{
	return m_isKeyDownDown;
}

bool InputManager::IsKeyUpUp()
{
	return m_isKeyUpUp;
}

bool InputManager::IsKeyLeftDown()
{
	return m_isKeyLeftDown;
}

bool InputManager::IsKeyRightDown()
{
	return m_isKeyRightDown;
}


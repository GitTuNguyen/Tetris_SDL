#include "InputManager.h"

InputManager::InputManager()
{
	m_mouseX = 0;
	m_mouseY = 0;
	m_isGoingToQuit = false;
	m_isMouseUp = false;
#ifndef __ANDROID__
	m_isKeyDownDown = false;
	m_isKeyUpUp = false;
	m_isKeyLeftDown = false;
	m_isKeyRightDown = false;
#else
	m_isMouseDown = false;
	m_isSwipeToLeft = false;
	m_isSwipeToRight = false;
	m_isSwipeToDown = false;
	m_startSwipeX = 0;
	m_startSwipeY = 0;
	m_endSwipeX = 0;
	m_endSwipeY = 0;
#endif // __ANDROID__

	
}

void InputManager::UpdateInput()
{
#ifndef __ANDROID__
	m_isKeyDownDown = false;
	m_isKeyUpUp = false;
	m_isKeyLeftDown = false;
	m_isKeyRightDown = false;
#else	
	m_isTap = false;
	m_isSwipeToLeft = false;
	m_isSwipeToRight = false;
	m_isSwipeToDown = false;
#endif // __ANDROID__
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
#ifdef __ANDROID__
				if (!m_isMouseDown)
				{
					m_mouseDownX = mainEvent.motion.x;
					m_mouseDownY = mainEvent.motion.y;
					m_startSwipeX = m_mouseDownX;
					m_startSwipeY = m_mouseDownY;
					m_isMouseDown = true;
				}
#endif __ANDROID__
				break;
			}
#ifdef __ANDROID__
			case SDL_MOUSEMOTION:
			{
				if (m_isMouseDown)
				{
					m_endSwipeX = mainEvent.motion.x;
					m_endSwipeY = mainEvent.motion.y;
					if (m_endSwipeX > m_startSwipeX && ((m_endSwipeY > m_startSwipeY && m_endSwipeX - m_startSwipeX > m_endSwipeY - m_startSwipeY) || (m_endSwipeY < m_startSwipeY && m_endSwipeX - m_startSwipeX > m_startSwipeY - m_endSwipeY)))
					{
						m_isSwipeToRight = true;
						m_startSwipeX = m_endSwipeX;
						m_startSwipeY = m_endSwipeY;
					}
					else if (m_endSwipeX < m_startSwipeX && ((m_endSwipeY > m_startSwipeY && m_startSwipeX - m_endSwipeX > m_endSwipeY - m_startSwipeY) || (m_endSwipeY < m_startSwipeY && m_startSwipeX - m_endSwipeX > m_startSwipeY - m_endSwipeY)))
					{
						m_isSwipeToLeft = true;
						m_startSwipeX = m_endSwipeX;
						m_startSwipeY = m_endSwipeY;
					}
					else if (m_endSwipeY > m_startSwipeY && ((m_endSwipeX > m_startSwipeX && m_endSwipeY - m_startSwipeY > m_endSwipeX - m_startSwipeX) || (m_endSwipeX < m_startSwipeX && m_endSwipeY - m_startSwipeY > m_startSwipeX - m_endSwipeX)))
					{
						m_isSwipeToDown = true;
						m_startSwipeX = m_endSwipeX;
						m_startSwipeY = m_endSwipeY;
					}
				}
				
				break;
			}
#endif // __ANDROID__
			
			case SDL_MOUSEBUTTONUP:
			{
				m_isMouseUp = true;
				m_mouseX = mainEvent.motion.x;
				m_mouseY = mainEvent.motion.y;
#ifdef  __ANDROID__
				m_mouseUpX = mainEvent.motion.x;
				m_mouseUpY = mainEvent.motion.y;
				m_isMouseDown = false;
				if (m_mouseUpX == m_mouseDownX && m_mouseUpY == m_mouseDownY)
				{
					m_isTap = true;
				}
				m_isSwipeToLeft = false;
				m_isSwipeToRight = false;
				m_isSwipeToDown = false;
				m_startSwipeX = 0;
				m_startSwipeY = 0;
				m_endSwipeX = 0;
				m_endSwipeY = 0;
#endif //  __ANDROID__

				break;
			}
#ifndef __ANDROID__
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
#endif
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

#ifdef __ANDROID__

bool InputManager::IsTap()
{
	return m_isTap;
}

bool InputManager::IsSwipeToLeft()
{
	return m_isSwipeToLeft;
}

bool InputManager::IsSwipeToRight()
{
	return m_isSwipeToRight;
}

bool InputManager::IsSwipeToDown()
{
	return m_isSwipeToDown;
}

#else

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

#endif // __ANDROID__






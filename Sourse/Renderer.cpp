#include "Renderer.h"
#ifndef __ANDROID__
#include <Windows.h>
#endif
#undef DrawText

Renderer::Renderer()
{
	//Hide console window
#ifndef __ANDROID__
	HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle, SW_HIDE);
#endif
	//Init
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return;
	}

	//Create window
	m_window = SDL_CreateWindow("Tetris - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		return;
	}

	//create a renderer
	m_sdlRenderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_sdlRenderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		return;
	}

	//Render in center of window
	SDL_RenderSetLogicalSize(m_sdlRenderer, WINDOW_WIDTH, WINDOW_HEIGHT);

	//Init ttf
	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		return;
	}
}

void Renderer::DrawCell(CellType i_cellType, int i_X, int i_Y, int i_scale)
{
	SDL_Rect newRect;
	newRect.w = (SIZE_CELL - 3) * i_scale;
	newRect.h = (SIZE_CELL - 3) * i_scale;
	newRect.x = i_Y * SIZE_CELL + 3;
	newRect.y = i_X * SIZE_CELL + 3;
	if (i_cellType == CellType::I)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["I"], NULL, &newRect);
	}
	else if (i_cellType == CellType::L)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["L"], NULL, &newRect);
	}
	else if (i_cellType == CellType::J)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["J"], NULL, &newRect);
	}
	else if (i_cellType == CellType::S)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["S"], NULL, &newRect);
	}
	else if (i_cellType == CellType::Z)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["Z"], NULL, &newRect);
	}
	else if (i_cellType == CellType::T)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["T"], NULL, &newRect);
	}
	else if (i_cellType == CellType::O)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["O"], NULL, &newRect);
	}
	else if (i_cellType == CellType::WALL)
	{
		SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["WALL"], NULL, &newRect);
	}
}

void Renderer::DrawShape(Shape i_shape, int i_scale)
{
	for (int i = 0; i < SHAPE_MATRIX_SIZE; i++)
	{
		for (int j = 0; j < SHAPE_MATRIX_SIZE; j++)
		{
			if (i_shape.matrix[i][j] != 0)
			{
				DrawCell(i_shape.type, i + i_shape.x, j + i_shape.y, i_scale);
			}
		}
	}
}

void Renderer::DrawText(std::string i_text, int i_size, int i_X, int i_Y, int i_H, int i_W)
{
	TTF_Font* font = TTF_OpenFont("Data/arial.ttf", i_size);
	SDL_Color White = { 255, 255, 255 };
	const char* renderText = i_text.c_str();
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, renderText, White);
	SDL_Texture* message = SDL_CreateTextureFromSurface(m_sdlRenderer, surfaceMessage);
	SDL_Rect Message_rect;
	Message_rect.x = i_X;
	Message_rect.y = i_Y;
	Message_rect.w = i_W;
	Message_rect.h = i_H;
	SDL_RenderCopy(m_sdlRenderer, message, NULL, &Message_rect);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}
void Renderer::DrawScoreBoard()
{
	SDL_SetRenderDrawColor(m_sdlRenderer, 255, 255, 255, 255);
	SDL_Point startPoint = { X_SCORE_BOARD, Y_SCORE_BOARD};
	SDL_Point endPoint = { X_SCORE_TEXT - 10, Y_SCORE_BOARD};
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	endPoint = { X_SCORE_BOARD, Y_SCORE_BOARD + SCORE_BOARD_HEIGHT};
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	startPoint = { X_SCORE_BOARD + SCORE_BOARD_WIDTH, Y_SCORE_BOARD};
	endPoint = {X_SCORE_TEXT + SCORE_TEXT_WIDTH + 10, Y_SCORE_BOARD};
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	endPoint = {startPoint.x, startPoint.y + SCORE_BOARD_HEIGHT};
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	startPoint = { X_SCORE_BOARD, endPoint.y };
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	std::string score_text = "SCORE";
	DrawText(score_text, TEXT_SIZE, X_SCORE_TEXT, Y_SCORE_TEXT, SCORE_TEXT_HEIGHT, SCORE_TEXT_WIDTH);
}

void Renderer::DrawNextShapeBoard()
{
	SDL_SetRenderDrawColor(m_sdlRenderer, 255, 255, 255, 255);
	SDL_Point startPoint = { X_NEXT_SHAPE_BOARD, Y_NEXT_SHAPE_BOARD};
	SDL_Point endPoint = { X_NEXT_SHAPE_TEXT - 10, startPoint.y };
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);

	endPoint = { startPoint.x, (startPoint.y + NEXT_SHAPE_BOARD_HEIGHT)};
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);

	startPoint = { X_NEXT_SHAPE_BOARD + NEXT_SHAPE_BOARD_WIDTH, Y_NEXT_SHAPE_BOARD};
	endPoint = { X_NEXT_SHAPE_TEXT + NEXT_SHAPE_TEXT_WIDTH + 10, startPoint.y };
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);

	endPoint = { startPoint.x, (startPoint.y + NEXT_SHAPE_BOARD_HEIGHT)};
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);

	startPoint = { X_NEXT_SHAPE_BOARD , endPoint.y };
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);

	std::string score_text = "NEXT";
	DrawText(score_text, TEXT_SIZE, X_NEXT_SHAPE_TEXT, Y_NEXT_SHAPE_TEXT, NEXT_SHAPE_TEXT_HEIGHT, NEXT_SHAPE_TEXT_WIDTH);
}

void Renderer::DrawGameOverPopup()
{

	SDL_Rect newRect;
	newRect.w = GAME_OVER_POPUP_WIDTH * SIZE_CELL;
	newRect.h = GAME_OVER_POPUP_HEIGHT * SIZE_CELL;
	newRect.x = (WINDOW_WIDTH - newRect.w) / 2;
	newRect.y = (WINDOW_HEIGHT - newRect.h) / 2;

	SDL_SetRenderDrawColor(m_sdlRenderer, 255, 255, 255, 255);

	SDL_Point startPoint = { newRect.x - 1, newRect.y - 1};
	SDL_Point endPoint = { startPoint.x, startPoint.y + newRect.h + 2};
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);

	endPoint = { newRect.x + newRect.w + 1, newRect.y - 1};
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);

	startPoint = { newRect.x + newRect.w + 1, newRect.y + newRect.h + 1};
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);

	endPoint = { newRect.x - 1, newRect.y + newRect.h + 1};
	SDL_RenderDrawLine(m_sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);

	SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255);

	SDL_RenderFillRect(m_sdlRenderer, &newRect);

	DrawText("GAME OVER", TEXT_SIZE * 2, newRect.x + ((GAME_OVER_POPUP_WIDTH - TEXT_GAME_OVER_WIDTH) * SIZE_CELL) / 2, newRect.y + SIZE_CELL / 2, TEXT_GAME_OVER_HEIGHT * SIZE_CELL, TEXT_GAME_OVER_WIDTH * SIZE_CELL);

	DrawText("PLAY AGAIN?", TEXT_SIZE, newRect.x + ((GAME_OVER_POPUP_WIDTH - TEXT_PLAY_AGAIN_WIDTH) * SIZE_CELL) / 2, newRect.y + SIZE_CELL * 2 + SIZE_CELL / 2, TEXT_PLAY_AGAIN_HEIGHT * SIZE_CELL, TEXT_PLAY_AGAIN_WIDTH * SIZE_CELL);

	newRect.x = newRect.x + SIZE_CELL * 2;
	newRect.y = newRect.y + SIZE_CELL * 3 + SIZE_CELL / 2;
	newRect.w = YES_BUTTON_WIDTH * SIZE_CELL;
	newRect.h = YES_BUTTON_HEIGHT * SIZE_CELL;


	SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["YES"], NULL, &newRect);

	newRect.x = newRect.x + SIZE_CELL * 2;
	newRect.y = newRect.y;
	newRect.w = NO_BUTTON_WIDTH * SIZE_CELL;
	newRect.h = NO_BUTTON_HEIGHT * SIZE_CELL;

	SDL_RenderCopy(m_sdlRenderer, m_loadedTextures["NO"], NULL, &newRect);
}

void Renderer::PreRendering()
{
	SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_sdlRenderer);
}

void Renderer::PostFrame()
{
	SDL_RenderPresent(m_sdlRenderer);
	SDL_Delay(16);
}

void Renderer::CleanUp()
{
	for (std::pair<std::string, SDL_Texture*> loadTexture : m_loadedTextures)
	{
		SDL_DestroyTexture(loadTexture.second);
	}
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_sdlRenderer);
	TTF_Quit();
	SDL_Quit();
}

void Renderer::LoadTexture(std::string i_ImageName)
{
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	std::string str = "Data/" + i_ImageName + ".bmp";
	tempSurface = SDL_LoadBMP(str.c_str());
	texture = SDL_CreateTextureFromSurface(m_sdlRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	m_loadedTextures.insert(std::pair<std::string, SDL_Texture*>(i_ImageName, texture));
}

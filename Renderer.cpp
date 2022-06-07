#include "Renderer.h"

Renderer::Renderer()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return;
	}

	//Create window
	m_window = SDL_CreateWindow("Tic And Toe - SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

}

void Renderer::DrawCell(CellType i_cellType, int i_X, int i_Y)
{
	SDL_Rect newRect;
	newRect.w = SIZE_CELL;
	newRect.h = SIZE_CELL;
	newRect.x = i_Y * SIZE_CELL;
	newRect.y = i_X * SIZE_CELL;
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

void Renderer::DrawShape(Shape i_shape)
{
	for (int i = 0; i < SIZE_SHAPE; i++)
	{
		for (int j = 0; j < SIZE_SHAPE; j++)
		{
			if (i_shape.matrix[i][j] != 0)
			{
				DrawCell(i_shape.type, i + i_shape.x, j + i_shape.y);
			}
		}
	}
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

	SDL_DestroyWindow(m_window);

	//Destroy a renderer
	SDL_DestroyRenderer(m_sdlRenderer);

	//cleans up all initialized subsystems
	SDL_Quit();
}

void Renderer::LoadTexture(std::string i_ImageName)
{
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* texture = NULL;
	std::string str = i_ImageName + ".bmp";
	tempSurface = SDL_LoadBMP(str.c_str());
	texture = SDL_CreateTextureFromSurface(m_sdlRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	m_loadedTextures.insert(std::pair<std::string, SDL_Texture*>(i_ImageName, texture));
}

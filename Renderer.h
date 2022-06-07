#pragma once
#include <SDL.h>
#include "Board.h"
#include <map>
#include <string>

class Renderer
{
public:
	Renderer();
	void DrawCell(CellType i_cellType, int i_pixelX, int i_pixelY);
	void DrawShape(Shape i_shape);
	void PostFrame();
	void CleanUp();
	void LoadTexture(std::string i_imageName);
	void PreRendering();
private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_sdlRenderer = NULL;
	std::map<std::string, SDL_Texture*> m_loadedTextures;
};
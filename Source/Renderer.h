#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Board.h"
#include <map>
#include <string>
class Renderer
{
public:
	Renderer();
	void DrawCell(CellType i_cellType, int i_pixelX, int i_pixelY, float i_scale = 1, int i_coordinateX = 0, int i_coordinateY = 0);
	void DrawCurrentShape(Shape i_shape, float i_scale = 1);
	void DrawText(std::string text, int i_size, int i_X, int i_Y, int i_H, int i_W);
	void DrawScoreBoard();
	void DrawNextShapeBoard();
	void DrawGameOverPopup();
	void PostFrame();
	void CleanUp();
	void LoadTexture(std::string i_imageName);
	void PreRendering();
private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_sdlRenderer = NULL;
	std::map<std::string, SDL_Texture*> m_loadedTextures;
};
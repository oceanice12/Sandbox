#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Entity.hpp"

class RenderWindow
{
public:
	explicit RenderWindow();
	explicit RenderWindow(int _w, int _h);
	inline int GetError() { return errorCode; }
	SDL_Texture* LoadTexture(const char* _filePath);
	void RenderEntity(Entity& _e);
	void RenderBackground(SDL_Texture *_pBackground);
	void ClearFrame();
	void DrawFrame();
	~RenderWindow();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width, height;
	int errorCode;
};


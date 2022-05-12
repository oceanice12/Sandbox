#include "RenderWindow.hpp"

using namespace std;

RenderWindow::RenderWindow() 
	: width(640), height(480), errorCode(0)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "FAILED TO INITIALIZE SDL. ERROR CODE: " << SDL_GetError() << "\n";
		errorCode = -1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		cout << "FAILED TO INITIALIZE IMG. ERROR CODE: " << SDL_GetError() << "\n";
		errorCode = -1;
	}

	window = SDL_CreateWindow("Sandbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, NULL);
	if (window == NULL)
	{
		cout << "FAILED TO CREATE WINDOW. ERROR CODE: " << SDL_GetError() << "\n";
		errorCode = -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		cout << "FAILED TO CREATE RENDERER. ERROR CODE: " << SDL_GetError() << "\n";
		errorCode = -1;
	}
}

RenderWindow::RenderWindow(int _w, int _h) 
	: width(_w), height(_h), errorCode(0)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "FAILED TO INITIALIZE SDL. ERROR CODE: " << SDL_GetError() << "\n";
		errorCode = -1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		cout << "FAILED TO INITIALIZE IMG. ERROR CODE: " << SDL_GetError() << "\n";
		errorCode = -1;
	}

	window = SDL_CreateWindow("Sandbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, NULL);
	if (window == NULL)
	{
		cout << "FAILED TO CREATE WINDOW. ERROR CODE: " << SDL_GetError() << "\n";
		errorCode = -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		cout << "FAILED TO CREATE RENDERER. ERROR CODE: " << SDL_GetError() << "\n";
		errorCode = -1;
	}
}

void RenderWindow::ClearFrame()
{
	if (SDL_RenderClear(renderer) < 0)
		cout << "Unable to clear renderer. Error Code: " << SDL_GetError() << "\n";
}

void RenderWindow::DrawFrame()
{
	SDL_RenderPresent(renderer);
}

SDL_Texture* RenderWindow::LoadTexture(const char* _filePath)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, _filePath);
	if (texture == NULL)
	{
		cout << "COULD NOT LOAD TEXTURE AT FILE PATH " << _filePath << "\n";
		errorCode = -2;
	}
	
	return texture;
}

void RenderWindow::RenderEntity(Entity& _e)
{
	SDL_Rect dst;
	dst.w = _e.GetSize().x;
	dst.h = _e.GetSize().y;
	dst.x = _e.ScreenPos().x;
	dst.y = _e.ScreenPos().y;

	if (SDL_RenderCopy(renderer, _e.GetTexture(), NULL, &dst) < 0)
	{
		cout << "COULD NOT COPY TEXTURE TO RENDERER. ERROR CODE: " << SDL_GetError() << "\n";
		errorCode = -2;
	}
}

void RenderWindow::RenderBackground(SDL_Texture *_pBackground)
{
	SDL_Rect src;
	src.h = SCREEN_HEIGHT;
	src.w = SCREEN_WIDTH;
	src.x = 0;
	src.y = 0;

	SDL_Rect dst;
	dst.h = SCREEN_HEIGHT;
	dst.w = SCREEN_WIDTH;
	dst.x = 0;
	dst.y = 0;

	if (SDL_RenderCopy(renderer, _pBackground, &src, &dst) < 0)
	{
		cout << "COULD NOT COPY TEXTURE TO RENDERER. ERROR CODE: " << SDL_GetError() << "\n";
		errorCode = -2;
	}
}

RenderWindow::~RenderWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
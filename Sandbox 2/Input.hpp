#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"
#include <vector>
#include "def.hpp"

struct Mouse
{
	int x, y;
	bool leftDown, rightDown;
	bool mouseDown;
	bool onScreen;
};

struct Keyboard
{
	bool space;
	bool one, two, three;
};

class Input
{
public:
	explicit Input();
	void PollEvent();
	void UpdateMouseState();

	bool Quit() const { return quit; }
	Mouse MouseState() const { return mouse; }
	bool ClearScreen() const { return key.space; }
	int SelectedEntityType() const { return currentEntityType; }
private:
	SDL_Event event;
	bool quit;
	Mouse mouse;
	Keyboard key;
	int currentEntityType;
};


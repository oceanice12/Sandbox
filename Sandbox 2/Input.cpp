#include "Input.hpp"

Input::Input()
	: quit(false), currentEntityType(SAND)
{
	mouse.leftDown = false;
	mouse.rightDown = false;
	mouse.mouseDown = false;
	mouse.onScreen = false;
	key.space = false;
	key.one = false;
	key.two = false;
	key.three = false;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	SDL_PollEvent(&event);
}


void Input::PollEvent()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse.leftDown = mouse.mouseDown = true;
				break;

			case SDL_BUTTON_RIGHT:
				mouse.rightDown = mouse.mouseDown = true;
				break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse.leftDown = mouse.mouseDown = false;
				break;

			case SDL_BUTTON_RIGHT:
				mouse.rightDown = mouse.mouseDown = false;
				break;
			}
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				key.space = true;
				break;

			case SDLK_1:
				key.one = true;
				currentEntityType = SAND;
				break;

			case SDLK_2:
				key.two = true;
				currentEntityType = STONE;
				break;

			case SDLK_3:
				key.three = true;
				currentEntityType = WATER;
				break;
			}
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				key.space = false;
				break;

			case SDLK_1:
				key.one = false;
				break;

			case SDLK_2:
				key.two = false;
				break;

			case SDLK_3:
				key.three = false;
				break;
			}
			break;
		}
	}
}

void Input::UpdateMouseState()
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
	mouse.onScreen = (mouse.x >= 0 && mouse.x < SCREEN_WIDTH && mouse.y >= 0 && mouse.y < SCREEN_HEIGHT);
}

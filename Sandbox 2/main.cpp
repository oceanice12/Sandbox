#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <array>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "def.hpp"
#include "Input.hpp"
#include "math.hpp"

using namespace std;

void PlaceEntity(array<array<Entity*, GRID_HEIGHT>, GRID_WIDTH> *_pGrid, vector<Entity> &_entities,
	vector<SDL_Texture*> _textures, const Input &_input);

void CreateFloor(array<array<Entity*, GRID_HEIGHT>, GRID_WIDTH>* _pGrid, vector<Entity>& _entities, vector<SDL_Texture*> _textures);

vector<SDL_Texture*> LoadAllTextures(RenderWindow& _renderer);

int main(int argc, char* argv[])
{
	// Initialize and error check all SDL systems
	RenderWindow window = RenderWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (window.GetError() != 0)
		return window.GetError();
	
	vector<SDL_Texture*> textures = LoadAllTextures(window);

	vector<Entity> entities = {};

	// A 2D array holding pointers to each entity at their respective grid coordinates
	array<array<Entity*, GRID_HEIGHT>, GRID_WIDTH> *pGrid = new array<array<Entity*, GRID_HEIGHT>, GRID_WIDTH>;
	for (auto& col : *pGrid)
	{
		col.fill(nullptr);
	}

	CreateFloor(pGrid, entities, textures);

	// Game loop
	for (Input input{}; !input.Quit();)
	{
		// Input handling
		{
			input.PollEvent();
			input.UpdateMouseState();

			if (input.MouseState().mouseDown && input.MouseState().onScreen)
				PlaceEntity(pGrid, entities, textures, input);

			if (input.ClearScreen())
			{
				for (auto& col : *pGrid)
				{
					col.fill(nullptr);
				}
				entities.clear();
				entities = vector<Entity>();
				CreateFloor(pGrid, entities, textures);
			}
		}

		// Frame update
		{
			window.ClearFrame();
			window.RenderBackground(textures[0]);
			for (auto& e : entities)
			{
				e.Update(pGrid);
				window.RenderEntity(e);
			}
			window.DrawFrame();
		}
	}

	// Close all initialized SDL systems
	window.~RenderWindow();
	return 0;
}




void PlaceEntity(array<array<Entity*, GRID_HEIGHT>, GRID_WIDTH> *_pGrid, vector<Entity> &_entities,
	vector<SDL_Texture*> _textures, const Input &_input)
{
	// Coordinates in grid units
	sVector2 gridPos{ static_cast<short>(_input.MouseState().x) / BLOCK_SIZE , static_cast<short>(_input.MouseState().y) / BLOCK_SIZE };

	// Cooridnates converted back to screen units
	sVector2 screenPos{ gridPos.x * BLOCK_SIZE , gridPos.y * BLOCK_SIZE };


	int type = _input.SelectedEntityType();

	if (type == NONE)
	{
		cout << "ERROR! CAN NOT PLACE ENTITY OF TYPE NONE." << '\n';
		return;
	}
	SDL_Texture *pTexture = _textures[type];

	if (_pGrid->at(gridPos.x).at(gridPos.y) == nullptr)
	{
		_entities.push_back(Entity(type, _textures[type], gridPos, screenPos));
		_pGrid->at(gridPos.x).at(gridPos.y) = &_entities.back();
	}
}

void CreateFloor(array<array<Entity*, GRID_HEIGHT>, GRID_WIDTH>* _pGrid, vector<Entity>& _entities, vector<SDL_Texture*> _textures)
{
	for (short i = 0; i < GRID_WIDTH; i++)
	{
		sVector2 gridPos{ i, GRID_HEIGHT - 1 }; 
		sVector2 screenPos{ i * BLOCK_SIZE, SCREEN_HEIGHT - BLOCK_SIZE };
		_entities.push_back(Entity(STONE, _textures[STONE], gridPos, screenPos));
		_pGrid->at(i).at(GRID_HEIGHT - 1) = &_entities.back();
	}
}

vector<SDL_Texture*> LoadAllTextures(RenderWindow &_renderer)
{
	SDL_Texture* pBackground = _renderer.LoadTexture("res/sky.png");
	SDL_Texture* pSandTexture = _renderer.LoadTexture("res/sand.png");
	SDL_Texture* pStoneTexture = _renderer.LoadTexture("res/stone.png");
	SDL_Texture* pWaterTexture = _renderer.LoadTexture("res/water.png");
	vector<SDL_Texture*> textures = { pBackground, pSandTexture, pStoneTexture, pWaterTexture };
	return textures;
}
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <array>
#include <iostream>
#include "def.hpp"
#include "math.hpp"

using namespace std;

enum Type
{
	NONE,
	SAND,
	STONE,
	WATER
};

class Entity
{
public:
	explicit Entity(short _type, SDL_Texture* _pTexture, sVector2 _gridPos, sVector2 _screenPos);
	void Update(array<array<Entity*, GRID_HEIGHT>, GRID_WIDTH> *_pGrid);

	SDL_Texture* GetTexture() const { return pTexture; }
	sVector2& GridPos() { return gridPos; }
	sVector2& ScreenPos() { return screenPos; }
	sVector2 GetSize() const { return size; }
	int GetType() const { return type; }
private:
	sVector2 gridPos, screenPos;
	sVector2 size;
	short type;
	SDL_Texture *pTexture;
};
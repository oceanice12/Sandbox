#include "Entity.hpp"


Entity::Entity(short _type, SDL_Texture *_pTexture, sVector2 _gridPos, sVector2 _screenPos) 
	: type(_type), pTexture(_pTexture), gridPos(_gridPos), screenPos(_screenPos), size{BLOCK_SIZE, BLOCK_SIZE} {}


void Entity::Update(array<array<Entity*, GRID_HEIGHT>, GRID_WIDTH> *_pGrid)
{
	// Boundary check
	if (gridPos.y + 1 >= GRID_HEIGHT || gridPos.y < 0 || gridPos.x + 1 > GRID_WIDTH || gridPos.x < 0)
		return;

	Entity *tl, *t, *tr;
	Entity *l,  *c,  *r;
	Entity *bl, *b, *br;
	// Create reference variables for the surrounding entities
	{
		c = this;
		tl = t = tr = l = r = bl = b = br = nullptr;

		// Check each surrounding grid space and if it is valid then grab a reference
		if (gridPos.y > 0 && gridPos.x > 0)
			tl = _pGrid->at(gridPos.x - 1).at(gridPos.y - 1);
		if (gridPos.y > 0)
			t = _pGrid->at(gridPos.x).at(gridPos.y - 1);
		if (gridPos.y > 0 && gridPos.x + 1 < GRID_WIDTH)
			tr = _pGrid->at(gridPos.x + 1).at(gridPos.y - 1);
		if (gridPos.x > 0)
			l = _pGrid->at(gridPos.x - 1).at(gridPos.y);
		if (gridPos.x + 1 < GRID_WIDTH)
			r = _pGrid->at(gridPos.x + 1).at(gridPos.y);
		if (gridPos.x > 0 && gridPos.y + 1 < GRID_HEIGHT)
			bl = _pGrid->at(gridPos.x - 1).at(gridPos.y + 1);
		if (gridPos.y + 1 < GRID_HEIGHT)
			b = _pGrid->at(gridPos.x).at(gridPos.y + 1);
		if (gridPos.x + 1 < GRID_WIDTH && gridPos.y + 1 < GRID_HEIGHT)
			br = _pGrid->at(gridPos.x + 1).at(gridPos.y + 1);
	}

	_pGrid->at(gridPos.x).at(gridPos.y) = nullptr;


	switch (type)
	{
	case SAND:
	{		
		// Gravity
		if (b == nullptr)
		{
			gridPos.y++;
			screenPos.y += BLOCK_SIZE;
		}
		// Sink in water
		// There is a bug where the game will sometimes crash when you dereference an entity at the bottom of the screen
		// I put in an edge case check to not check for the floor type
		else if (gridPos.y != GRID_HEIGHT - 2 && b->GetType() == WATER)
		{
			
			b->GridPos() = gridPos;
			b->ScreenPos() = screenPos;
			
			if (_pGrid->at(gridPos.x + 1).at(gridPos.y) == nullptr)
			{
				b->GridPos().x += 1;
				b->ScreenPos().x += BLOCK_SIZE;
			}
			else if (_pGrid->at(gridPos.x - 1).at(gridPos.y) == nullptr)
			{
				b->GridPos().x -= 1;
				b->ScreenPos().x -= BLOCK_SIZE;
			}

			_pGrid->at(b->GridPos().x).at(b->GridPos().y) = b;
			
			gridPos.y++;
			screenPos.y += BLOCK_SIZE;
		}
		// Fall to the right
		else if (r == nullptr && br == nullptr && gridPos.x + 1 < GRID_WIDTH)
		{
			if (b->GetType() == SAND)
			{
				gridPos.y++;
				screenPos.y += BLOCK_SIZE;
			}
			gridPos.x++;
			screenPos.x += BLOCK_SIZE;
		}
		// Fall to the left
		else if (l == nullptr && bl == nullptr && gridPos.x - 1 >= 0)
		{
			if (b->GetType() == SAND)
			{
				gridPos.y++;
				screenPos.y += BLOCK_SIZE;
			}
			gridPos.x--;
			screenPos.x -= BLOCK_SIZE;
		}
	}
		break;
		
	case STONE:
		break;

	case WATER:
	{
		// Gravity
		if (b == nullptr)
		{
			gridPos.y++;
			screenPos.y += BLOCK_SIZE;
		}
		// Fall to the right
		else if (r == nullptr && br == nullptr && gridPos.x + 1 < GRID_WIDTH)
		{
			if (b->GetType() == WATER)
			{
				gridPos.y++;
				screenPos.y += BLOCK_SIZE;
			}
			gridPos.x++;
			screenPos.x += BLOCK_SIZE;
		}
		// Fall to the left
		else if (l == nullptr && bl == nullptr && gridPos.x - 1 >= 0)
		{
			if (b->GetType() == WATER)
			{
				gridPos.y++;
				screenPos.y += BLOCK_SIZE;
			}
			gridPos.x--;
			screenPos.x -= BLOCK_SIZE;
		}
		// Prioritize moving left or right depending on if there is an empty grid space in the row below
		else if (bl != nullptr && b != nullptr && br != nullptr)
		{
			unsigned int leftDistance = GRID_WIDTH;
			unsigned int rightDistance = GRID_WIDTH;
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				if (x != GRID_WIDTH - 1 && _pGrid->at(x).at(gridPos.y + 1) == nullptr && _pGrid->at(x + 1).at(gridPos.y + 1) != nullptr)
					leftDistance = gridPos.x - x;
				else if (x != 0 && _pGrid->at(x).at(gridPos.y + 1) == nullptr && _pGrid->at(x - 1).at(gridPos.y + 1) != nullptr)
					rightDistance = x - gridPos.x;
			}

			if (rightDistance < leftDistance && r == nullptr)
			{
				gridPos.x++;
				screenPos.x += BLOCK_SIZE;
			}
			else if (leftDistance < rightDistance && l == nullptr)
			{
				gridPos.x--;
				screenPos.x -= BLOCK_SIZE;
			}
			
		}
	}
		break;
	}

	_pGrid->at(gridPos.x).at(gridPos.y) = this;
}

#include "header.h"

#include "Demo2TileManager.h"

Demo2TileManager::Demo2TileManager(void)
{
}

Demo2TileManager::~Demo2TileManager(void)
{
}

// Get the size of a tile - width
int Demo2TileManager::GetTileWidth()
{
	return 50;
}

// Get the size of a tile - height
int Demo2TileManager::GetTileHeight()
{
	return 50;
}

// Draw a tile at a location on the screen determined by the tile
// position and the base X and Y co-ordinates
// OVERRIDE THIS TO DRAW YOUR TILE!!!
// Draw a tile
void Demo2TileManager::DrawTileAt( 
	BaseEngine* pEngine, 
	SDL_Surface* pSurface, 
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY )
{
	// Base class implementation just draws some grey tiles
	pEngine->DrawRectangle( 
		iStartPositionScreenX,
		iStartPositionScreenY, 
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		pEngine->GetColour( GetValue(iMapX,iMapY) ),
		pSurface );
}

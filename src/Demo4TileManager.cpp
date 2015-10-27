#include "header.h"

#include "Demo4TileManager.h"

Demo4TileManager::Demo4TileManager(void)
{
}

Demo4TileManager::~Demo4TileManager(void)
{
}

// Get the size of a tile - width
int Demo4TileManager::GetTileWidth()
{
	return 50;
}

// Get the size of a tile - height
int Demo4TileManager::GetTileHeight()
{
	return 50;
}

// Draw a tile at a location on the screen determined by the tile
// position and the base X and Y co-ordinates
// OVERRIDE THIS TO DRAW YOUR TILE!!!
// Draw a tile
void Demo4TileManager::DrawTileAt( 
	BaseEngine* pEngine, 
	SDL_Surface* pSurface, 
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY )
{
	// Base class implementation just draws some grey tiles
/*
pEngine->DrawRectangle( 
		iStartPositionScreenX,
		iStartPositionScreenY, 
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		pEngine->GetColour( GetValue(iMapX,iMapY) ),
		pSurface );
*/

	// Base class implementation just draws some grey tiles
	switch( GetValue(iMapX,iMapY) )
	{
	case 0:
	case 1:
		pEngine->DrawRectangle( 
			iStartPositionScreenX,
			iStartPositionScreenY, 
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour( GetValue(iMapX,iMapY) ),
			pSurface );
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		pEngine->DrawRectangle( 
			iStartPositionScreenX,
			iStartPositionScreenY, 
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour( 0 ),
			pSurface );
		pEngine->DrawOval( 
			iStartPositionScreenX+GetValue(iMapX,iMapY)*2+5,
			iStartPositionScreenY+GetValue(iMapX,iMapY)*2+5, 
			iStartPositionScreenX + GetTileWidth() - GetValue(iMapX,iMapY)*2 -6,
			iStartPositionScreenY + GetTileHeight() - GetValue(iMapX,iMapY)*2 -6,
			pEngine->GetColour( GetValue(iMapX,iMapY) ),
			pSurface );
		break;
	}
}

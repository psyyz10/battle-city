#pragma once

#include "BaseEngine.h"

class TileManager
{
public:
	// Constructor
	TileManager(void)
		: m_pData(NULL)
		, m_iMapWidth(0)
		, m_iMapHeight(0)
		, m_iBaseScreenX(0)
		, m_iBaseScreenY(0)
	{
	}

	// Destructor
	~TileManager(void)
	{
		if ( m_pData != NULL )
			delete [] m_pData;
		m_pData = NULL;
	}

	// Re-size, and zero all values
	void SetSize(int iMapWidth, int iMapHeight)
	{
		if ( m_pData != NULL )
			delete [] m_pData;
		// Set up the map data
		m_pData = new int[iMapWidth*iMapHeight];
		m_iMapWidth = iMapWidth;
		m_iMapHeight = iMapHeight;
		memset( m_pData, 0, sizeof(int)*iMapWidth*iMapHeight );
	}

	// Get a value for a specific tile
	int GetValue(int iMapX, int iMapY)
	{
		return m_pData[ iMapX + iMapY * m_iMapWidth ];
	}

	// Set the value of a specific tile
	void SetValue(int iMapX, int iMapY, int iValue)
	{
		m_pData[ iMapX + iMapY * m_iMapWidth ] = iValue;
	}

// The following functions use a base tile position, to avoid needing to pass the offset each time

	// You can specify whereabouts on the screen the map should appear
	void SetBaseTilesPositionOnScreen( int iScreenX, int iScreenY )
	{
		m_iBaseScreenX = iScreenX;
		m_iBaseScreenY = iScreenY;
	}

	// Using the base tiles position, work out which tile the point is over
	int GetTileXForPositionOnScreen( int iScreenX )
	{
		return (iScreenX - m_iBaseScreenX)/GetTileWidth();
	}

	// Using the base tiles position, work out which tile the point is over
	int GetTileYForPositionOnScreen( int iScreenY )
	{
		return (iScreenY - m_iBaseScreenY)/GetTileHeight();
	}

	// Determine whether a screen position is inside the current tiled area
	// Assuming that the base position has been initialised
	bool IsValidTilePosition( int iScreenX, int iScreenY )
	{
		if ( iScreenX < m_iBaseScreenX )
			return false;
		if ( iScreenY < m_iBaseScreenY )
			return false;
		if ( iScreenX >= ( m_iBaseScreenX + GetTileWidth() * m_iMapWidth ) )
			return false;
		if ( iScreenY >= ( m_iBaseScreenY + GetTileHeight() * m_iMapHeight ) )
			return false;
		return true;
	}

	// Update a tile at a location on the screen determined by the tile
	// position and the base X and Y co-ordinates
	void UpdateTile( BaseEngine* pEngine, 
		int iMapX, int iMapY,	int iNewTileValue )
	{
		UpdateTileAt( pEngine, iMapX, iMapY, iNewTileValue,
				m_iBaseScreenX + iMapX*GetTileWidth(), 
				m_iBaseScreenY + iMapY*GetTileHeight() );
	}

	// Draw a tile
	// Using the base draw position
	virtual void DrawTile( 
		BaseEngine* pEngine, 
		SDL_Surface* pSurface, 
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY )
	{
		DrawTileAt( pEngine, pSurface, iMapX, iMapY, m_iBaseScreenX, m_iBaseScreenY );
	}

	// Draw all tiles, from start to end position
	// Using the base draw position
	void DrawAllTiles( 
		BaseEngine* pEngine, 
		SDL_Surface* pSurface, 
		int iMapXStart, int iMapYStart,
		int iMapXEnd, int iMapYEnd )
	{
		return DrawAllTilesAt( pEngine, pSurface, iMapXStart, iMapYStart, iMapXEnd, iMapYEnd, m_iBaseScreenX, m_iBaseScreenY );
	}

// THE NEXT FEW FUNCTIONS ARE THE ONES YOU MAY WISH TO OVERRIDE YOURSELF
// You probably don't need to change the stuff above.

	// Get the size of a tile - width
	virtual int GetTileWidth();

	// Get the size of a tile - height
	virtual int GetTileHeight();

	// Draw a tile at a location on the screen determined by the tile
	// position and the base X and Y co-ordinates
	virtual void DrawTile( 
		BaseEngine* pEngine, SDL_Surface* pSurface, 
		int iTileX, int iTileY )
	{
		DrawTile( pEngine, pSurface, iTileX, iTileY,
				m_iBaseScreenX + iTileX*GetTileWidth(), 
				m_iBaseScreenY + iTileY*GetTileHeight() );
	}


//
// These functions DO NOT use the base tile position:
//
public:

	// Draw a tile at a location on the screen determined by the tile
	// position and the base X and Y co-ordinates
	// OVERRIDE THIS TO DRAW YOUR TILE!!!
	virtual void DrawTileAt( 
		BaseEngine* pEngine, 
		SDL_Surface* pSurface, 
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY );

	// Draw all tiles, from start to end position
	void DrawAllTilesAt( 
		BaseEngine* pEngine, 
		SDL_Surface* pSurface, 
		int iMapXStart, int iMapYStart,
		int iMapXEnd, int iMapYEnd,
		int iStartPositionScreenX, int iStartPositionScreenY );

	// Call this when you change a tile. It will update the background AND foreground.
	void UpdateTileAt( BaseEngine* pEngine, 
			int iMapX, int iMapY,	int iNewTileValue,
			int iScreenLeftTilePosition, int iScreenTopTilePosition );

protected:
	// Map Data
	int* m_pData;
	// Map size - width
	int m_iMapWidth;
	// Map size - height
	int m_iMapHeight;
	// Base map position on the screen - to simplify things
	int m_iBaseScreenX;
	int m_iBaseScreenY;
};

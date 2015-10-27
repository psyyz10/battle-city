#pragma once
#include "tilemanager.h"
#include "JPGImage.h"

class MyTileManager :
	public TileManager
{
public:
	MyTileManager(void);
	~MyTileManager(void);

	void DrawTileAt(BaseEngine* pEngine, 
	SDL_Surface* pSurface, 
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY );

	virtual int GetTileWidth();

	virtual int GetTileHeight();

private:
	ImageData imGrass, imWater, imBrick, imIce, imSteel;
};


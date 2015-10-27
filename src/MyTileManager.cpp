#include "MyTileManager.h"


MyTileManager::MyTileManager(void)
{
	ImageData im1, im2, im3, im4;

	im1.LoadImage("grass.png");
	im2.LoadImage("water.png");
	im3.LoadImage("brick.png");
	im4.LoadImage("steel.png");

	imGrass.ResizeTo(&im1, 20, 20, false);
	imWater.ResizeTo(&im2, 20, 20, false);
	imBrick.ResizeTo(&im3, 20, 20, false);
	imSteel.ResizeTo(&im4, 20, 20, false);

}

MyTileManager::~MyTileManager(void)
{
}

void MyTileManager::DrawTileAt( 
	BaseEngine* pEngine, 
	SDL_Surface* pSurface, 
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY )
{	/*
	  There four kinds of tiles: tile with black colour, tile with orange colour which
	  works as a brick , tile with white colour which works as steel walls, tile with blue colour which is work as water.
	*/
	switch(		GetValue(iMapX,iMapY) )
	{
	case 0: // black tile
		pEngine->DrawRectangle( 
			iStartPositionScreenX,
			iStartPositionScreenY, 
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour( 0 ),
			pSurface );
		break;
	//case 1:
	case 1:
		imBrick.RenderImage( pSurface, 
						0,0, 
						iStartPositionScreenX, iStartPositionScreenY,
						imBrick.GetWidth(), imBrick.GetHeight() );
		break;
	case 2: 
		imSteel.RenderImage( pSurface, 
						0,0, 
						iStartPositionScreenX, iStartPositionScreenY,
						imSteel.GetWidth(), imSteel.GetHeight() );
		
		break;
	case 3: 
		imWater.RenderImage( pSurface, 
						0,0, 
						iStartPositionScreenX, iStartPositionScreenY,
						imWater.GetWidth(), imWater.GetHeight() );
		break;
	}	
}

// Get the size of a tile - width
int MyTileManager::GetTileWidth()
{
	return 20;
}

// Get the size of a tile - height
int MyTileManager::GetTileHeight()
{
	return 20;
}
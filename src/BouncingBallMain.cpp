#include "header.h"

#include "BaseEngine.h"

#include "BouncingBall.h"

#include "BouncingBallMain.h"

#include "JPGImage.h"

#include "TileManager.h"

/*
Draw the background of the screen.
This fills the background with black
Then puts some random colour on it
Then demos various ways of drawing shapes, images, etc
*/
void BouncingBallMain::SetupBackgroundBuffer()
{
	FillBackground( 0 );

	for ( int iX = 0 ; iX < GetScreenWidth() ; iX++ )
		for ( int iY = 0 ; iY < this->GetScreenHeight() ; iY++ )
			switch( rand()%100 )
			{
			case 0: SetBackgroundPixel( iX, iY, 0xFF0000 ); break;
			case 1: SetBackgroundPixel( iX, iY, 0x00FF00 ); break;
			case 2: SetBackgroundPixel( iX, iY, 0x0000FF ); break;
			case 3: SetBackgroundPixel( iX, iY, 0xFFFF00 ); break;
			case 4: SetBackgroundPixel( iX, iY, 0x00FFFF ); break;
			case 5: SetBackgroundPixel( iX, iY, 0xFF00FF ); break;
		}

	DrawBackgroundVerticalSidedRegion( 650, 750, // X
		100, 50, // Top line
		150, 180, // Bottom line
		0xff0000 );

	int iLineThickness = 2;

	// Draw a triangle where all three points are specified.
	DrawBackgroundTriangle( 300,300, 325,275, 350,350, 0x00ffff );
	DrawBackgroundTriangle( 425,375, 450,450, 400,375, 0x00ffff );
	DrawBackgroundTriangle( 550,550, 525,475, 450,500, 0x00ffff );

	// Draw various polygons
//	DrawBackgroundPolygon( 100, 100, 150, 100, 250, 200, 150, 200, 0xff0000 );
//	DrawBackgroundPolygon( 100, 300, 200, 275, 300, 325, 250, 400, 150, 375, 0x00ff00 );
//	DrawBackgroundPolygon( 400, 100, 500, 150, 600, 100, 550, 200, 450, 200, 400, 250, 0x0000ff );

	// Draw a polygon and some lines joining the points.
	DrawBackgroundPolygon( 100, 100, 150, 100, 
			250, 200, 150, 200, 
			100, 300, 200, 275, 
			300, 325, 50, 400, 0xff00ff );
	DrawBackgroundLine( 100, 100, 150, 100, 0xffffff );
	DrawBackgroundLine( 150, 100, 250, 200, 0xffffff );
	DrawBackgroundLine( 250, 200, 150, 200, 0xffffff );
	DrawBackgroundLine( 150, 200, 100, 300, 0xffffff );
	DrawBackgroundLine( 100, 300, 200, 275, 0xffffff );
	DrawBackgroundLine( 200, 275, 300, 325, 0xffffff );
	DrawBackgroundLine( 300, 325,  50, 400, 0xffffff );
	DrawBackgroundLine(  50, 400, 100, 100, 0xffffff );

	DrawBackgroundPolygon( 350, 100, 500, 150, 
			600, 100, 550, 200, 
			450, 200, 400, 250, 
			410, 180, 0x00ff00 );
	DrawBackgroundLine( 350, 100, 500, 150, 0xffffff );
	DrawBackgroundLine( 500, 150, 600, 100, 0xffffff );
	DrawBackgroundLine( 600, 100, 550, 200, 0xffffff );
	DrawBackgroundLine( 550, 200, 450, 200, 0xffffff );
	DrawBackgroundLine( 450, 200, 400, 250, 0xffffff );
	DrawBackgroundLine( 400, 250, 410, 180, 0xffffff );
	DrawBackgroundLine( 410, 180, 350, 100, 0xffffff );

	// Draw an image loaded from a file.
	ImageData im, im2;
	im2.LoadImage( "demo.png" );
	im.ShrinkFrom( &im2, 2 );

	// Note: image loaded only once, above, and now we will draw it nine times
	for ( int i = 0 ; i < 3 ; i++ )
		for ( int j = 0 ; j < 3 ; j++ )
			im.RenderImageWithMask( this->GetBackground(), 
					0, 0, 
					i*100, j*100 + 300, 
					im.GetWidth(), im.GetHeight() );


	// Draw some tiles using the tile manager

	// Specify how many tiles wide and high
	m.SetSize( 10, 10 ); 
	// Specify the screen x,y of top left corner
	m.SetBaseTilesPositionOnScreen( 450, 300 );
	// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
	// to the background of this screen
	m.DrawAllTiles( this, this->GetBackground(), 0, 0, 9, 9 );
}


/*
In here you need to create any movable objects that you wish to use.
Sub-classes need to implement this function.
*/
int BouncingBallMain::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// Create a new object of type BouncingBall1
	m_pBall1 = new BouncingBall1( this, 
		0/*Id*/, 1/*Type*/, 
		100/*Size*/, 
		1/*Colour*/,
		"A"/*Label*/, 
		-10/*XLabelOffset*/,
		-15/*YLabelOffset*/, 
		&m );

	// Bouncing ball 1 has a movement object, tells it to move from
	// position a to position b, over a specific period of time.
	// The update for the ball will reverse the move at the end of this time
	m_pBall1->SetMovement( GetTime(), GetTime()+1000, GetTime(), 100, 100, 700, 500 );

	// Create another, different, type of ball
	m_pBall2 = new BouncingBall2( this, 
		0/*Id*/, 1/*Type*/, 
		100/*Size*/, 
		2/*Colour*/,
		"B"/*Label*/, 
		-10/*XLabelOffset*/,
		-15/*YLabelOffset*/ );
	m_pBall2->SetPosition( 100,100 );
	m_pBall2->SetSpeed( 1.1,1.0 );

	// And a third ball
	m_pBall3 = new BouncingBall2( this, 
		0/*Id*/, 1/*Type*/, 
		100/*Size*/, 
		3/*Colour*/,
		"C"/*Label*/, 
		-10/*XLabelOffset*/,
		-15/*YLabelOffset*/ );
	m_pBall3->SetPosition( 300,250 );
	m_pBall3->SetSpeed( 0.8,1.2 );

	// Create an array one element larger than the number of objects that you want.
	m_ppDisplayableObjects = new DisplayableObject*[4]; // i.e. 3 balls + 1 for NULL

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	m_ppDisplayableObjects[0] = m_pBall1;
	m_ppDisplayableObjects[1] = m_pBall2;
	m_ppDisplayableObjects[2] = m_pBall3;

	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	m_ppDisplayableObjects[3] = NULL;

	// NOTE: We also need to destroy the objects, but the method at the 
	// top of this function will destroy all objects pointed at by the 
	// array elements so we can ignore that here.
	return 0;

}







/* Draw text labels */
void BouncingBallMain::DrawStrings()
{
	CopyBackgroundPixels( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
	DrawScreenString( 150, 10, "Example text", 0xffffff, NULL );
	SetNextUpdateRect( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
}


/* Overridden GameAction to ensure that objects use the modified time */
void BouncingBallMain::GameAction()
{
	// If too early to act then do nothing
	if ( !TimeToAct() )
		return;

	// Don't act for another 10 ticks
	SetTimeToAct( 1 );

	UpdateAllObjects( GetTime() );
}


// Override to add a node at specified point
void BouncingBallMain::MouseDown( int iButton, int iX, int iY )
{
	m_pBall2->SetPosition( iX, iY );
}

/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is pressed
*/
void BouncingBallMain::KeyDown(int iKeyCode)
{
	switch ( iKeyCode )
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode( 0 );
		break;
	case SDLK_SPACE: // SPACE Pauses
		break;
	}
}


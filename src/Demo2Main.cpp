#include "header.h"

#include "BaseEngine.h"

#include "Demo2Object.h"

#include "Demo2Main.h"

#include "JPGImage.h"

#include "TileManager.h"


Demo2Main::Demo2Main(void)
: BaseEngine( 50 )
{
}

Demo2Main::~Demo2Main(void)
{
}

void Demo2Main::SetupBackgroundBuffer()
{
	FillBackground( 0 );

/*
	// Specify how many tiles wide and high
	m_oTiles.SetSize( 15, 11 ); 
	// Set up the tiles
	for ( int x = 0 ; x < 15 ; x++ )
		for ( int y = 0 ; y < 11 ; y++ )
			m_oTiles.SetValue( x, y, rand()%31 );
	// Specify the screen x,y of top left corner
	m_oTiles.SetBaseTilesPositionOnScreen( 25, 40 );
	// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
	// to the background of this screen
	m_oTiles.DrawAllTiles( this, this->GetBackground(), 0, 0, 14, 10 );
*/
}

int Demo2Main::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// Create an array one element larger than the number of objects that you want.
	m_ppDisplayableObjects = new DisplayableObject*[21]; // i.e. 1 object

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	for ( int i = 0 ; i < 20 ; i++ )
		m_ppDisplayableObjects[i] = new Demo2Object(this);

	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	m_ppDisplayableObjects[20] = NULL;

	// NOTE: We also need to destroy the objects, but the method at the 
	// top of this function will destroy all objects pointed at by the 
	// array elements so we can ignore that here.

	return 0;
}







/* Draw text labels */
void Demo2Main::DrawStrings()
{
	CopyBackgroundPixels( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
	DrawScreenString( 150, 10, "Example text", 0xffffff, NULL );
	SetNextUpdateRect( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
}


/* Overridden GameAction to ensure that objects use the modified time */
void Demo2Main::GameAction()
{
	// If too early to act then do nothing
	if ( !TimeToAct() )
		return;

	// Don't act for another 10 ticks
	SetTimeToAct( 1 );

	UpdateAllObjects( GetTime() );
}


// Override to add a node at specified point
void Demo2Main::MouseDown( int iButton, int iX, int iY )
{
}

/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is pressed
*/
void Demo2Main::KeyDown(int iKeyCode)
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

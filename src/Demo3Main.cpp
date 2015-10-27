#include "header.h"

#include "BaseEngine.h"

#include "Demo3Object.h"
#include "Demo3ObjectFinished.h"

#include "Demo3Main.h"

#include "JPGImage.h"

#include "TileManager.h"


Demo3Main::Demo3Main(void)
: BaseEngine( 50 )
{
}

Demo3Main::~Demo3Main(void)
{
}

void Demo3Main::SetupBackgroundBuffer()
{
	FillBackground( 0 );

	char* data[] = {
		"bbbbbbbbbbbbbbb",
		"baeaeadadaeaeab",
		"babcbcbcbcbibeb",
		"badadgdadhdadhb",
		"bgbcbcbcbibcbeb",
		"badadadadadadab",
		"bfbcbibcbcbcbeb",
		"bahadadhdadadab",
		"bfbcbcbibcbibeb",
		"badadadadadadab",
		"bbbbbbbbbbbbbbb" };

	// Specify how many tiles wide and high
	m_oTiles.SetSize( 15, 11 ); 
	// Set up the tiles
	for ( int x = 0 ; x < 15 ; x++ )
		for ( int y = 0 ; y < 11 ; y++ )
			m_oTiles.SetValue( x, y, data[y][x]-'a' );

//			m_oTiles.SetValue( x, y, rand()%10 );

	for ( int y = 0 ; y < 11 ; y++ )
	{
		for ( int x = 0 ; x < 15 ; x++ )
			printf("%d ", m_oTiles.GetValue(x,y) );
		printf("\n" );
	}

	// Specify the screen x,y of top left corner
	m_oTiles.SetBaseTilesPositionOnScreen( 25, 40 );
//	m_oTiles.SetBaseTilesPositionOnScreen( 10, 10 );

	// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
	// to the background of this screen
	m_oTiles.DrawAllTiles( this, 
		this->GetBackground(), 
		0, 0, 14, 10 );
}

int Demo3Main::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// Create an array one element larger than the number of objects that you want.
	m_ppDisplayableObjects = new DisplayableObject*[6]; // i.e. 1 object

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	m_ppDisplayableObjects[0] = new Demo3ObjectFinished(this,1,1);
	m_ppDisplayableObjects[1] = new Demo3Object(this,9,9);
	m_ppDisplayableObjects[2] = new Demo3Object(this,13,9);
	m_ppDisplayableObjects[3] = new Demo3Object(this,9,5);
	m_ppDisplayableObjects[4] = new Demo3Object(this,13,5);

	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	m_ppDisplayableObjects[5] = NULL;

	// NOTE: We also need to destroy the objects, but the method at the 
	// top of this function will destroy all objects pointed at by the 
	// array elements so we can ignore that here.

	return 0;
}



void Demo3Main::DrawChanges()
{
	// Remove objects from their old positions
	UndrawChangingObjects();
	// Draw the text for the user
	DrawStrings();
	// Draw objects at their new positions
	DrawChangingObjects();
}



/* Draw text labels */
void Demo3Main::DrawStrings()
{
	CopyBackgroundPixels( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
	DrawScreenString( 150, 10, "Tile placement example", 0xffffff, NULL );
	SetNextUpdateRect( 0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/ );
}


/* Overridden GameAction to ensure that objects use the modified time */
void Demo3Main::GameAction()
{
	// If too early to act then do nothing
	if ( !TimeToAct() )
		return;

	// Don't act for another 10 ticks
	SetTimeToAct( 1 );

	UpdateAllObjects( GetTime() );
}


// Override to add a node at specified point
void Demo3Main::MouseDown( int iButton, int iX, int iY )
{
}

/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is pressed
*/
void Demo3Main::KeyDown(int iKeyCode)
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

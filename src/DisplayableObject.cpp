#include "header.h"


#include "BaseEngine.h"

#include "DisplayableObject.h"


// Constructor
DisplayableObject::DisplayableObject(BaseEngine* pEngine) :
	// Current position of object on the screen
	m_iCurrentScreenX(-1),
	m_iCurrentScreenY(-1),
	// Previous position of object on the screen
	m_iPreviousScreenX(-1),
	m_iPreviousScreenY(-1),
	// Offset within the drawing area to draw at:
	m_iStartDrawPosX(0),
	m_iStartDrawPosY(0),
	// Size of the thing inside the tile:
	m_iDrawWidth(10),
	m_iDrawHeight(10),
	// Store pointer to the game object, for later use
	m_pEngine(pEngine)
{
}


// Destructor
DisplayableObject::~DisplayableObject()
{
}

// Draw the object - override to implement the actual drawing of the correct object
// This just draws a magenta square at the current location
void DisplayableObject::Draw()
{
	// Draw the object
	for ( int iX = m_iCurrentScreenX + m_iStartDrawPosX ; iX < (m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth) ; iX++ )
		for ( int iY = m_iCurrentScreenY + m_iStartDrawPosY ; iY < (m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight) ; iY++ )
			m_pEngine->SafeSetScreenPixel( iX, iY, 0xff00ff );

	// Store the position at which the object was last drawn.
	StoreLastScreenPositionAndUpdateRect();
}

void DisplayableObject::StoreLastScreenPositionAndUpdateRect() 
{
	// Our initial rectangle that needs updating is the current screen position
	int x1 = m_iCurrentScreenX + m_iStartDrawPosX;
	int x2 = m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth;
	int y1 = m_iCurrentScreenY + m_iStartDrawPosY;
	int y2 = m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight;

	// The screen area changed is the previous position + the new position
	// so grow the rectangle according to the previous position of the object
	if ( m_iPreviousScreenX < m_iCurrentScreenX )
		x1 = m_iPreviousScreenX + m_iStartDrawPosX;
	if ( m_iPreviousScreenX > m_iCurrentScreenX )
		x2 = m_iPreviousScreenX + m_iStartDrawPosX + m_iDrawWidth;
	if ( m_iPreviousScreenY < m_iCurrentScreenY )
		y1 = m_iPreviousScreenY + m_iStartDrawPosY;
	if ( m_iPreviousScreenY > m_iCurrentScreenY )
		y2 = m_iPreviousScreenY + m_iStartDrawPosY + m_iDrawHeight;

	// Now set up the rectangle
	m_iXUpdateRect = x1;
	m_iWUpdateRect = x2 - x1;
	m_iYUpdateRect = y1;
	m_iHUpdateRect = y2 - y1;

	// Store the location that was last drawn at, so that it can be removed again
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;
}

void DisplayableObject::RedrawBackground()
{
	// Copy the background pixels back over.
	m_pEngine->CopyBackgroundPixels( m_iPreviousScreenX + m_iStartDrawPosX, 
		m_iPreviousScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight );
}


void DisplayableObject::GetRedrawRect( SDL_Rect *pRect ) 
{
	// Now set up the rectangle
	pRect->x = m_iXUpdateRect;
	pRect->y = m_iYUpdateRect;
	pRect->w = m_iWUpdateRect;
	pRect->h = m_iHUpdateRect;

//	printf( "Redraw %d %d %d %d\n", (int)(pRect->x), (int)(pRect->y), (int)(pRect->w), (int)(pRect->h) );
//	printf( "Redraw %d %d %d %d\n", m_iXUpdateRect, m_iYUpdateRect, m_iWUpdateRect, m_iHUpdateRect );
}



// Handle the update action, moving the object and/or handling any game logic
void DisplayableObject::DoUpdate( int iCurrentTime )
{
	// Override can handle player input or do some AI actions to redirect object and set the current screen position
	// Set m_iCurrentScreenX, m_iCurrentScreenY
}


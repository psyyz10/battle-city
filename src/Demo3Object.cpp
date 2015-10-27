#include "header.h"

#include "Demo3Object.h"
#include "Demo3Main.h"

Demo3Object::Demo3Object(Demo3Main* pEngine, int iMapX, int iMapY)
: DisplayableObject(pEngine)
, m_pMainEngine( pEngine )
, m_iMapX(iMapX)
, m_iMapY(iMapY)
, m_iDir(0)
{
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;

	// Record the ball size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;
	
	// Out item at specific coordinates
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX*50+25+25;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY*50+25+40;

	// And make it visible
	SetVisible(true);
}

Demo3Object::~Demo3Object(void)
{
}

void Demo3Object::Draw()
{
	// Do not draw if it should not be visible
	if ( !IsVisible() )
		return;

	int iSize = 25;
//	int iTick = m_pMainEngine->GetTime()/20; // 1 per 20ms
//	int iFrame = iTick % 30;
//	int iSize = 10 + iFrame;
//	if ( iFrame > 15 )
//		iSize = 10 + (30-iFrame);

	m_pMainEngine->DrawScreenOval(
			m_iCurrentScreenX - iSize,
			m_iCurrentScreenY - iSize,
			m_iCurrentScreenX + iSize-1,
			m_iCurrentScreenY + iSize-1,
			0x00ffff );

	// Store the position at which the object was last drawn
	// You MUST do this to ensure that the screen is updated when only drawing movable objects
	// This tells the system where to 'undraw' the object from
	StoreLastScreenPositionAndUpdateRect();
}

void Demo3Object::DoUpdate( int iCurrentTime )
{
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;


	// If movement has finished
	if ( m_oMover.HasMovementFinished(iCurrentTime) )
	{
		Demo3TileManager& tm = m_pMainEngine->GetTileManager();
 
		// INSERT POSITION A

		// Set off a new movement
		switch( rand() % 10 )
		{
		case 0: // Increase dir by 1
			m_iDir = ( m_iDir + 1 )%4;
			break;
		case 1: // Reduce dir by 1
			m_iDir = ( m_iDir + 3 )%4;
			break;
		}

		// INSERT POSITION C

		// REPLACE THE FOLLOWING CODE FOR CHANGE B
		if ( m_iMapX + GetXDiffForDirection(m_iDir) > 14 )
			m_iDir = 3;
		if ( m_iMapX + GetXDiffForDirection(m_iDir) < 0 )
			m_iDir = 1;
		if ( m_iMapY + GetYDiffForDirection(m_iDir) > 10 )
			m_iDir = 0;
		if ( m_iMapY + GetYDiffForDirection(m_iDir) < 0 )
			m_iDir = 2;

		// Allow move - set up new movement now
		m_iMapX += GetXDiffForDirection(m_iDir);
		m_iMapY += GetYDiffForDirection(m_iDir);

		m_oMover.Setup( 
			m_iCurrentScreenX,
			m_iCurrentScreenY,
			m_iMapX *50 + 25 + 25,
			m_iMapY *50 + 25 + 40,
			iCurrentTime,
			iCurrentTime+400+rand()%200 );
		// END OF REPLACE THE FOLLOWING CODE FOR CHANGE B
	}

	// If making a move then do the move
	if ( !m_oMover.HasMovementFinished(iCurrentTime) )
	{
		// Ask the mover where the object should be
		m_oMover.Calculate( iCurrentTime );
		m_iCurrentScreenX = m_oMover.GetX();
		m_iCurrentScreenY = m_oMover.GetY();
	}

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}


/*
Insert this code at the place labelled "INSERT POSITION A"
When you do so, you should see the pellets shrink when something passes over them.
It checks the tile value and increases it by one each time.

		// Handle any tile that we just moved onto
		switch ( tm.GetValue( m_iMapX, m_iMapY ) )
		{
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			tm.UpdateTile( m_pMainEngine, m_iMapX, m_iMapY, 
				tm.GetValue( m_iMapX, m_iMapY ) + 1 );
			break;
		case 8:
			tm.UpdateTile( m_pMainEngine, m_iMapX, m_iMapY, 0 );
			break;
		}
*/

/*
Optionally insert this code at position labelled "INSERT POSITION C"
This will make the arrow keys change the direction
Note: the code to randomly change direction may then change it again

	if ( m_pMainEngine->IsKeyPressed( SDLK_UP ) )
		m_iDir = 0;
	if ( m_pMainEngine->IsKeyPressed( SDLK_RIGHT ) )
		m_iDir = 1;
	if ( m_pMainEngine->IsKeyPressed( SDLK_DOWN ) )
		m_iDir = 2;
	if ( m_pMainEngine->IsKeyPressed( SDLK_LEFT ) )
		m_iDir = 3;
*/

/*
The following code should replace the code labelled
"REPLACE THE FOLLOWING CODE FOR CHANGE B"
to the line labelled 
"END OF REPLACE THE FOLLOWING CODE FOR CHANGE B"
It will change the behaviour so that the objects move around the walls instead
of through them. i.e. it will check the tile position and only allow a move
if there is no blocking wall.

		switch ( tm.GetValue( 
				m_iMapX + GetXDiffForDirection(m_iDir),
				m_iMapY + GetYDiffForDirection(m_iDir) ) )
		{
		case 0: // Passageway
		case 2: // Pellet
		case 3: // Pellet
		case 4: // Pellet
		case 5: // Pellet
		case 6: // Pellet
		case 7: // Pellet
		case 8: // Pellet
			// Allow move - set up new movement now
			m_iMapX += GetXDiffForDirection(m_iDir);
			m_iMapY += GetYDiffForDirection(m_iDir);

			m_oMover.Setup( 
				m_iCurrentScreenX,
				m_iCurrentScreenY,
				m_iMapX *50 + 25 + 25,
				m_iMapY *50 + 25 + 40,
				iCurrentTime,
				iCurrentTime+400+rand()%200 );
			break;	
		case 1: // Wall
			m_iDir = rand()%4; // Rotate randomly
			break;
		}
*/

/*
Finally, perform a simple animation by changing the ball sizes:

Change the code:
	int iSize = 25;
To:
	int iTick = m_pMainEngine->GetTime()/20; // 1 per 20ms
	int iFrame = iTick % 30;
	int iSize = 10 + iFrame;
	if ( iFrame > 15 )
		iSize = 10 + (30-iFrame);

You should now see the size change constantly.
*/

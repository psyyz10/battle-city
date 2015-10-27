#include "Bullet.h"
#include "JPGImage.h"
#include "EnemyTank.h"

/* This class for producting bullet object */
Bullet::Bullet(MyProjectMain* pEngine, Tank* t, MyTileManager* m, bool fromPlayer)
	: DisplayableObject( pEngine )
, tank (t) 
, m_pTileManager(m)
, fromPlayer(fromPlayer)
{
	im.LoadImage("bullet.png");
	im_Bullet.ResizeTo(&im, 5, 8, false);

	m_iStartDrawPosX = -5;
	m_iStartDrawPosY = -5;

	if (!fromPlayer && tank->IsVisible())
		SetVisible(true);
	else
		SetVisible(false);
}


Bullet::~Bullet(void)
{
}

void Bullet :: Draw()
{

	if (!IsVisible())
		return;

	// draw bullet
	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX - m_iDrawWidth/2 + 1,
		m_iCurrentScreenY - m_iDrawHeight/2 + 1,
		m_iCurrentScreenX + m_iDrawWidth/2 - 1,
		m_iCurrentScreenY + m_iDrawHeight/2 - 1,
		0xcdcdcd);

	StoreLastScreenPositionAndUpdateRect();
}	

void Bullet :: checkTouchWithOtherBullets()
{
	// Check all bullets belong to enemies
	DisplayableObject* pObject;
	for ( int i = 6 ; 
	 (pObject = m_pEngine->GetDisplayableObject( i)) != NULL ; i++ )
	{
		Bullet* bullet = dynamic_cast<Bullet*> (pObject);
		// skip non-bullet object and invisible bullets
		if (bullet == NULL || !bullet->IsVisible()) 
			continue;
		
		int iXDiff = bullet->GetXCentre() - m_iCurrentScreenX;
		int iYDiff = bullet->GetYCentre() - m_iCurrentScreenY;

		int iSize = m_iDrawWidth/2;
		int iSizeOther = bullet->getWidth()/2;


	    // Pythagorus' theorum:
		if ( ((iXDiff*iXDiff)+(iYDiff*iYDiff)) 
			<= ((iSizeOther+iSize)*(iSizeOther+iSize)) )
		{
			// set two collided bullets invisible
			this->SetVisible(false);
			bullet->SetVisible(false);
		}
	}
}

void Bullet :: DoUpdate( int iCurrentTime )
{
	MyProjectMain* myEngine = dynamic_cast <MyProjectMain*> (m_pEngine);

	if(tank->gameProp == 5 && dynamic_cast<EnemyTank*>(tank) != 0)
	{	SetVisible(0);
		return;
	}

	// if in paused state, return
	if (myEngine -> isPausedState() )
	{
		RedrawObjects();
		return;
	}
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;
	int distance;
	int interval = 1400;

	if (!fromPlayer)
	{
		if(tank -> getID() == 4)
			interval = 1000;
	}



	if (fromPlayer)
		checkTouchWithOtherBullets();

	if ( m_oMover.HasMovementFinished(iCurrentTime) )
	{
		if (!fromPlayer && tank->IsVisible())
		{
			SetVisible(true);
			// Bullets start from tank's current position and and move the
			// direction tank faces.
			switch (tank->getDirection())
			{
			case 0: //Up
				distance = tank->GetYCentre()- tank->getHeight()/2 - 50;
				SetMovement(  iCurrentTime, iCurrentTime+interval * distance / 520, iCurrentTime,
							tank->GetXCentre(), tank->GetYCentre()- tank->getHeight()/2 , tank->GetXCentre() , 50);
				break;
			case 1: //Left
				distance = tank->GetXCentre()- tank->getWidth()/2 - 50;
				SetMovement(  iCurrentTime, iCurrentTime+interval * distance / 520, iCurrentTime,
							tank->GetXCentre()- tank->getWidth()/2, tank->GetYCentre() , 50 , tank->GetYCentre());
					break;
			case 2: //Right
				distance = 570 - tank->GetXCentre()+tank->getWidth()/2;
				SetMovement(  iCurrentTime, iCurrentTime+interval * distance / 520, iCurrentTime,
						tank->GetXCentre()+tank->getWidth()/2, tank->GetYCentre() , 570 , tank->GetYCentre());
				break;
			case 3: //Down
				distance = 570 - tank->GetYCentre()+ tank->getHeight()/2;
				SetMovement(  iCurrentTime, iCurrentTime+interval * distance / 520, iCurrentTime,
				tank->GetXCentre(), tank->GetYCentre()+ tank->getHeight()/2 , tank->GetXCentre() , 570);
				break;
				}//End switch
			}
		else
			SetVisible(false);

	}// End if
	if ( !m_oMover.HasMovementFinished(iCurrentTime) )
	{
		// Ask the mover where the object should be
		m_oMover.Calculate( iCurrentTime );
		m_iCurrentScreenX = m_oMover.GetX();
		m_iCurrentScreenY = m_oMover.GetY();
	}

	// Handle non-black tile hit by bullet
	if ( m_pTileManager->IsValidTilePosition( m_iCurrentScreenX, m_iCurrentScreenY ) 
			&& IsVisible())
	{
		int iTileX = m_pTileManager->GetTileXForPositionOnScreen(m_iCurrentScreenX);
		int iTileY = m_pTileManager->GetTileYForPositionOnScreen(m_iCurrentScreenY);
		int iCurrentTile = m_pTileManager->GetValue( iTileX, iTileY );
		
		// If bullets hits the brick, bullet and brick disappears
		if (iCurrentTile == 1)
		{
			m_pTileManager->UpdateTile( GetEngine(), iTileX, iTileY, 0 );
			SetVisible(false);
		}
		// If bullets hit the steel, bullet disappears
		else if (iCurrentTile == 2)
			SetVisible(false);
		
	}
	RedrawObjects();
}

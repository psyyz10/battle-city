#include "PlayerTank.h"
#include "EnemyTank.h"
#include "MyProjectMain.h"

/* To produce player tank object */
PlayerTank::PlayerTank(MyProjectMain* pEngine,
					 MyTileManager* m , int id)
	: Tank(pEngine, m)
	, startCounter(0)
	, imageSate (0)
{
	this -> id = id;

	// initial state
	if (id == 0 && startCounter == 0)
		changTankState(1);
	else if (id == 2 && startCounter == 0)
		changTankState(3);

	loadTankImage();
	gamePropTime = 0;
	m_iDrawWidth = im_TankU.GetWidth();
	m_iDrawHeight = im_TankU.GetHeight();
	
	m_iStartDrawPosX = -m_iDrawWidth/2;
	m_iStartDrawPosY = -m_iDrawHeight/2;

	direction = 0;

	// set position
	if (id == 0)
	{
		X = m_iPreviousScreenX = m_iCurrentScreenX = 230;
		Y = m_iPreviousScreenY = m_iCurrentScreenY = 550;
	}
	else
	{
		X = m_iPreviousScreenX = m_iCurrentScreenX = 390;
		Y = m_iPreviousScreenY = m_iCurrentScreenY = 550;
	}

	// Speed
	speed_X = speed;
	speed_Y = speed;
}


PlayerTank::~PlayerTank(void)
{
}

/* load image */
void PlayerTank :: loadTankImage()
{
	switch(id)
	{
	case 0:
		tempL.LoadImage("tank1L.png" );
		tempR.LoadImage("tank1R.png");
		tempU.LoadImage("tank1U.png");
		tempD.LoadImage("tank1D.png");
		break;
	case 1: // protected state is two kinds of image take turns to replace
		if (imageSate)
		{
			tempL.LoadImage("tank1L_protected.png");
			tempR.LoadImage("tank1R_protected.png");
			tempU.LoadImage("tank1U_protected.png");
			tempD.LoadImage("tank1D_protected.png");
		}
		else
		{
			tempL.LoadImage("tank1L_protected2.png");
			tempR.LoadImage("tank1R_protected2.png");
			tempU.LoadImage("tank1U_protected2.png");
			tempD.LoadImage("tank1D_protected2.png");
		}
	
		imageSate = !imageSate;
		break;
	case 2:
		tempL.LoadImage("tank2L.png" );
		tempR.LoadImage("tank2R.png");
		tempU.LoadImage("tank2U.png");
		tempD.LoadImage("tank2D.png");
		break;
	case 3:// protected state is two kinds of image take turns to replace
		if (imageSate)
		{
			tempL.LoadImage("tank2L_protected.png");
			tempR.LoadImage("tank2R_protected.png");
			tempU.LoadImage("tank2U_protected.png");
			tempD.LoadImage("tank2D_protected.png");
		}
		else
		{
			tempL.LoadImage("tank2L_protected2.png");
			tempR.LoadImage("tank2R_protected2.png");
			tempU.LoadImage("tank2U_protected2.png");
			tempD.LoadImage("tank2D_protected2.png");
		}
	
		imageSate = !imageSate;
		break;
	}

	im_TankD.ResizeTo(&tempD, 33, 33, false);
	im_TankR.ResizeTo(&tempR, 33, 33, false);
	im_TankU.ResizeTo(&tempU, 33, 33, false);
	im_TankL.ResizeTo(&tempL, 33, 33, false);
}


// Change speed when the direction key pressed every time
void PlayerTank :: changeSpeedWhenKeyPressed()
{
	MyProjectMain* engine = dynamic_cast <MyProjectMain*> (m_pEngine);

	if (engine != NULL && engine->isPlayState() && (id == 0 || id == 1))
	{
		if ( GetEngine()->IsKeyPressed( SDLK_w ) )// Move up
		{
			if (direction == 0)
				speed_Y = -speed;
			else 
				speed_Y = 0;

			direction = 0; 


		}
		else if ( GetEngine()->IsKeyPressed( SDLK_s ) )// Move down 
		{
			if (direction == 3)
				speed_Y = speed;
			else 
				speed_Y = 0;

			direction = 3;
		}
		else 
			speed_Y = 0;

		if ( GetEngine()->IsKeyPressed( SDLK_a ) )// Move left
		{
			if (direction == 1)
				speed_X = -speed;
			else 
				speed_X = 0;

			direction = 1;
		}
		else if ( GetEngine()->IsKeyPressed( SDLK_d ) )// Move right
		{
			if (direction == 2)
				speed_X = speed;
			else 
				speed_X = 0;

			direction = 2;
		}
		else
			speed_X = 0;
	}
	else if (engine != NULL && engine->isPlayState() && (id == 2 || id == 3))
	{
		if ( GetEngine()->IsKeyPressed( SDLK_UP ) )// Move up
		{
			if (direction == 0)
				speed_Y = -speed;
			else 
				speed_Y = 0;

			direction = 0; 
		}
		else if ( GetEngine()->IsKeyPressed( SDLK_DOWN ) )// Move down 
		{
			if (direction == 3)
				speed_Y = speed;
			else 
				speed_Y = 0;

			direction = 3;
		}
		else 
			speed_Y = 0;

		if ( GetEngine()->IsKeyPressed( SDLK_LEFT ) )// Move left
		{
			if (direction == 1)
				speed_X = -speed;
			else 
				speed_X = 0;

			direction = 1;
		}
		else if ( GetEngine()->IsKeyPressed( SDLK_RIGHT ) )// Move right
		{
			if (direction == 2)
				speed_X = speed;
			else 
				speed_X = 0;

			direction = 2;
		}
		else
			speed_X = 0;
	}
}

void PlayerTank :: DoUpdate(int iCurrentTime )
{
	// transform to the shield state to protect the tank when it startts
	if (id == 0 && startCounter == 0)
		changTankState(1);
	else if (id == 2 && startCounter == 0)
		changTankState(3);
	startCounter ++;

	// in shield state, change image continuously
	if (startCounter < 300 && startCounter % 3 == 0 || gamePropTime != 0 &&  gamePropTime % 3 == 0)
		loadTankImage();

	// after 300 time unit of appearance, change shield state to normal state
	if (startCounter == 300)
	{
		if (id == 1)
			changTankState(0);
		else if (id == 3)
			changTankState(2);
	}

	MyProjectMain* myEngine = dynamic_cast <MyProjectMain*> (m_pEngine);

	//check pause
	if (myEngine -> isPausedState())
	{
		RedrawObjects();
		return;
	}
	if (!initial)
	{
		if (!IsVisible())
		return;

	changeSpeedWhenKeyPressed();

	int tempX = X;
	int tempY = Y;

	X += speed_X;
	Y += speed_Y;

	checkTouchWithOtherObjects(tempX, tempY);

	// if the wall is in front, not change the position
	if (isWallInFront())
	{
		X = tempX;
		Y = tempY;
	}	

	checkTouchWithBoundary();	


	m_iCurrentScreenX = (int)(X);
	m_iCurrentScreenY = (int)(Y);
	}

	// calculate treasures using time
	if (gamePropTime != 0)
		gamePropTime++;

	// if the treasure's using time is more than 500 time unit, cancel out the effect
	if (gamePropTime > 500)
	{
		switch (gameProp)
		{
		case 1:
			changeBrickToSteel(0);
			break;
		case 4:
			if (id == 1)
				changTankState(0);
			else if(id == 3)
				changTankState(2);
			break;
		}

		// reset them to zero
		gamePropTime = 0;
		gameProp = 0;
	}


	RedrawObjects();
}

void PlayerTank :: checkTouchWithOtherObjects(int X, int Y)
{
	DisplayableObject* pObject;

	for ( int i = 1 ; 	
		(pObject = m_pEngine->GetDisplayableObject( i )) != NULL ; i++ )
	{
		// Three posible types
		Tank* tank = dynamic_cast<Tank*> (pObject);
		Bullet* bullet = dynamic_cast<Bullet*> (pObject);
		GameProp* gameProp = dynamic_cast<GameProp*> (pObject);

		// Skip itself and bullets belong to itself; also skip objects which are not visible.
		if ( !pObject->IsVisible() || pObject == this || (bullet != NULL && bullet->isfromPlayer())) 
			continue;
			
		int iXDiff = pObject->GetXCentre() - (int)(X + 0.5);
		int iYDiff = pObject->GetYCentre() - (int)(Y + 0.5);
		int iXDiff1 = pObject->GetXCentre() - m_iCurrentScreenX;
		int iYDiff1 = pObject->GetYCentre() - m_iCurrentScreenY; 
		bool isChecked = false;
		int iSize = m_iDrawWidth/2;
		int iSizeOther = 0;

		// Other objects' size 
		if (bullet != NULL) // bullets belongs to home tank
			iSizeOther = bullet->getWidth()/2;
		else if (tank != NULL)// another player tank
			iSizeOther = tank->getWidth()/2;
		else if (gameProp != NULL)// bonu
			iSizeOther = gameProp->getWidth()/2;


		// Pythagorus' theorum:
		if ( ((iXDiff*iXDiff)+(iYDiff*iYDiff)) 
			<= ((iSizeOther+iSize)*(iSizeOther+iSize)) )
		{
			// If tank hit a visible bullet
			if (bullet != NULL && !shot)
			{
				// If player tank is shield shape, then after hitting bullet nothing happens to it
				if (id == 1 || id == 3)
					return;
				else
				{
					// Otherwise set its state as shot.
					MyProjectMain* myEngine = dynamic_cast <MyProjectMain*> (m_pEngine);
					shot = true;
					SetVisible(false);
					startCounter = 0;
				}
				// The bullet is invisible after hitting the tank.
				if (bullet != NULL)
					bullet->SetVisible(false);

			}
			else if (tank != NULL )// If player tank collides with other visible tank, just not move.
			{
				this->X = X;
				this->Y = Y;
			}
			else if (gameProp != NULL)// If there is a treasure, set treasure invisible, and does the function.
			{
				gameProp->SetVisible(false);
				int id = gameProp->getID();
				touchWithGameProp(id);
			}
		
		}
	}
}

void PlayerTank :: touchWithGameProp(int id)
{
	gameProp = id;
	MyProjectMain* myEngine = dynamic_cast <MyProjectMain*> (m_pEngine);
	switch (id)
	{
	case 1:
		//change base wall to steel
		changeBrickToSteel(1);
		gamePropTime = 1;
		break;
	case 2: // set all enenmy on the screan invisible
		DisplayableObject* p;
		for ( int i = 7 ; 
	 		( p = m_pEngine->GetDisplayableObject( i )) != NULL ;
				i++ )
		{
			if (!p->IsVisible())
				continue;
			Tank* t = dynamic_cast <Tank*> (p);
			Bullet* b = dynamic_cast <Bullet*> (p);
			
			if (t != NULL){
				t->setShot(true);
				}
			else if (b != NULL)
				b->SetVisible(false);
		}
		break;
	case 3:
		// Add one to home tanks life.
		if (this -> id == 0 || this -> id == 1)
			myEngine->changeHomeTankLife(1,1);
		else
			myEngine->changeHomeTankLife(2,1);
		break;
	case 4: // change to shield state
		if (this -> id == 0)
			changTankState(1);
		else if(this -> id == 2)
			changTankState(3);
		gamePropTime = 1;
		break;
	case 5:// frose the enemy tank
		gamePropTime = 1;
		break;
	}
}


void PlayerTank :: changeBrickToSteel(bool b)
{
	for (int y = 23; y <= 25; y++)
	{
		m->UpdateTile( GetEngine(), 11, y, b + 1 );
		m->UpdateTile( GetEngine(), 14, y, b + 1 );
	}
	m->UpdateTile( GetEngine(), 12, 23, b + 1 );
	m->UpdateTile( GetEngine(), 13, 23, b + 1 );
}

void PlayerTank :: checkTouchWithBoundary()
{
	//The left boundary
	if ( (X+m_iStartDrawPosX) < 50 )
	{
		X = 50 - m_iStartDrawPosX;
		if ( speed_X < 0 )
				speed_X = -speed_X;
	}
	//The right boundary
	if ( (X+m_iStartDrawPosX+m_iDrawWidth) > 569 )
	{
		X = 569 - m_iStartDrawPosX - m_iDrawWidth;
		if ( speed_X > 0 )
			speed_X = -speed_X;
	}
	//The top boundary
	if ( (Y+m_iStartDrawPosY) < 50 )
	{
		Y = 50 - m_iStartDrawPosY;
		if ( speed_Y < 0 )
			speed_Y = -speed_Y;
	}
	//The bottom boundary
	if ( (Y+m_iStartDrawPosY+m_iDrawHeight) > (569) )
	{
		Y = 620 - 50 - 1 - m_iStartDrawPosY - m_iDrawHeight;
		if ( speed_Y > 0 )
			speed_Y = -speed_Y;
	}
}

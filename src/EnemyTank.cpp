#include "EnemyTank.h"
#include "GameProp.h"
#include "Bullet.h"

int EnemyTank:: enemyTank1 = 0;
int EnemyTank:: enemyTank2 = 0;
int EnemyTank:: enemyTank3 = 0;
int EnemyTank:: enemyTank4 = 0;

EnemyTank::EnemyTank(MyProjectMain* pEngine, MyTileManager* m , int startPosX, int startPosY, int id)
	:Tank(pEngine, m)
{
	this -> id = id;
	loadTankImage();

	m_iDrawWidth = im_TankU.GetWidth();
	m_iDrawHeight = im_TankU.GetHeight();
	
	m_iStartDrawPosX = -m_iDrawWidth/2;
	m_iStartDrawPosY = -m_iDrawHeight/2;
		
	//Just put it somewhere initially
	
	X = m_iPreviousScreenX = m_iCurrentScreenX = startPosX;
	Y = m_iPreviousScreenY = m_iCurrentScreenY = startPosY;

	speed_X = speed;
	speed_Y = speed;

	direction = 3;
}

EnemyTank::~EnemyTank(void)
{
}

/* load tank images */
void EnemyTank :: loadTankImage()
{
	switch(id)
	{
	case 0:
		tempL.LoadImage("enemyTank1L.png" );
		tempR.LoadImage("enemyTank1R.png");
		tempU.LoadImage("enemyTank1U.png");
		tempD.LoadImage("enemyTank1D.png");
		break;
	case 1:
		tempL.LoadImage("enemyTank1L_1.png" );
		tempR.LoadImage("enemyTank1R_1.png");
		tempU.LoadImage("enemyTank1U_1.png");
		tempD.LoadImage("enemyTank1D_1.png");
		break;
	case 2:
		tempL.LoadImage("enemyTank2L.png" );
		tempR.LoadImage("enemyTank2R.png");
		tempU.LoadImage("enemyTank2U.png");
		tempD.LoadImage("enemyTank2D.png");
		break;
	case 3:
		tempL.LoadImage("enemyTank2L_1.png" );
		tempR.LoadImage("enemyTank2R_1.png");
		tempU.LoadImage("enemyTank2U_1.png");
		tempD.LoadImage("enemyTank2D_1.png");
		break;
	case 4:
		tempL.LoadImage("enemyTank3L.png" );
		tempR.LoadImage("enemyTank3R.png");
		tempU.LoadImage("enemyTank3U.png");
		tempD.LoadImage("enemyTank3D.png");
		break;
	case 5:
		tempL.LoadImage("enemyTank4L.png" );
		tempR.LoadImage("enemyTank4R.png");
		tempU.LoadImage("enemyTank4U.png");
		tempD.LoadImage("enemyTank4D.png");
		break;
	case 6:
		tempL.LoadImage("enemyTank4L_1.png" );
		tempR.LoadImage("enemyTank4R_1.png");
		tempU.LoadImage("enemyTank4U_1.png");
		tempD.LoadImage("enemyTank4D_1.png");
		break;
	case 7:
		tempL.LoadImage("enemyTank4L_2.png" );
		tempR.LoadImage("enemyTank4R_2.png");
		tempU.LoadImage("enemyTank4U_2.png");
		tempD.LoadImage("enemyTank4D_2.png");
		break;
	case 8:
		tempL.LoadImage("enemyTank4L_3.png" );
		tempR.LoadImage("enemyTank4R_3.png");
		tempU.LoadImage("enemyTank4U_3.png");
		tempD.LoadImage("enemyTank4D_3.png");
		break;
	}
	im_TankD.ResizeTo(&tempD, 35, 35, false);
	im_TankR.ResizeTo(&tempR, 35, 35, false);
	im_TankU.ResizeTo(&tempU, 35, 35, false);
	im_TankL.ResizeTo(&tempL, 35, 35, false);

}


void EnemyTank :: DoUpdate( int iCurrentTime )
{

	MyProjectMain* myEngine = dynamic_cast <MyProjectMain*> (m_pEngine);
	if (myEngine -> isPausedState())
	{
		RedrawObjects();
		return;
	}
	if (!initial)
	{
		if (!IsVisible())
		return;

	double tempX = X;
	double tempY = Y;
	// Alter position for speed

	// if player eat clock treasure, the enemy is frozen
	if (gameProp != 5)
	{
		X += speed_X;
		Y += speed_Y;
	}


	checkCollisionWithOtherObjects(tempX, tempY);

	// If there is wall blocked at front, then just turnto another direction.
	if (isWallInFront())
	{
		X = tempX;
		Y = tempY;
		moveDownward();
	}
	setSpeedForDirection(direction);
		
	CheckCollisionWithBoundary();
		
	// Set current position
	m_iCurrentScreenX = (int)(X);
	m_iCurrentScreenY = (int)(Y);

	}
	RedrawObjects();
}

void EnemyTank ::reactToBulletCollision()
{
	switch (id)
	{
		case 0:// for normal tank
			shot = true;
			enemyTank1++;
			printf("%d", enemyTank1);
			break;
		case 1: // for red tank; when it hits bullets, a bonus will appear
			shot = true;
			(dynamic_cast <GameProp*>(m_pEngine->GetDisplayableObject(6))) -> randomSetID();
			(m_pEngine->GetDisplayableObject(6)) -> SetVisible(true);
			enemyTank1++;
			break;
		case 2:// for fast tank
			shot = true;
			enemyTank2++;
			break;
		case 3:// for red fast tank
			shot = true;
			(dynamic_cast <GameProp*>(m_pEngine->GetDisplayableObject(6))) -> randomSetID();
			(m_pEngine->GetDisplayableObject(6)) -> SetVisible(true);
			enemyTank2++;
			break;
		case 4: // for big tank
			shot = true;
			enemyTank3++;
			break;
		case 5: // for big tank which has hit bullet once
			id = 6;
			loadTankImage();
			break;
		case 6: // for big tank which has hit bullet once
			id = 7;
			loadTankImage();
			break;
		case 7: // for big tank which has hit bullet once
			id = 8;
			loadTankImage();
			break;
		case 8: // for big tank which has hit bullet twice
			enemyTank4++;
			shot = true;
			break;

	}		
	printf("%d,%d,%d,%d", enemyTank1,enemyTank2,enemyTank3,enemyTank4);
}

void EnemyTank ::checkCollisionWithOtherObjects(double tempX, double tempY)
{
	// Check all tanks and bullets
	DisplayableObject* p;
	for ( int i = 2; (p = m_pEngine->GetDisplayableObject( i )) != NULL ;	i++ )
	{
		Tank* tank = dynamic_cast<Tank*> (p);
		Bullet* bullet = dynamic_cast<Bullet*> (p);

		// skip itself and bullets belong to enemy tanks, and all invisible objects
		if ( p == this || !p->IsVisible() ||
			(bullet != NULL && !bullet->isfromPlayer())) 
			continue;
		
		// the distance on x and y coordinate
		int iXDiff = p->GetXCentre() -(int)(X);
		int iYDiff = p->GetYCentre() -(int)(Y);

		int iXDiff1 = p->GetXCentre() - m_iCurrentScreenX;
		int iYDiff1 = p->GetYCentre() - m_iCurrentScreenY; 

		int iSize = m_iDrawWidth/2;
		int iSizeOther = 0;

		bool isChecked = false;

		if (bullet != NULL) // bullets belongs to home tank
			iSizeOther = bullet->getWidth()/2;
		else if (tank != NULL)// other tanks
			iSizeOther = tank->getWidth()/2;
	

		if (((iXDiff1*iXDiff1)+(iYDiff1*iYDiff1)) 
			<= (iSizeOther+iSize)*(iSizeOther+iSize) && tank != NULL)
			isChecked = true;

		// Pythagorus' theorum:
		if (!isChecked && ((iXDiff*iXDiff)+(iYDiff*iYDiff)) 
			<= ((iSizeOther+iSize)*(iSizeOther+iSize)) )
		{
			if (bullet != NULL  && !shot)
			{
				reactToBulletCollision();
				bullet->SetVisible(false);
			}
			else if (tank != NULL )
			{
				// Stay at its original position and choose another direction
				X = tempX;
				Y = tempY;
				moveDownward();
			}
		}
	}
}

//set the enemey tank 50 percent posibility to move downwards, and 50% move to other direction
void EnemyTank :: moveDownward()
{
	int percentage = rand()%100;
	if (percentage <= 50)
		direction = rand()%4;
	else
	{
		direction = 3;
	}
}

void EnemyTank :: CheckCollisionWithBoundary()
{
	//Left boundary
	if ( (X+m_iStartDrawPosX) < 50 )
	{
		X = 50 - m_iStartDrawPosX;
		if ( speed_X < 0 )
		{
			direction = rand()%4; // randomly choose another direction
			setSpeedForDirection(direction);
		}
	}
	//Right boundary
	if ( (X+m_iStartDrawPosX+m_iDrawWidth) > 569 )
	{
		X = 569 - m_iStartDrawPosX - m_iDrawWidth;
		if ( speed_X > 0 )
		{
			direction = rand()%4;
			setSpeedForDirection(direction);
		}
	}
	//Top boundary
	if ( (Y+m_iStartDrawPosY) < 50 )
	{
		Y = 50 - m_iStartDrawPosY;
		if ( speed_Y < 0 )
		{
			direction = rand()%4;
			setSpeedForDirection(direction);
		}
	}
	//Bottom boundary
	if ( (Y+m_iStartDrawPosY+m_iDrawHeight) > 569 )
	{
		Y = 620 - 50 - 1 - m_iStartDrawPosY - m_iDrawHeight;
		
		if (X <= 310)
			direction = 2;
		else
			direction = 1;
		setSpeedForDirection(direction);
	}

}

void  EnemyTank :: setSpeedForDirection(int dir)
	{
		// When the identity of tank is 2 or 3, the enemy tank is faster
		if (id == 2 || id == 3)
			speed = fastSpeed;
		switch( dir%4 )
		{
		case 0: // Up
			speed_Y = -speed;
			speed_X = 0;    
			break;
		case 1: // Left
			speed_Y = 0;
			speed_X = -speed; 
			break;
		case 2: // Right
			speed_Y = 0;
			speed_X = speed;  
			break;
		case 3: // Down
			speed_Y = speed;
			speed_X		 = 0;
			break;
		}
	}
#include "Tank.h"
#include "header.h"
#include "templates.h"
#include "MyProjectMain.h"
#include "JPGImage.h"
#include "PlayerTank.h"
#include "EnemyTank.h"

int Tank::gameProp = 0;
Tank::Tank(MyProjectMain* pEngine, MyTileManager* mTileManager)
	:DisplayableObject(pEngine)
	, m(mTileManager)
	, counter(0)
	, counter1(0)
	, shot(false)
	, speed(2.5)
	, fastSpeed(4)
	, initial (true)
{
	temp1.LoadImage("explosion.png");
	im_explosion1.ResizeTo(&temp1, 35, 35, false);
	im_explosion2.ResizeTo(&temp1, 20, 20, false);
	temp2.LoadImage("appear.png");
	im_appear1.ResizeTo(&temp2, 33, 33, false);
	im_appear2.ResizeTo(&temp2, 20, 20, false);
	SetVisible(false);

	m_iDrawWidth = 35;
	m_iDrawHeight = 35;
	
	m_iStartDrawPosX = -m_iDrawWidth/2;
	m_iStartDrawPosY = -m_iDrawHeight/2;
}


Tank::~Tank(void)
{
}

// check whether there is a wall in front
bool Tank :: isWallInFront()
{
	int x[18];

	int y[18];

	int tileValue[18];
	
	//because tank is four tile size,
	// so check the four center and four vertices
	x[1] = x[2] = x[0] = X + m_iStartDrawPosX;
	y[3] = y[4] = y[0] = Y + m_iStartDrawPosY;
	
	x[3] = x[5] =x[0] + m_iDrawWidth / 2;
	x[4] = x[6] = x[7] = x[0] + m_iDrawWidth;

	y[1] = y[7] = y[0] + m_iDrawHeight / 2;
	y[2] = y[5] = y[6] = y[0]+ m_iDrawHeight;

	int iTileX;
	int iTileY;

	// Get the 8 points tile value
	for (int i = 0; i <= 7; i++)
	{
		iTileX = m->GetTileXForPositionOnScreen(x[i]);
		iTileY = m->GetTileYForPositionOnScreen(y[i]);
		tileValue[i] = m->GetValue( iTileX, iTileY );
	}

	// Check whether the 8 point collise with a walls
	for (int i = 0; i <= 7; i++)
	{
		if (tileValue[i] != 0 && tileValue[i] != 4)
			return true;
	}

	return false;
}

// When tank appear, draw the effect
void Tank :: appear()
{
	if (counter1 > 36)
		return;

	counter1++;
	m_iCurrentScreenX = X;
	m_iCurrentScreenY = Y;
	im_appear1.RenderImageWithMask( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - im_appear1.GetWidth()/2, m_iCurrentScreenY - im_appear1.GetHeight()/2,
						im_appear1.GetWidth(), im_appear1.GetHeight() );

	// Use counter1 to do the appear effect
	if (counter1 > 12)
	{
			im_appear2.RenderImageWithMask( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - im_appear2.GetWidth()/2, m_iCurrentScreenY - im_appear2.GetHeight()/2,
						im_appear2.GetWidth(), im_appear2.GetHeight() );
		if (counter1 > 24)
		{
			im_appear1.RenderImageWithMask( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - im_appear1.GetWidth()/2, m_iCurrentScreenY - im_appear1.GetHeight()/2,
						im_appear1.GetWidth(), im_appear1.GetHeight() );
			if (counter1 > 36){
				initial = false;
				SetVisible(true);
			}
		}
	}
	StoreLastScreenPositionAndUpdateRect();
}

void Tank :: Draw()
{

	MyProjectMain* myEngine = dynamic_cast <MyProjectMain*> (m_pEngine);
	PlayerTank* tank = dynamic_cast <PlayerTank*> (this);
	if (!(myEngine -> isPlayState() || myEngine -> isPausedState()))
	{
		SetVisible(false);
		return;
	}
	// if it is intial, the do the appear effect
	else if (initial )
	{
		appear();
	}

	if (shot)
	{
		SetVisible(false);

		if (tank != 0)
			{
				// if player, decrease a life
			if (id == 0 || id == 1){
				dynamic_cast <MyProjectMain*> (m_pEngine)->changeHomeTankLife(1, -1);
				setPosition(230, 550);
				counter1 = 0;
				initial = true;
			}
			else if (id == 2 || id == 3){
				dynamic_cast <MyProjectMain*> (m_pEngine)->changeHomeTankLife(2, -1);
				setPosition(390, 550);
				counter1 = 0;
				initial = true;
			}
			direction = 0;
		}
		shot = false;
		GetEngine() ->DrawRectangle(
		m_iCurrentScreenX - m_iDrawWidth/2 + 1,
		m_iCurrentScreenY - m_iDrawHeight/2 + 1,
		m_iCurrentScreenX + m_iDrawWidth/2 - 1,
		m_iCurrentScreenY + m_iDrawHeight/2 - 1,
		0x0);
		StoreLastScreenPositionAndUpdateRect();
				}
	else if (IsVisible()) //If visible draw it
	{
		if (direction == 0)
			im_TankU.RenderImage( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - im_TankU.GetWidth()/2, m_iCurrentScreenY - im_TankU.GetHeight()/2,
						im_TankU.GetWidth(), im_TankU.GetHeight() );
		else if (direction == 1)
			im_TankL.RenderImage( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - im_TankL.GetWidth()/2, m_iCurrentScreenY - im_TankL.GetHeight()/2,
						im_TankL.GetWidth(), im_TankL.GetHeight() );
		else if (direction == 2)
			im_TankR.RenderImage( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - im_TankR.GetWidth()/2, m_iCurrentScreenY - im_TankR.GetHeight()/2,
						im_TankR.GetWidth(), im_TankR.GetHeight() );
		else
			im_TankD.RenderImage( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - im_TankD.GetWidth()/2, m_iCurrentScreenY - im_TankD.GetHeight()/2,
						im_TankD.GetWidth(), im_TankD.GetHeight() );
		StoreLastScreenPositionAndUpdateRect();
	}
}
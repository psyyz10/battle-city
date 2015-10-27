#include "GameProp.h"

/** 
The game prop is the power-ups to help player
**/
GameProp::GameProp(MyProjectMain* pEngine)
	: DisplayableObject(pEngine)
	, counter (0)
{
	temp1.LoadImage("shovel.png");
	temp2.LoadImage("star.png");
	temp3.LoadImage("bomb.png");
	temp4.LoadImage("tank.png");
	temp5.LoadImage("helmet.png");
	temp6.LoadImage("clock.png");

	imShovel.ResizeTo(&temp1, 35,35, false);
	imStar.ResizeTo(&temp2, 35,35, false);
	imBomb.ResizeTo(&temp3, 35,35, false);
	imTank.ResizeTo(&temp4, 35,35, false);
	imHelmet.ResizeTo(&temp5, 35,35, false);
	imClock.ResizeTo(&temp6, 35,35, false);

	m_iDrawWidth = imShovel.GetWidth();
	m_iDrawHeight = imShovel.GetHeight();
	
	m_iStartDrawPosX = -m_iDrawWidth/2;
	m_iStartDrawPosY = -m_iDrawHeight/2;
		
	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = 80 + rand() % 470;
	m_iPreviousScreenY = m_iCurrentScreenY = 80 + rand() % 470;

	SetVisible(false);

}


GameProp::~GameProp(void)
{
}

void GameProp :: Draw()
{
	if (!IsVisible())
	{
		counter = 0;
		return;
	}
	switch (id)
	{
	case 1: // bonus of Shove
			imShovel.RenderImageWithMask( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - imShovel.GetWidth()/2, m_iCurrentScreenY - imShovel.GetHeight()/2,
						imShovel.GetWidth(), imShovel.GetHeight() );
		break;
	case 2: // bonus of bomb
			imBomb.RenderImageWithMask( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - imBomb.GetWidth()/2, m_iCurrentScreenY - imBomb.GetHeight()/2,
						imBomb.GetWidth(), imBomb.GetHeight() );
		break;
	case 3: // bonus tank life
			imTank.RenderImageWithMask( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - imTank.GetWidth()/2, m_iCurrentScreenY - imTank.GetHeight()/2,
						imTank.GetWidth(), imTank.GetHeight() );
		break;
	case 4: // bonus of Helmet
			imHelmet.RenderImageWithMask( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - imHelmet.GetWidth()/2, m_iCurrentScreenY - imHelmet.GetHeight()/2,
						imHelmet.GetWidth(), imHelmet.GetHeight() );
		break;
	case 5: // bonus of Clock
			imClock.RenderImageWithMask( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - imClock.GetWidth()/2, m_iCurrentScreenY - imClock.GetHeight()/2,
						imClock.GetWidth(), imClock.GetHeight() );
		break;

	}
	counter++;
	if (counter == 10000) // The appearence of bonus lasts for 1000 tick interval
		SetVisible(false);
	StoreLastScreenPositionAndUpdateRect();
}

void GameProp :: DoUpdate(int iCurrentTime)
{
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	RedrawObjects();

}
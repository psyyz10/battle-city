#include "Base.h"
#include "Bullet.h"
/**
This class is the base object for player to protected
**/

Base::Base(MyProjectMain* pEngine)
	:DisplayableObject(pEngine)
	,shot(false)
	,over(false)
{
	im_Temp1.LoadImage("eagle.png");
	im_Temp2.LoadImage("die.png");
	im_Die.ResizeTo(&im_Temp2, 40, 40, false);
	im_Eagle.ResizeTo(&im_Temp1, 40, 40, false);
	SetVisible(false);

	m_iDrawWidth = im_Eagle.GetWidth();
	m_iDrawHeight = im_Eagle.GetHeight();
	
	m_iStartDrawPosX = -m_iDrawWidth/2;
	m_iStartDrawPosY = -m_iDrawHeight/2;
	
	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = 310;
	m_iPreviousScreenY = m_iCurrentScreenY = 550;
}


Base::~Base(void)
{
}

void Base :: Draw ()
{
	if (!IsVisible())
		return;
	if (!shot)
	{
		
		im_Eagle.RenderImageWithMask( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - im_Eagle.GetWidth()/2, m_iCurrentScreenY - im_Eagle.GetHeight()/2,
						im_Eagle.GetWidth(), im_Eagle.GetHeight() );
		
	}
	else
	{
		// Draw the die image
		im_Die.RenderImageWithMask( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - im_Die.GetWidth()/2, m_iCurrentScreenY - im_Die.GetHeight()/2,
						im_Die.GetWidth(), im_Die.GetHeight() );
		over = true; // Mark that game is over, player loses
	}
	StoreLastScreenPositionAndUpdateRect();
}

void Base :: DoUpdate (int iCurrentTime)
{

	MyProjectMain* myEngine = dynamic_cast <MyProjectMain*> (m_pEngine);

	if (!(myEngine -> isPlayState()))
	{
		SetVisible(false);
		return;
	}

	SetVisible(true);
	DisplayableObject* pObject;
	for ( int iObjectId = 2 ; 
			(pObject = m_pEngine->GetDisplayableObject( iObjectId )
			) != NULL ;
		iObjectId++ )
	{
		// Consider all bullets
		Bullet* bullet = dynamic_cast<Bullet*> (pObject);

		// Skip all non-bullets objects and invisible bullets
		if (bullet == NULL || !bullet->IsVisible()) 
			continue;

		int iXDiff = pObject->GetXCentre() - m_iCurrentScreenX ;
		int iYDiff = pObject->GetYCentre() - m_iCurrentScreenY;

		int iSize = m_iDrawWidth/2;
		int iSizeOther = bullet->getWidth()/2;


		// Pythagorus' theorum, check collision with bullets:
		if (((iXDiff*iXDiff)+(iYDiff*iYDiff)) 
			<= ((iSizeOther+iSize)*(iSizeOther+iSize)) )
		{
			shot = true;	
			bullet->SetVisible(false);
		}
	}

	RedrawObjects();

}
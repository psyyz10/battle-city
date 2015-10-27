#include "SelectionIcon.h"
#include "header.h"
#include "templates.h"
#include "MyProjectMain.h"


SelectionIcon::SelectionIcon(BaseEngine* pEngine)
	:DisplayableObject(pEngine)
{
	SetVisible(0);
	icon.LoadImage("tank1R.png");
	im.ResizeTo(&icon,30,30, false);

	// initial a position
	m_iCurrentScreenX = m_iPreviousScreenX = 205; 
	m_iCurrentScreenY = m_iPreviousScreenY = 343;
	m_iDrawWidth = icon.GetWidth();
	m_iDrawHeight = icon.GetHeight();
	
	m_iStartDrawPosX = -m_iDrawWidth/2;
	m_iStartDrawPosY = -m_iDrawHeight/2;
}


SelectionIcon::~SelectionIcon(void)
{

}

void SelectionIcon :: Draw()
{
	if (!IsVisible())
		return;
	im.RenderImageWithMask( GetEngine()->GetForeground(), 
						0,0, 
						m_iCurrentScreenX - im.GetWidth()/2, m_iCurrentScreenY,
						im.GetWidth(), im.GetHeight() );

	StoreLastScreenPositionAndUpdateRect();
}

void SelectionIcon :: DoUpdate(int iCurrentTime )
{
	if (!IsVisible())
		return;

	// change position every option changes
	if (dynamic_cast <MyProjectMain*> (m_pEngine)->isLevelState())
	{
		switch (dynamic_cast <MyProjectMain*> (m_pEngine)->getOption() )
		{
		case 0:
			m_iCurrentScreenY = 80 + 40;
			break;
		case 1:
			m_iCurrentScreenY = 120 + 40;
			break;
		case 2:
			m_iCurrentScreenY = 160 + 40;
			break;
		case 3:
			m_iCurrentScreenY = 200 + 40;
			break;
		case 4:
			m_iCurrentScreenY = 240 + 40;
			break;
		case 5:
			m_iCurrentScreenY = 280 + 40;
			break;
		case 6:
			m_iCurrentScreenY = 320 + 40;
			break;
		}
	}
	else
	{
		switch (dynamic_cast <MyProjectMain*> (m_pEngine)->getOption() )
		{
		case 0:
			m_iCurrentScreenY = 343;
			break;
		case 1:
			m_iCurrentScreenY = 385;
			break;
		case 2:
			m_iCurrentScreenY = 425;
			break;
		case 3:
			m_iCurrentScreenY = 465;
			break;
		}
	}
	
	RedrawObjects();
}

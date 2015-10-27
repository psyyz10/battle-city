#ifndef BULLET_H
#define BULLET_H
#include "displayableobject.h"
#include "Tank.h"
#include "MyProjectMain.h"
#include "MovementPosition.h"

class Bullet :
	public DisplayableObject
{
public:
	Bullet(MyProjectMain* pEngine, Tank* t, MyTileManager* m, bool fromPlayer = true);
	~Bullet(void);
	double getWidth ()
	{
		return m_iDrawWidth;
	}

	bool isfromPlayer()
	{
		return fromPlayer;
	}

	void SetMovement( int iStartTime, int iEndTime, int iCurrentTime,
							   int iStartX, int iStartY, int iEndX, int iEndY )
	{
		m_oMover.Setup( iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime );
		m_oMover.Calculate( iCurrentTime );
		m_iCurrentScreenX = m_oMover.GetX();
		m_iCurrentScreenY = m_oMover.GetY();
	}

	void checkTouchWithOtherBullets();

	void Draw();

	void DoUpdate( int iCurrentTime );

private :
	bool fromPlayer;
	Tank* tank;
	MovementPosition m_oMover;
	MyTileManager* m_pTileManager; 
	ImageData im_Bullet;
	ImageData im;
	ImageData im_explosion1, im_explosion2, temp1, temp2;
};
#endif

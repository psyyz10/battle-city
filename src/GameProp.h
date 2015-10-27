#ifndef GAMEPRO_H
#define GAMEPRO_H
#include "displayableobject.h"
#include "MyProjectMain.h"
#include "JPGImage.h"

class GameProp :
	public DisplayableObject
{
public:
	GameProp(MyProjectMain* pEngine);
	~GameProp(void);

	int getWidth()
	{
		return m_iDrawWidth;
	}

	int getHeight()
	{
		return m_iDrawHeight;
	}

	int getID()
	{
		return id;
	}

	void randomSetID()
	{
		id = rand()%5 + 1;
		m_iCurrentScreenX =  80 + rand() % 470 ;
		m_iCurrentScreenY =  80 + rand() % 470 ;
	}
	void Draw();

	void DoUpdate(int iCurrentTime);

private:
	int id;
	ImageData imBomb, imClock, imHelmet, imShovel, imTank, imStar, temp1, temp2, temp3, temp4, temp5, temp6;
	int counter;
};

#endif
#pragma once

#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include "tank.h"
#include "MyProjectMain.h"
#include "MyTileManager.h"
#include "Bullet.h"
#include "GameProp.h"
#include "JPGImage.h"

class PlayerTank :
	public Tank
{
public:
	PlayerTank(MyProjectMain* pEngine, MyTileManager* m , int id);
	~PlayerTank(void);
	void loadTankImage();
	//void Draw();
	void changeSpeedWhenKeyPressed();
	void checkTouchWithOtherObjects(int X, int Y);
	void checkTouchWithBoundary();
	void DoUpdate(int iCurrentTime );
	void touchWithGameProp(int id);
	void changeBrickToSteel(bool b);
	void changeSteelToBrick();
	void setPosition(int X, int Y)
	{
		this->X = X;
		this->Y = Y;
	}
	void setID(int id)
	{
		this->id = id;
	}

	void changTankState(int i)
	{
		if (i == 1)
		{
			id = 1;
			loadTankImage();
		}
		else if (i == 0)
		{
			id = 0;
			loadTankImage();
		}
		else if (i == 2)
		{
			id = 2;
			loadTankImage();
		}
		else if (i == 3)
		{
			id = 3;
			loadTankImage();
		}
	}
private:
	int startCounter;
	bool imageSate;
};

#endif
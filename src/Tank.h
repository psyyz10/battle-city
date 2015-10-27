#pragma once

#ifndef TANK_H
#define TANK_H

#include "displayableobject.h"
#include "JPGImage.h"
#include "MyProjectMain.h"

class Tank :
	public DisplayableObject
{
public:
	static int gameProp;
	Tank(MyProjectMain* pEngine, MyTileManager* m);
	~Tank(void);

	int getHeight()
	{
		return m_iDrawHeight;
	};

	int getWidth()
	{
		return m_iDrawWidth;
	};

	int getDirection()
	{
		return direction;
	}

	void Draw();

	void setShot(bool shot)
	{
		this -> shot = shot;
	}

	void setPosition(int X, int Y)
	{
		this->X  = X;
		this->Y  = Y;
		m_iCurrentScreenX = X;
		m_iCurrentScreenY = Y;
	}

	void setInitial(bool initial)
	{
		this->initial = initial;
	}

	bool isInitial ()
	{
		return initial;
	}

	int getID()
	{
		return id; 
	}
	bool isWallInFront();

	void appear();

protected:
	// position
	double X;
	double Y;
	// record whether tank is shot
	bool shot;
	// speed
	double speed_X;
	double speed_Y;

	double speed;
	double fastSpeed;

	int direction;
	ImageData im_explosion1, im_explosion2, im_appear1, im_appear2, temp1, temp2;
	ImageData im_TankL, im_TankR, im_TankU, im_TankD, tempU,tempD, tempR, tempL;
	int id;
	int counter;
	int counter1;
	bool initial;
	int gamePropTime;

	MyTileManager* m;
};

#endif
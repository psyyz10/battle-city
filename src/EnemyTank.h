#ifndef ENEMYTANK_H
#define ENEMYTANK_H
#include "tank.h"
#include "MyProjectMain.h"
#include "MyTileManager.h"

class EnemyTank :
	public Tank
{
public:
	EnemyTank(MyProjectMain* pEngine, MyTileManager* m , int startPosX, int startPosY, int id);
	~EnemyTank(void);

	//void Draw();

	void loadTankImage();

	void setSpeedForDirection(int dir);

	void checkCollisionWithOtherObjects(double tempX, double tempY);

	void DoUpdate(int iCurrentTime);
	void reactToBulletCollision();

	void CheckCollisionWithBoundary();

	void moveDownward();

	static int enemyTank1;
	static int enemyTank2;
	static int enemyTank3;
	static int enemyTank4;

};

#endif
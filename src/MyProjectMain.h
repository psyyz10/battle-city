#ifndef MYPROJECTMAIN_H
#define MYPROJECTMAIN_H

#include "BaseEngine.h"
#include "JPGImage.h"
#include "MyTileManager.h"

class EnemyTank;
class MyProjectMain : public BaseEngine
{
public:

	/**
	Constructor
	*/
	MyProjectMain (void);

	~MyProjectMain (void);

	// Do any setup of back buffer prior to locking the screen buffer
	// Basically do the drawing of the background in here and it'll be copied to the screen for you as needed
	virtual void SetupBackgroundBuffer();

	// Create any moving objects
	int InitialiseObjects();

	/** Draw any strings */
	void DrawStrings();
	//void DrawChanges();
	//void StoreLastScreenPositionAndUpdateRect();
	
	/**
	The game logic - move things and change the state if necessary.
	Must call Redraw(true/false) if anything changes that shows on the screen.
	*/
	bool isPausedState()
	{
		return state == pausedState;
	}

	bool isLevelState()
	{
		return state == levelState;
	}

	virtual void GameAction();
	void initialiseNextStage(bool isRestarted);
	void drawEnemyLife();
	
	virtual void KeyDown(int iKeyCode);

	void calculateCurrentScore();

	enum State {initState, onePlayState, twoPlayState, pausedState,  overState, levelState, transitionState, scoreState};
	bool isBackFromPause()
	{
		return backFromPause;
	}
	void setBackFromPause(bool backFromPause)
	{
		this ->backFromPause = backFromPause;
	}

	void nextOption();
	void lastOption();
	int getOption();
	void fire(int player);
	bool isPlayState()
	{
		return (state == onePlayState || state == twoPlayState) ;
	};
	void doOption();

	void drawPlayBackground(int number);
	void loadLevel(char* file);
	void loadHighestScore();
	//void DrawScreen();


	void changeHomeTankLife (int player, int life)
	{
		if (player == 1)
			player1LifeLeft = player1LifeLeft + life;
		else if (player == 2)
			player2LifeLeft = player2LifeLeft + life;
	}
	void drawBackgroundInformation(int player);
	void saveHighestScore();
	void checkEnd(void);

	private:
		State state;
		int option;
		MyTileManager m;
		ImageData im, imCover, imControl, imEnemyLife, imPlayerLife, imFlag, imGameOver, imScore;
		int level;
		int highestScore;
		int currentScore;
		int player1LifeLeft;
		int player2LifeLeft;
		int playerNumber;
		int accumulateScore;
		bool noEnemy;
		bool initialized;
		bool backFromPause;
		bool newHighScore;
		int lastLevel;
		int currentTime;
		int enemy1, enemy1Accumulate, enemy2, enemy2Accumulate, enemy3, enemy3Accumulate, enemy4, enemy4Accumulate;
		//EnemyTank* enemyTank1, enemyTank2;
		EnemyTank* enemyTank1;	
		EnemyTank* enemyTank;
		EnemyTank* enemyTank3;
		EnemyTank* enemyTank4;
		int numberOfEnemyTankLeft;
		DisplayableObject* pObject;
		
};

#endif

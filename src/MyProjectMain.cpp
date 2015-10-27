#include "header.h"
#include "templates.h"

#include "BaseEngine.h"

#include "MyProjectMain.h"

#include "JPGImage.h"
#include "EnemyTank.h"
#include "TileManager.h"
#include "PlayerTank.h"
#include "DisplayableObject.h"
#include "SelectionIcon.h"
#include "PlayerTank.h"
#include "Base.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime> 
using namespace std;

MyProjectMain::MyProjectMain(void)
: BaseEngine( 50 )
, state(initState)
, option(0)
, level(1)
, playerNumber(1)
, currentScore(0)
, player1LifeLeft(3)
, player2LifeLeft(3)
, noEnemy(false)
, lastLevel(7)
, accumulateScore(0)
, numberOfEnemyTankLeft(20)
, initialized(0)
, backFromPause(0)
, newHighScore (0)
, enemy1(0), enemy2(0), enemy3(0), enemy4(0)
, enemy1Accumulate(0), enemy2Accumulate(0), enemy3Accumulate(0), enemy4Accumulate(0)
{
	//load images
	im.LoadImage( "control.png" );
	imControl.ResizeTo(&im,160,620,false);
	im.LoadImage( "cover.png" );
	imCover.ResizeTo(&im,670,620,false);
	im.LoadImage("tank1U.png");
	imPlayerLife.LoadImage("playerLife.png");
	imFlag.LoadImage("flag.png");
	imScore.LoadImage("score.png");
	im.LoadImage("enemyLife.png");
	imEnemyLife.ResizeTo(&im, 20,18,false);
	im.LoadImage("gameover.png");
	imGameOver.ResizeTo(&im,670,620,false);
	loadHighestScore();
	m.SetSize( 26, 26 );


}

MyProjectMain::~MyProjectMain(void)
{
}

/* setup background based on the state */
void MyProjectMain::SetupBackgroundBuffer()
{
	
	

	FillBackground( 0x000000 );

	imControl.RenderImage( this->GetBackground(), 
						0,0, 
						670,0,
						imControl.GetWidth(), imControl.GetHeight());

	switch (state)
	{
	char buffer[20];
	case initState:
		m_ppDisplayableObjects [0] ->SetVisible(true);
		imCover.RenderImage( this->GetBackground(), 
						0,0, 
						0,0,
						imCover.GetWidth(), imCover.GetHeight());	
		break;
	case onePlayState:	// onePlayState, set the map
		if (!backFromPause)
		{
			sprintf(buffer, "level%d.txt", level);
			loadLevel(buffer);
			m.SetBaseTilesPositionOnScreen( 50, 50 );
		}
	
		drawPlayBackground(1);
		break;
	case twoPlayState:// twoPlayState, set the map
		if (!backFromPause)
		{
			sprintf(buffer, "level%d.txt", level);
			loadLevel(buffer);
			m.SetBaseTilesPositionOnScreen( 50, 50 );
		}
		drawPlayBackground(2);
		break;
	case pausedState:
		break;
		
	case overState:
		imGameOver.RenderImage( this->GetBackground(), 
						0,0, 
						0,0,
						imGameOver.GetWidth(), imGameOver.GetHeight() );
		break;
	case levelState:
		break;
	case scoreState:
		imScore.RenderImage( this->GetBackground(), 
						0,0, 
						140,150,
						imScore.GetWidth(), imScore.GetHeight());	
		break;
	}
	
}

void MyProjectMain :: drawPlayBackground(int number)
{
	FillBackground( 0x000000 );
	// Draw the boundary background, and fill it to grey.

	DrawBackgroundRectangle(0, 0, 670, GetScreenHeight(), 0xC0C0C0);

	imControl.RenderImage( this->GetBackground(), 
						0,0, 
						670,0,
						imControl.GetWidth(), imControl.GetHeight());

	imPlayerLife.RenderImage( this->GetBackground(), 
						0,0, 
						600, 380,
						imPlayerLife.GetWidth(), imPlayerLife.GetHeight() );
	if (playerNumber == 2)
	{
		imPlayerLife.RenderImage( this->GetBackground(), 
						0,0, 
						600, 440,
						imPlayerLife.GetWidth(), imPlayerLife.GetHeight() );
	}
	imFlag.RenderImage( this->GetBackground(), 
						0,0, 
						600, 470,
						imFlag.GetWidth(), imFlag.GetHeight() );

	// Draw tile in tile array, to the background of this screen
	m.DrawAllTiles( this, 
		this->GetBackground(), 
		0, 0, 25, 25 );

}

int MyProjectMain::InitialiseObjects()
{
	srand(time(0));

	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// Create an array one element larger than the number of objects that you want.
	m_ppDisplayableObjects = new DisplayableObject*[18];

	SelectionIcon* selectionIcon = new SelectionIcon(this);
	m_ppDisplayableObjects [0] = selectionIcon;
	Base* base = new Base(this);
	m_ppDisplayableObjects[1] = base;
	PlayerTank* playerTank1 = new PlayerTank(this, &m, 0);
	PlayerTank* playerTank2 = new PlayerTank(this, &m, 2);
	m_ppDisplayableObjects[2] = playerTank1;
	m_ppDisplayableObjects[3] = new Bullet(this, playerTank1, &m, true);
	m_ppDisplayableObjects[4] = playerTank2;
	m_ppDisplayableObjects[5] = new Bullet(this, playerTank2, &m, true);
	m_ppDisplayableObjects[6] = new GameProp (this);

	//initialize enemy tanks
	for (int i = 7; i <= 15; i = i + 2)
	{
		m_ppDisplayableObjects[i] = new EnemyTank(this, &m, 70 + 80 * rand() % 6, 60, rand() % 6);
		m_ppDisplayableObjects[i+1] = new Bullet(this, dynamic_cast <EnemyTank*> (m_ppDisplayableObjects[i]), &m, 0);
		dynamic_cast <EnemyTank*> (m_ppDisplayableObjects[i]) -> setInitial(0);
	}

 	m_ppDisplayableObjects[17] = NULL;
	currentTime = 0;

	return 0;
}

int MyProjectMain :: getOption()
{
	return option;
}

// move the select cursor down, then the option changed
void MyProjectMain :: nextOption(){
	if (state == initState)
		option = (option + 1) % 3;
	else if (state == levelState)
		option = (option + 1) % 7;
}

// move the select cursor up, then the option changed
void MyProjectMain :: lastOption(){
	if (state == initState)
	{
		if (option == 0)
			option = 2;
		else 
			option = (option - 1) % 2;
	}
	else if (state == levelState)
	{
		if (option == 0)
			option = 6;
		else 
			option = (option - 1) % 6;
	}
}




/* Draw text labels */
void MyProjectMain::DrawStrings()
{
	 //Build the string to print
	char buf[128];

	switch( state )
	{
	case initState:
		CopyBackgroundPixels( 50, 50, 300, 100);
		sprintf(buf,"%d", highestScore);
		DrawScreenString( 250, 50, buf, 0xfffff0, m_oFontManager.GetFont("Cornerstone Regular.ttf", 25));
		SetNextUpdateRect( 50, 50, 300, 100);
		break;
	case onePlayState:
		drawBackgroundInformation(1);
		break;
	case twoPlayState:
		drawBackgroundInformation(2);
		break;
	case levelState:
		CopyBackgroundPixels( 50, 200, 520, 300 );
		for (int i = 0; i < 7; i ++)
		{
			sprintf(buf,"STAGE %d", i + 1);
			DrawScreenString( 250, 120 + i * 40, buf, 0xe91919, NULL );
		}
		DrawScreenString( 200, 500, "Press H to rstart", 0xe91919, m_oFontManager.GetFont("Cornerstone Regular.ttf", 20) );
		SetNextUpdateRect( 50, 200, 520, 300 );
		break;

	case transitionState:
		char buf[128];
		
		CopyBackgroundPixels( 0, 280, GetScreenWidth(), 40 );
		sprintf( buf, "STAGE %d", level+1 );
		DrawScreenString( 240, 200, buf, 0xe50707, m_oFontManager.GetFont( "Cornerstone Regular.TTF", 40 ) );
		DrawScreenString( 190, 400, "Press H to start", 0xe50707, m_oFontManager.GetFont( "Cornerstone Regular.TTF", 30 ) );
		SetNextUpdateRect( 0/*X*/, 280, GetScreenWidth(), 40 );
		break;
	case pausedState:
		CopyBackgroundPixels( 50, 280,520, 300 );
		DrawScreenString( 150, 300, "Paused. Press H to continue", 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 20));
		SetNextUpdateRect( 50, 280, 520, 300 );
		break;
	case scoreState:
		CopyBackgroundPixels( 50, 50, 570, 130);
		DrawScreenString( 80, 70, "HI Score ", 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 20) );
		sprintf(buf, " %d", highestScore);
		DrawScreenString( 230, 70, buf, 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 30) );

		// draw the score
		sprintf(buf, " %d", enemy1);
		DrawScreenString( 270, 170, buf, 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 26) );
		sprintf(buf, " %d", enemy1 * 100);
		DrawScreenString( 110, 170, buf, 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 26) );
		sprintf(buf, " %d", enemy2);
		DrawScreenString( 270, 230, buf, 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 26) );
		sprintf(buf, " %d", enemy2 * 200);
		DrawScreenString( 110, 230, buf, 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 26) );
		sprintf(buf, " %d", enemy3);
		DrawScreenString( 270, 290, buf, 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 26) );
		sprintf(buf, " %d", enemy3 * 300);
		DrawScreenString( 110, 290, buf, 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 26) );
		sprintf(buf, " %d", enemy4);
		DrawScreenString( 270, 350, buf, 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 26) );
		sprintf(buf, " %d", enemy4 * 400);
		DrawScreenString( 110, 350, buf, 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 26) );
		sprintf(buf, " %d", currentScore);

		DrawScreenString( 320, 420, buf, 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 35) );
		DrawScreenString( 150, 510, "Press H to restart", 0xffffff, m_oFontManager.GetFont("Cornerstone Regular.ttf", 25) );
		SetNextUpdateRect( 50/*X*/, 50/*Y*/, 520, 130/*Height*/ );
		break;
	case overState:

		if (newHighScore)
		{
			FillBackground(0x0);
			CopyBackgroundPixels( 50/*X*/, 50/*Y*/, /*GetScreenWidth()*/520, 520/*Height*/ );
			DrawScreenString( 180, 250, "HIGH SCORE", 0xf80202, m_oFontManager.GetFont("Cornerstone Regular.ttf", 35));
			SetNextUpdateRect( 50/*X*/, 50/*Y*/, /*GetScreenWidth()*/520, 520/*Height*/ );
		}
		break;
	}
}

void MyProjectMain :: drawBackgroundInformation(int player)
{
	char buf[128];

	CopyBackgroundPixels( 0, 0, 570, 50);
	DrawScreenString( 80, 580,"Press N to next stage", 0x808080, m_oFontManager.GetFont("Cornerstone Regular.ttf", 30));
	SetNextUpdateRect( 0/*X*/, 0/*Y*/, 570, 50/*Height*/ );

	CopyBackgroundPixels( 570, 50,  100, 570);
	DrawBackgroundRectangle(570, 50,  660, 330, 0xC0C0C0);
	drawEnemyLife();

	DrawScreenString( 600, 340,"1P", 0x0, m_oFontManager.GetFont("Cornerstone Regular.ttf", 30));

	// draw player 1 life left
	if (player1LifeLeft < 0)
		sprintf( buf, "%d", 0);
	else 
		sprintf( buf, "%d", player1LifeLeft);
	DrawScreenString( 630, 380, buf, 0x0 );

	// draw player 2 life left
	if (playerNumber == 2)
	{
		DrawScreenString( 600, 410,"2P", 0x0, m_oFontManager.GetFont("Cornerstone Regular.ttf", 30));
		if (player2LifeLeft < 0)
			sprintf( buf, "%d", 0);
		else 
			sprintf( buf, "%d", player2LifeLeft);
		DrawScreenString( 630, 440, buf, 0x0 );
	}
	sprintf( buf, "%d", level ); // draw level number
	DrawScreenString( 620, 510, buf, 0x0 , m_oFontManager.GetFont("Cornerstone Regular.ttf", 30));
	SetNextUpdateRect( 570/*X*/, 50/*Y*/, 200, 570/*Height*/ );

}

void MyProjectMain:: drawEnemyLife()
{
	// dra enemey life left
	for (int i = 0; i < numberOfEnemyTankLeft; i++)
	imEnemyLife.RenderImage( this->GetBackground(), 
						0,0, 
						600 + (i % 2) * 22, 70 + (i / 2) * 20,
						imEnemyLife.GetWidth(), imEnemyLife.GetHeight() );	
}


void MyProjectMain::GameAction()
{
	// If too early to act then do nothing
	if ( !TimeToAct() )
		return;

	// Don't act for another 10 ticks
	SetTimeToAct( 17 );

	// Tell all objects to update themselves
	UpdateAllObjects( GetTime() );

	switch( state )
	{
	case initState:
		break;
	case pausedState:
		break;
	case onePlayState:
	case twoPlayState: 
		/*In play state, ever 120 time unit, a new enemy tank appears*/
 		if (currentTime < 120)
		{
			currentTime++;
			break;
		}
		noEnemy = true;

		// if there are still some enemy not have been appeared
		if (numberOfEnemyTankLeft > 0)
		{
			for ( int i = 1 ; (pObject = GetDisplayableObject( i )) != NULL ; i++ )
			{
				EnemyTank* enemyTank = dynamic_cast<EnemyTank*> (pObject);

				/* choose the first invisible and uninitial tank*/
				if (enemyTank != NULL){
					if ((!enemyTank -> IsVisible()) && (!enemyTank -> isInitial()))
					{
						m_ppDisplayableObjects[i] = new EnemyTank(this, &m, 50 + rand() % 480, 70, rand() % 6);
						m_ppDisplayableObjects[i+1] = new Bullet(this, dynamic_cast <EnemyTank*> (m_ppDisplayableObjects[i]), &m, 0);
						numberOfEnemyTankLeft--;
						currentTime = 0;
						break;
					}
				
				}
			}
		}

		checkEnd();
		break;
	case transitionState:
		if (!initialized)
		{
			// if last level, go back to the first level
			if (level == lastLevel)
			{
				level = 0;
				initialiseNextStage(false);
			}
			else
				initialiseNextStage(false);
			SetupBackgroundBuffer();
			Redraw(true);
			initialized = true;

		}
		break;
	case scoreState:
		if (!initialized) 
		{	
			SetupBackgroundBuffer();
			Redraw(true);
			initialized = true;
			initialiseNextStage(true);
		}
		break;
	}

	if (backFromPause)
	{
		backFromPause = 0;
	}
}

/* calculate the current score */
void MyProjectMain::calculateCurrentScore()
{
	currentScore = accumulateScore + (EnemyTank :: enemyTank1) * 100 + (EnemyTank :: enemyTank2) * 200
		+ (EnemyTank :: enemyTank3) * 300 + (EnemyTank :: enemyTank4) * 400;
	enemy1 = enemy1Accumulate + (EnemyTank :: enemyTank1);
	enemy2 = enemy2Accumulate + (EnemyTank :: enemyTank2);
	enemy3 = enemy3Accumulate + (EnemyTank :: enemyTank3);
	enemy4 = enemy4Accumulate + (EnemyTank :: enemyTank4);
}


void MyProjectMain::KeyDown(int iKeyCode)
{
	switch ( iKeyCode )
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode( 0 );
		break;
	
	case (SDLK_UP ) : //move cursor up
		if (state == initState || state == levelState){
			lastOption();
		}
		break;
	case SDLK_DOWN://move cursor down
		if (state == initState || state == levelState){
			nextOption();
		}
		break;

	case SDLK_f: //move cursor down
		if (state == initState){
			nextOption();
		}
		break;
	case SDLK_SPACE:
	case SDLK_h:
		if (state == initState || state == levelState)//start game
		{
			doOption();
			SetupBackgroundBuffer();
			m_ppDisplayableObjects [0] -> SetVisible(false);
			if (state == levelState)
				m_ppDisplayableObjects [0] -> SetVisible(1);
			Redraw(true);
		}
		else if (state == onePlayState || state == twoPlayState)// pause game
		{
			state = pausedState;
		}
		else if (state == pausedState) //start game from paused state
		{
			if (playerNumber == 1)
				state = onePlayState;
			else if (playerNumber == 2)
				state = twoPlayState;	
			backFromPause = true;
			SetupBackgroundBuffer();
			Redraw(true);
		}
		else if (state == scoreState)
		{
			state = overState;// change to overState

			SetupBackgroundBuffer();
			Redraw(true);
		}
		else if (state == overState)
		{
			state = initState; //change to init state

			SetupBackgroundBuffer();
			Redraw(true);
		}
		if (state == transitionState)
		{
			level++;
			if (playerNumber == 1)
			{
				state = onePlayState;
			}
			else
			{
				state = twoPlayState;
			}
			SetupBackgroundBuffer();
			Redraw(true);
		}
			

		break;

	case SDLK_j: // player 1 fires when j is pressed
		fire(1);
		break;
	case SDLK_RCTRL:// player 2 fires when right control is pressed
		fire(2);
		break;
	case SDLK_n: // jump to next level
		if (!(state == onePlayState || state == twoPlayState))
			break;

		if (level == lastLevel)
			level = 0;

		state = transitionState;
		numberOfEnemyTankLeft = 20;
		initialized = 0;
		
		break;
	}
}

void MyProjectMain :: fire(int player)
{

	PlayerTank* tank = NULL; 
	Bullet* bullet = NULL;

	// get player tank and bullet depends on which player fires
	if (player == 1)
	{
		tank = dynamic_cast<PlayerTank*> (m_ppDisplayableObjects[2]);
		bullet = dynamic_cast<Bullet*> (m_ppDisplayableObjects[3]);
	}
	else
	{
		tank = dynamic_cast<PlayerTank*> (m_ppDisplayableObjects[4]);
		bullet = dynamic_cast<Bullet*> (m_ppDisplayableObjects[5]);
	}


	int ID = tank->getID(); // Get the status of home tank
	int distance;
	int interval = 1400;
	if (ID == 1 || ID == 3)// If the home tank is big size, then its bullets movement interval becomes smaller
	{						// bullets move faster
		interval = 1000;
	}
	if (state == onePlayState || state == twoPlayState)
	{

			if (!bullet->IsVisible())
			{
				bullet->SetVisible(true);
			
				switch (tank->getDirection())
				{
				case 0: //Up
					distance = tank->GetYCentre()- tank->getHeight()/2 - 50;
					bullet->SetMovement(  GetTime(), GetTime()+interval * distance / 520, GetTime(),
							tank->GetXCentre(), tank->GetYCentre()- tank->getHeight()/2 , tank->GetXCentre() , 50);
					break;
				case 1: //Left
					distance = tank->GetXCentre()- tank->getWidth()/2 - 50;
					bullet->SetMovement(  GetTime(), GetTime()+interval * distance / 520, GetTime(),
							tank->GetXCentre()- tank->getWidth()/2, tank->GetYCentre() , 50 , tank->GetYCentre());
					break;
				case 2: //Right
					distance = 570 - tank->GetXCentre()+tank->getWidth()/2;
					bullet->SetMovement(  GetTime(), GetTime()+interval * distance / 520, GetTime(),
							tank->GetXCentre()+tank->getWidth()/2, tank->GetYCentre() , 570 , tank->GetYCentre());
					break;
				case 3: //Down
					distance = 570 - tank->GetYCentre()+ tank->getHeight()/2;
					bullet->SetMovement(  GetTime(), GetTime()+interval * distance / 520, GetTime(),
							tank->GetXCentre(), tank->GetYCentre()+ tank->getHeight()/2 , tank->GetXCentre() , 570);
					break;
				}
			}
	}
}

/* Make a decision at welcome page */
void MyProjectMain :: doOption()
{
	if (state == initState)
	{
		switch (option)
		{
		case 0:
			state = onePlayState;
			dynamic_cast <PlayerTank*> (m_ppDisplayableObjects[4]) ->setInitial(0);
			playerNumber = 1;
			break;
		case 1:
			state = twoPlayState;
			playerNumber = 2;
			break;
		case 2:
			state = levelState;
			option = 0;
			break;
		}
	}
	else if (state == levelState)
	{
		state = onePlayState;
		dynamic_cast <PlayerTank*> (m_ppDisplayableObjects[4]) ->setInitial(0);
		playerNumber = 1;
		level = option + 1;
	}
}

/* check whether the game ends */
void MyProjectMain::checkEnd(void)
{
	calculateCurrentScore();


	for (int i = 7; i <= 16; i++)
	{
		if (m_ppDisplayableObjects[i] != NULL && m_ppDisplayableObjects[i]->IsVisible())
		{
			noEnemy = 0;
				break;
		}
	}//

	// if no enemy left, win and go next level
	if (noEnemy && numberOfEnemyTankLeft == 0)
	{
		if (level == lastLevel && currentScore > highestScore)
			saveHighestScore();

		state = transitionState;
		numberOfEnemyTankLeft = 20;
		initialized = 0;
	}
	else if (state == onePlayState)
	{
		// if no player life or base is over, then game over
		if (player1LifeLeft < 0|| (dynamic_cast <Base*> (m_ppDisplayableObjects[1]))->isOver())
		{
			state = scoreState;
			initialized = 0;
			if (currentScore > highestScore)
				saveHighestScore();
		}

	}
	else if (state == twoPlayState)
	{
		// if no player life or base is over, then game over
		if ((player1LifeLeft < 0 && player2LifeLeft < 0) || (dynamic_cast <Base*> (m_ppDisplayableObjects[1]))->isOver())
		{
			state = scoreState;
			initialized = 0;
			if (currentScore > highestScore)
				saveHighestScore();
		}
		else if (player1LifeLeft < 0)
		{
			m_ppDisplayableObjects[2] ->SetVisible(false);
		}
		else if (player2LifeLeft < 0)
		{
			m_ppDisplayableObjects[4] ->SetVisible(false);
		}

	}
}

/* load the level */
void MyProjectMain :: loadLevel(char* file)
{
	FILE *fp;
	char buff[1024];

	if ((fp = fopen(file, "r")) == NULL)
		return;

	int i = 0;
	char n;
	while(!feof(fp))
	{
		if (fscanf(fp, "%1023s", buff) > 0)
			for (int j = 0; (n = buff[j]) != NULL; j++)
				m.SetValue( j, i, n -'a' ); // Set value to each tile
		i++;
	}
}

/* load high score */
void MyProjectMain :: loadHighestScore ()
{
	FILE *fp;
	char buffer[512];
	if ((fp = fopen("highestScore.txt", "r")) == NULL)
		return;
	
	while (!feof(fp))
	{
		if (fscanf(fp, "%15s", buffer) > 0)
			highestScore = atoi(buffer);
	}

	fclose(fp);
}

/* save the score to the file */
void MyProjectMain :: saveHighestScore()
{
	FILE *fp = fopen ("highestScore.txt", "w");
	if (fp == NULL)
		return;
	fprintf(fp, "%d", currentScore);
	fclose(fp);
	newHighScore = true;
	highestScore = currentScore;
}

/* initialize the next stage, resize some parameters*/
void MyProjectMain::initialiseNextStage(bool isRestarted)
{
	//Reset the number of destroyed enemy tanks
	EnemyTank :: enemyTank1 = 0;
	EnemyTank :: enemyTank2 = 0;
	EnemyTank :: enemyTank3 = 0;
	EnemyTank :: enemyTank4 = 0;

	PlayerTank* tank1 = dynamic_cast <PlayerTank*> (m_ppDisplayableObjects[2]); 
	PlayerTank* tank2 = dynamic_cast <PlayerTank*> (m_ppDisplayableObjects[4]); 
	int tank1ID = tank1->getID();
	int tank2ID = tank2->getID();
	numberOfEnemyTankLeft = 20;
	InitialiseObjects();

	/* if restart reset these parameters */
	if (isRestarted)
	{
		player1LifeLeft = 3;
		player2LifeLeft = 3;
		accumulateScore = 0;
		enemy1Accumulate = 0;
		enemy2Accumulate = 0;
		enemy3Accumulate = 0;
		enemy4Accumulate = 0;
	}
	else
	{
		// change player tanks to normal state
		if (tank1ID == 1)
			(dynamic_cast <PlayerTank*> (m_ppDisplayableObjects[2]))->changTankState(0);
		if (tank2ID == 3)
			(dynamic_cast <PlayerTank*> (m_ppDisplayableObjects[4]))->changTankState(2);

		// Score of previous level will be accumulated to next nevel.
		accumulateScore = currentScore;
		enemy1Accumulate = enemy1;
		enemy2Accumulate = enemy2;
		enemy3Accumulate = enemy3;
		enemy4Accumulate = enemy4;
	}

	// if only one player, hide the other one
	if (playerNumber == 1)
	{
		dynamic_cast <PlayerTank*> (m_ppDisplayableObjects[4]) ->setInitial(0);
	}
}

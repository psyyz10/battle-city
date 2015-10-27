#ifndef BouncingBallMain_H
#define BouncingBallMain_H

#include "BaseEngine.h"

// Forward declarations of classes
// Says that these are classes, but not what the classes look like
// Doesn't matter, since I only use pointers to them, so compiler only
// cares when I de-reference the pointer.
class BouncingBall;
class BouncingBall1;
class BouncingBall2;

// This includes the class definition for the TileManager class,
// which I use
#include "TileManager.h"

// Class definition for BouncingBallMain
// Says that it subclasses a class called BaseEngine
// so we inherit a lot of functionality for this class
class BouncingBallMain :
	public BaseEngine
{
protected:
	// Three member variables, to store pointers to the three balls
	BouncingBall1* m_pBall1;
	BouncingBall2* m_pBall2;
	BouncingBall2* m_pBall3;

	// A member object. Object is created when the BouncingBallMain
	// is created
	TileManager m;

public:

	/**
	Constructor
	The : here refers to an initialisation list
	*/
	BouncingBallMain()
	: BaseEngine( 6 ) // Pass 6 to superclass constructor
	, m_pBall1(NULL)  // Initialise pointers to NULL
	, m_pBall2(NULL)
	, m_pBall3(NULL)
	{}

	// Do any setup of back buffer prior to locking the screen buffer
	// Do the drawing of the background in here and 
	// it'll be copied to the screen for you as needed
	virtual void SetupBackgroundBuffer();

	// Create the bouncing ball(s)
	int InitialiseObjects();

	// Draw any strings that you need on the screen
	void DrawStrings();

	// The game logic - move things and change the state if necessary.
	// Must call Redraw(true/false) if anything changes that shows on the screen.
	virtual void GameAction();

	// Mouse-down override
	void MouseDown( int iButton, int iX, int iY );

	// Handle key presses if necessary
	virtual void KeyDown(int iKeyCode);
};

#endif

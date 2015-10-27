#pragma once

#include "BaseEngine.h"
#include "TileManager.h"
#include "Demo4TileManager.h"

class Demo4Main :
	public BaseEngine
{
public:
	Demo4Main(void);
	~Demo4Main(void);

	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void DrawStrings();
	void GameAction();
	void MouseDown( int iButton, int iX, int iY );
	void KeyDown(int iKeyCode);

	// Get a reference to the current tile manager
	Demo4TileManager& GetTileManager() { return m_oTiles; }

private:
	Demo4TileManager m_oTiles;

public:
	// State number
	enum State { stateInit, stateMain, statePaused };

	void DrawScreen();
	void DrawChanges();

private:
	State m_state;
};


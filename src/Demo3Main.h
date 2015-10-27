#pragma once

#include "BaseEngine.h"
#include "TileManager.h"
#include "Demo3TileManager.h"


class Demo3Main :
	public BaseEngine
{
public:
	Demo3Main(void);
	~Demo3Main(void);

	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void DrawStrings();
	void GameAction();
	void MouseDown( int iButton, int iX, int iY );
	void KeyDown(int iKeyCode);
	void DrawChanges();
	// Get a reference to the current tile manager
	Demo3TileManager& GetTileManager() { return m_oTiles; }
private:
	Demo3TileManager m_oTiles;
};

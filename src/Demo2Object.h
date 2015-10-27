#pragma once
#include "displayableobject.h"

class Demo2Main;

class Demo2Object :
	public DisplayableObject
{
public:
	Demo2Object(Demo2Main* pEngine);
	~Demo2Object(void);

	void Draw();
	void DoUpdate( int iCurrentTime );

private:
	Demo2Main* m_pMainEngine;
};

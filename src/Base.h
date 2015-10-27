#ifndef BASE_H
#define BASE_H
#include "displayableobject.h"
#include "header.h"
#include "JPGImage.h"	
#include "MyProjectMain.h"

class Base :
	public DisplayableObject
{
public:
	Base(MyProjectMain* pEngine);
	~Base(void);
	bool isOver()
	{
		return over;
	}

	void Draw();

	void DoUpdate(int iCurrentTime);

private:
	ImageData im_Eagle, im_Die, im_Temp1, im_Temp2;
	bool shot;
	bool over;
};

#endif
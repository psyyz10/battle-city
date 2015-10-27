#include "header.h"

#include "templates.h"

// Needs one of the following #includes, to include the class definition
#include "BouncingBallMain.h"
#include "MyProjectMain.h"
#include "Demo2Main.h"
#include "Demo2aMain.h"
#include "Demo3Main.h"
#include "Demo4Main.h"

#define BASE_SCREEN_WIDTH 830
#define BASE_SCREEN_HEIGHT 620



int main(int argc, char *argv[])
{
	int iResult;

	// Needs just one of the two following lines:
	//BouncingBallMain oMain;
	MyProjectMain oMain;
	//Demo2Main oMain;
	//Demo2aMain oMain;
	//Demo3Main oMain;
	//Demo4Main oMain;
	//DemoAmain oMain;

	char buf[1024];
	sprintf( buf, "My Demonstration Program : Size %d x %d", BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT );
	iResult = oMain.Initialise( buf, BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, "Cornerstone Regular.ttf", 24 );
	iResult = oMain.MainLoop();
	oMain.Deinitialise();

	return iResult;
}

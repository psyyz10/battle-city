#include "header.h"

#include "Demo2aMain.h"

Demo2aMain::Demo2aMain()
: BaseEngine( 50 )
{
}

Demo2aMain::~Demo2aMain()
{
}

/* Fill the background - should be overridden to actually draw the correct thing. */
void Demo2aMain::SetupBackgroundBuffer()
{
	// Put any special code to call different render functions for different states here
	FillBackground( 0xff00ff );
}

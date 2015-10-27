#include "displayableobject.h"
#include "JPGImage.h"

class SelectionIcon :
	public DisplayableObject
{
public:
	SelectionIcon(BaseEngine* pEngine);
	~SelectionIcon(void);

	void Draw();
	void DoUpdate(int iCurrentTime );

private:
	ImageData im, icon;
};
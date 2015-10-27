#pragma once



void InitImage();

void DeinitImage();


class ImageData
{
public:
	ImageData()
		: m_iWidth(0), m_iHeight(0), m_aiPixels(NULL)
	{}

	~ImageData()
	{
		if ( m_aiPixels != NULL )
			delete[] m_aiPixels;
	}

	int GetWidth()  { return m_iWidth; }
	int GetHeight()  { return m_iHeight; }

	bool LoadImage( char* szFileName );

	bool IsLoaded() { return m_aiPixels != NULL; }

	void RenderImage( SDL_Surface* pTarget, 
		int iXSource, int iYSource, 
		int iXTarget, int iYTarget, 
		int iWidth, int iHeight );

	void RenderImageWithMask( SDL_Surface* pTarget, 
		int iXSource, int iYSource, 
		int iXTarget, int iYTarget, 
		int iWidth, int iHeight );

	void ShrinkFrom( ImageData* pSource, int iReductionMultiplier );

	void ResizeTo( ImageData* pSource, int iNewWidth, int iNewHeight, bool bJustSampleOnePixel );

	static void SetCropping( int iLeft, int iRight, int iTop, int iBottom )
	{
		g_iCropLeft = iLeft;
		g_iCropRight = iRight;
		g_iCropTop = iTop;
		g_iCropBottom = iBottom;
	}

	static void SetRotation( int iRotation ) { g_iRotation = iRotation; }

protected:
	int m_iWidth;
	int m_iHeight;
	unsigned int* m_aiPixels;

	static int g_iRotation;
	static int g_iCropLeft;
	static int g_iCropRight;
	static int g_iCropTop;
	static int g_iCropBottom;
};

class ImageSurface
{
public:
	ImageSurface()
		: m_pSurface(NULL)
	{}

	~ImageSurface()
	{
		if ( m_pSurface != NULL )
			SDL_FreeSurface( m_pSurface );
	}

	int GetWidth()  { return m_pSurface->w; }
	int GetHeight()  { return m_pSurface->h; }

	bool LoadImage( char* szFileName );

	void RenderImage( SDL_Surface* pTarget, 
		int iXSource, int iYSource, 
		int iXTarget, int iYTarget, 
		int iWidth, int iHeight );

protected:
	SDL_Surface* m_pSurface;
};

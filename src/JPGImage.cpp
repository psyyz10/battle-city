#include "header.h"

#include <SDL_image.h>

#include "JPGImage.h"


int ImageData::g_iCropLeft = 0;
int ImageData::g_iCropRight = 0;
int ImageData::g_iCropTop = 0;
int ImageData::g_iCropBottom = 0;
int ImageData::g_iRotation = 0;

#ifdef WIN32
	static void *jpeglib, *pnglib;
#endif

void InitImage()
{
#ifdef WIN32
	// PERF_IMPROVEMENT: Avoid SDL_Image to load/unload shared libs on every image
	// This also seems to fix a double load of the same file.
	jpeglib = SDL_LoadObject("jpeg.dll");	
	pnglib = SDL_LoadObject("libpng12-0.dll");
#endif
}

void DeinitImage()
{
#ifdef WIN32
	SDL_UnloadObject(pnglib);
	SDL_UnloadObject(jpeglib);
#endif
}

// Function to work out the X coordinate to retrieve a point from given a rotation and cropping
inline int GetXForRotationAndCrop( int iImageWidth, int iX, int iY, int iRotation, int iCropLeft, int iCropTop )
{
	switch( (iRotation+4)%4 )
	{
	default: return iX+iCropLeft;
	case 1: return iY + iCropTop;
	case 2: return iImageWidth - 1 - iX - iCropLeft;
	case 3: return iImageWidth - 1 - iY - iCropTop;
	}
}

// Function to work out the Y coordinate to retrieve a point from given a rotation and cropping
inline int GetYForRotationAndCrop( int iImageHeight, int iX, int iY, int iRotation, int iCropLeft, int iCropTop )
{
	switch( (iRotation+4)%4 )
	{
	default: return iY+iCropTop;
	case 1: return iImageHeight - 1 - iCropLeft - iX;
	case 2: return iImageHeight - 1 - iY - iCropTop;
	case 3: return iX + iCropLeft;
	}
}


bool ImageData::LoadImage( char* szFileName )
{
	char buf[128];

	// Free any current image data
	if ( m_aiPixels != NULL )
	{
		delete[] m_aiPixels;
		m_aiPixels = NULL;
	}

	SDL_Surface* imagesurface = IMG_Load( szFileName );
	if ( imagesurface != NULL )
	{
		{ // Make a 32 bit version
			SDL_Surface* newSurface = SDL_CreateRGBSurface (
						SDL_SWSURFACE, imagesurface->w, imagesurface->h, 32, 
						0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000 );
			SDL_BlitSurface( imagesurface, NULL, newSurface, NULL );

			SDL_FreeSurface( imagesurface );
			imagesurface = newSurface;
		}

		if ( ( g_iRotation % 2 ) == 1 )
		{
			m_iWidth = imagesurface->h - g_iCropTop - g_iCropBottom;
			m_iHeight = imagesurface->w - g_iCropLeft - g_iCropRight;
		}
		else
		{
			m_iWidth = imagesurface->w - g_iCropLeft - g_iCropRight;
			m_iHeight = imagesurface->h - g_iCropTop - g_iCropBottom;
		}

		// Allocate memory
		m_aiPixels = new unsigned int[ m_iWidth * m_iHeight ];

		int iIntsPerScreenRow = imagesurface->pitch/sizeof(unsigned int);

		for ( int iY = 0 ; iY < m_iHeight ; iY++ )
		{
			for ( int iX = 0 ; iX < m_iWidth ; iX++ )
			{
				// Calculate which pixel to pull from the image
/*				int x = iX+g_iCropLeft;
				int y = iY+g_iCropTop;
				switch( (g_iRotation+4)%4 )
				{
				case 1:
					x = iY + g_iCropTop;
					y = imagesurface->h - 1 - g_iCropLeft - iX;
					break;
				case 2:
					x = imagesurface->w - 1 - iX - g_iCropLeft;
					y = imagesurface->h - 1 - iY - g_iCropTop;
					break;
				case 3:
					x = imagesurface->w - 1 - iY - g_iCropTop;
					y = iX + g_iCropLeft;
					break;
				}

				m_aiPixels[ iY * m_iWidth + iX ] 
					= ( ((unsigned int *)imagesurface->pixels)[x + y * iIntsPerScreenRow] );
*/
				m_aiPixels[ iY * m_iWidth + iX ] 
					= ( ((unsigned int *)imagesurface->pixels)[GetXForRotationAndCrop(imagesurface->w, iX, iY, g_iRotation, g_iCropLeft, g_iCropTop )
							+ GetYForRotationAndCrop(imagesurface->h, iX, iY, g_iRotation, g_iCropLeft, g_iCropTop ) * iIntsPerScreenRow] );
			}
		}
		SDL_FreeSurface(imagesurface);
		return true;
	}
	return false;
}


// Create an image by shrinking another one by a factor of three
void ImageData::ShrinkFrom( ImageData* pSource, int iReductionMultiplier )
{
	// Free any current image data
	if ( m_aiPixels != NULL )
	{
		delete[] m_aiPixels;
		m_aiPixels = NULL;
	}

	m_iWidth = (pSource->m_iWidth)/iReductionMultiplier;
	m_iHeight = (pSource->m_iHeight)/iReductionMultiplier;
	m_aiPixels = new unsigned int[ m_iWidth * m_iHeight ];

	unsigned int iR, iG, iB, iA;
	unsigned int pixel;

	
	int iBrightnessFactor = (iReductionMultiplier * iReductionMultiplier);

	for ( int x = 0 ; x < m_iWidth ; x++ )
		for ( int y = 0 ; y < m_iHeight ; y++ )
		{
			iR = iG = iB = iA = 0;
			for ( int i = 0 ; i < iReductionMultiplier ; i++ )
				for ( int j = 0 ; j < iReductionMultiplier ; j++ )
				{
					pixel = pSource->m_aiPixels[ (y*iReductionMultiplier+j) * (pSource->m_iWidth) + (x*iReductionMultiplier+i) ];
					iA += ( 0xFF & ( pixel >> 24 ) );
					iR += ( 0xFF & ( pixel >> 16 ) );
					iG += ( 0xFF & ( pixel >> 8 ) );
					iB += ( 0xFF & pixel );
				}
			m_aiPixels[ y * m_iWidth + x ]  = //(((iA)&0xFF)<<24) +
					(((iR/iBrightnessFactor)&0xFF)<<16) 
					+ (((iG/iBrightnessFactor)&0xFF)<<8) 
					+ (((iB/iBrightnessFactor)&0xFF));
		}
}

// Create an image by shrinking another one by a factor of three
void ImageData::ResizeTo( ImageData* pSource, int iNewWidth, int iNewHeight, bool bJustSampleOnePixel )
{
	// Free any current image data
	if ( m_aiPixels != NULL )
	{
		delete[] m_aiPixels;
		m_aiPixels = NULL;
	}

	int iOldWidth = pSource->m_iWidth;
	int iOldHeight = pSource->m_iHeight;

	m_iWidth = iNewWidth;
	m_iHeight = iNewHeight;
	m_aiPixels = new unsigned int[ m_iWidth * m_iHeight ];

	double dR, dG, dB;
	unsigned int pixel;
	double dSampleX, dSampleY;
	int iSampleX, iSampleY;
	double dX[2], dY[2];

	for ( int x = 0 ; x < m_iWidth ; x++ )
		for ( int y = 0 ; y < m_iHeight ; y++ )
		{
			dSampleX = ((double)x * (double)iOldWidth) / (double)iNewWidth + 0.001;
			dSampleY = ((double)y * (double)iOldHeight) / (double)iNewHeight + 0.001;
			iSampleX = (int)dSampleX;
			iSampleY = (int)dSampleY;

			dX[1] = dSampleX - iSampleX;
			dX[0] = 1.0 - dX[1];
			dY[1] = dSampleY - iSampleY;
			dY[0] = 1.0 - dY[1];

			if ( bJustSampleOnePixel )
			{ // Just sample one of the pixels - not a good thing!
				dX[0] = dY[0] = 1.0;
				dX[1] = dY[1] = 0.0;
			}

			dR = dG = dB = 0.0;
			for ( int i = 0 ; i < 2 ; i++ )
				for ( int j = 0 ; j < 2 ; j++ )
				{
					if ( ((iSampleX+i) < iOldWidth) && ((iSampleY+j) < iOldHeight) )
					{
						pixel = pSource->m_aiPixels[ (iSampleY+j) * iOldWidth + (iSampleX+i) ];
						dR += ( ( 0xFF & ( pixel >> 16 ) ) * dX[i] * dY[j] );
						dG += ( ( 0xFF & ( pixel >> 8 ) ) * dX[i] * dY[j] );
						dB += ( ( 0xFF & pixel ) * dX[i] * dY[j] );
					}
				}
			m_aiPixels[ y * m_iWidth + x ] = 
					  (( ((int)(dR+0.5)) & 0xFF)<<16) 
					+ (( ((int)(dG+0.5)) & 0xFF)<<8) 
					+ (( ((int)(dB+0.5)) & 0xFF));
		}
}

void ImageData::RenderImage( SDL_Surface* pTarget, 
							int iXSource, int iYSource, 
							int iXTarget, int iYTarget, 
							int iWidth, int iHeight )
{
	if ( iXTarget < 0 )
	{ // Then trim
		iWidth += iXTarget;
		iXSource -= iXTarget;
		iXTarget = 0;
	}

	if ( (iXTarget+iWidth) >= pTarget->w )
	{ // Then trim
		iWidth = pTarget->w - iXTarget;
	}

	if ( iYTarget < 0 )
	{ // Then trim
		iHeight += iYTarget; // Decrease height
		iYSource -= iYTarget; // Increase start point
		iYTarget = 0;
	}

	if ( (iYTarget+iHeight) >= pTarget->h )
	{ // Then trim
		iHeight = pTarget->h - iYTarget;
	}

	int iXS, iYS = iYSource, iXT, iYT = iYTarget;
	int iIntsPerScreenRow = pTarget->pitch/sizeof(unsigned int);

	for ( int iYOffset = 0 ; iYOffset < iHeight ; iYOffset++ )
	{
		iXS = iXSource; 
		iXT = iXTarget;
		for ( int iXOffset = 0 ; iXOffset < iWidth ; iXOffset++ )
		{
			((unsigned int *)pTarget->pixels)[iXT + iYT * iIntsPerScreenRow] = m_aiPixels[ iYS * m_iWidth + iXS ];
			iXS++;
			iXT++;
		}
		iYS++; 
		iYT++;
	}
}

void ImageData::RenderImageWithMask( SDL_Surface* pTarget, 
							int iXSource, int iYSource, 
							int iXTarget, int iYTarget, 
							int iWidth, int iHeight )
{
	if ( iXTarget < 0 )
	{ // Then trim
		iWidth += iXTarget;
		iXSource -= iXTarget;
		iXTarget = 0;
	}

	if ( (iXTarget+iWidth) >= pTarget->w )
	{ // Then trim
		iWidth = pTarget->w - iXTarget;
	}

	if ( iYTarget < 0 )
	{ // Then trim
		iHeight += iYTarget; // Decrease height
		iYSource -= iYTarget; // Increase start point
		iYTarget = 0;
	}

	if ( (iYTarget+iHeight) >= pTarget->h )
	{ // Then trim
		iHeight = pTarget->h - iYTarget;
	}

	int iMask = m_aiPixels[ m_iHeight * m_iWidth -1 ];

	int iXS, iYS = iYSource, iXT, iYT = iYTarget;
	int iIntsPerScreenRow = pTarget->pitch/sizeof(unsigned int);

	for ( int iYOffset = 0 ; iYOffset < iHeight ; iYOffset++ )
	{
		iXS = iXSource; 
		iXT = iXTarget;
		for ( int iXOffset = 0 ; iXOffset < iWidth ; iXOffset++ )
		{
			if ( m_aiPixels[ iYS * m_iWidth + iXS ] != iMask )
				((unsigned int *)pTarget->pixels)[iXT + iYT * iIntsPerScreenRow] = m_aiPixels[ iYS * m_iWidth + iXS ];
			iXS++;
			iXT++;
		}
		iYS++; 
		iYT++;
	}
}

bool ImageSurface::LoadImage( char* szFileName )
{
	m_pSurface = IMG_Load( szFileName );
	return m_pSurface != NULL;
}


void ImageSurface::RenderImage( SDL_Surface* pTarget, 
							int iXSource, int iYSource, 
							int iXTarget, int iYTarget, 
							int iWidth, int iHeight )
{
	SDL_Rect rectS = { (Sint16) iXSource, (Sint16) iYSource, (Uint16) iWidth, (Uint16) iHeight };
	SDL_Rect rectD = { (Sint16) iXTarget, (Sint16) iYTarget, (Uint16) iWidth, (Uint16) iHeight };

	SDL_BlitSurface( m_pSurface, &rectS, pTarget, &rectD );
}

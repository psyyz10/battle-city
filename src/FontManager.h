#pragma once

#include <SDL_TTF.h>

class Font
{
public:
	Font(TTF_Font* pFont, char* szFontName, int iSize )
		: m_pFont(pFont)
		, m_iFontSize(iSize)
	{
		m_szFontName = new char[ strlen(szFontName)+1 ];
		strcpy( m_szFontName, szFontName );
	}

	~Font()
	{
		if ( m_pFont != NULL )
		{
			printf( "Free font: %d point %s\n", m_iFontSize, m_szFontName );
			TTF_CloseFont( m_pFont );
		}
		if ( m_szFontName != NULL )
		{
			delete[] m_szFontName;
		}
	}

	TTF_Font* GetFont() { return m_pFont; }

	// Allow only font manager to get to the private bits
	friend class FontManager;

	const char* GetName() { return m_szFontName; }
	int GetSize() { return m_iFontSize; }

protected:
	TTF_Font* m_pFont;
	char* m_szFontName;
	int m_iFontSize;
};


class FontManager
{
public:
	FontManager(void);

	~FontManager(void);

	Font* GetFont( char* szFontName, int iFontSize );

	/* Load all of the fonts which have been selected */
	void LoadFonts();

protected:
	int m_iFontCount;
	int m_iArraySize;
	Font** m_pArrayFonts;
	bool m_bInitialised;
};


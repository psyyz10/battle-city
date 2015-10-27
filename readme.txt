This zip contains:
Screenshot of the working, modified program
This file telling you the code changes.
Source code files where I already made the changes, in case you don't want to read this. In that case just take the JPGImage files.

I did not include the png file since I do not have distribution rights. 
You can get the example png file which I used from here:
http://www.google.co.uk/imgres?imgurl=http://tuxpaint.org/stamps/stamps/animals/birds/cartoon/tux.png&imgrefurl=http://tuxpaint.org/stamps/&usg=__2xJ7IGfQzJgjXsdUsXkHqjLRKv8=&h=479&w=400&sz=41&hl=en&start=0&zoom=1&tbnid=o2pbPrsh9Ou2nM:&tbnh=152&tbnw=127&ei=26aJTe6dI4O1hAf52fHJDQ&prev=/images%3Fq%3Dpng%2Bimage%26um%3D1%26hl%3Den%26client%3Dfirefox-a%26sa%3DN%26rls%3Dorg.mozilla:en-GB:official%26channel%3Ds%26biw%3D1027%26bih%3D939%26tbs%3Disch:1&um=1&itbs=1&iact=hc&vpx=130&vpy=406&dur=144&hovh=246&hovw=205&tx=111&ty=105&oei=26aJTe6dI4O1hAf52fHJDQ&page=1&ndsp=26&ved=1t:429,r:11,s:0
do a "save image as" or you can use any png file.
Note: I recommend using a format such as phg, since it won't work well with a lossy format such as jpg.

==========

Since I had a few requests for sprite help here is some sample code from a modified BouncingBallMain.
I have added a screenshot of the finished version to this file.
You can feel free to take this code and use it or to ignore it, as you wish.

Firstly, it shows you how you can shrink an image after loading it, if you wish.
Warning: Doing this will merge adjacent colours so the masking discussed below may not work on the edges of the image.
You load the image as it is, then create another image by shrinking the first one by a specified multiplier.

	// Draw an image loaded from a file.
	ImageData im, im2;
	im2.LoadImage( "tux.png" );
	im.ShrinkFrom( &im2, 5 );

You can also resize an image, but the effects are not so good as when just shrinking by an integer factor.

==============

Secondly, I was asked about not drawing the entire background.
There is no current function to do this but it is easy to add by copying and pasting this code into your JPGImage.cpp and .h files.

Firstly, calling it:
I changed the code in my BouncingBallMain to this, just changing the function name which is called:

	// Note: image loaded only once, above, and now we will draw it nine times
	for ( int i = 0 ; i < 3 ; i++ )
		for ( int j = 0 ; j < 3 ; j++ )
			im.RenderImageWithMask( this->GetBackground(), 
					0, 0, 
					i*100, j*100 + 300, 
					im.GetWidth(), im.GetHeight() );

I then added the declaration of the function within the class ImageData in JPGImage.h
	void RenderImageWithMask( SDL_Surface* pTarget, 
		int iXSource, int iYSource, 
		int iXTarget, int iYTarget, 
		int iWidth, int iHeight );

Finally, I added the implementation to JPGImage.cpp.
This is exactly the same as RenderImage() but the first thing is does is selects a colour NOT to draw.
Every pixel which is NOT of this colour will be copied from the image, but all pixels which ARE of this colour will be ignored.

The line:
	int iMask = m_aiPixels[ m_iHeight * m_iWidth -1 ];
selects the pixel not to draw and chooses the bottom right hand pixel.
You could choose any pixel, or pass the colour into the function.

Next I add an if statement before the copying of the pixel, saying only copy it if it is not the mask colour:
if ( m_aiPixels[ iYS * m_iWidth + iXS ] != iMask )
	((unsigned int *)pTarget->pixels)[iXT + iYT * iIntsPerScreenRow] = m_aiPixels[ iYS * m_iWidth + iXS ];
i.e. copy the pixel if and only if the colour is not the mask colour that was stored earlier.

Two simple line changes and it all works.

Note that you MAY change the framework classes (like this), but you need to make sure that you tell us what you changed in your readme file if you do.

Final function:
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





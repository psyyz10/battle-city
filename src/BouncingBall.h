#ifndef BouncingBall_H
#define BouncingBall_H

#include "DisplayableObject.h"
#include "MovementPosition.h"

#include "BouncingBallMain.h"

class BaseEngine;

class BouncingBall :
	public DisplayableObject
{
public:
	BouncingBall(BouncingBallMain* pEngine, int iID, 
		int iDrawType, int iSize, int iColour,
		char* szLabel, int iXLabelOffset, int iYLabelOffset );

	virtual ~BouncingBall(void);

	void Draw();

	void DoUpdate( int iCurrentTime );

private:
	/** Pointer to the main engine object */
	BouncingBallMain* m_pEngine;

	// Unique id for object, passed to engine to identify it
	int m_iID;

	// Type of thing to draw
	int m_iDrawType;

	// Size of thing to draw
	int m_iSize;

	// Colour index to draw with
	int m_iColour;

	// Label to apply
	char* m_szLabel;

	// Label offset in pixels
	int m_iXLabelOffset;
	int m_iYLabelOffset;
};

class TileManager;

class BouncingBall1 :
	public BouncingBall
{
public:
	BouncingBall1(BouncingBallMain* pEngine, int iID, 
		int iDrawType, int iSize, int iColour,
		char* szLabel, int iXLabelOffset, int iYLabelOffset,
		TileManager* pTileManager );

	void SetMovement( int iStartTime, int iEndTime, int iCurrentTime,
				int iStartX, int iStartY, int iEndX, int iEndY );

	void DoUpdate( int iCurrentTime );

protected:
	/** Movement position calculator - give it start and end position and times 
	and it works out current position for the current time. 
	Notice also the MyMovementPosition class. */
	MovementPosition m_oMovement;

	// Pointer to the tile manager - we are going to use this!
	TileManager* m_pTileManager;
};

class BouncingBall2 :
	public BouncingBall
{
public:
	BouncingBall2(BouncingBallMain* pEngine, int iID, 
		int iDrawType, int iSize, int iColour,
		char* szLabel, int iXLabelOffset, int iYLabelOffset );

	void SetPosition( double dX, double dY );

	void SetSpeed( double dSX, double dSY );

	void DoUpdate( int iCurrentTime );

protected:
	double m_dX;
	double m_dY;
	double m_dSX;
	double m_dSY;

};


#endif

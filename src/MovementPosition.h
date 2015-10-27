#ifndef MOVEMENT_POSITION_H
#define MOVEMENT_POSITION_H

#include "templates.h"

/** Class to maintain and calculate the current movement and position */
class MovementPosition
{
protected:
	/** Start time of movement */
	int m_iStartTime;
	/** End time of movement */
	int m_iEndTime;
	/** Start X coordinate of movement */
	int m_iStartX;
	/** Start Y coordinate of movement */
	int m_iStartY;
	/** End X coordinate of movement */
	int m_iEndX;
	/** End Y coordinate of movement */
	int m_iEndY;

	/** Calculated current X coordinate for current time */
	int m_iCurrentX;
	/** Calculated current Y coordinate for current time */
	int m_iCurrentY;


public:
	inline void Reverse()
	{
		Swap(m_iStartX,m_iEndX);
		Swap(m_iStartY,m_iEndY);
		int iNewEndTime = m_iEndTime * 2 - m_iStartTime;
		m_iStartTime = m_iEndTime;
		m_iEndTime = iNewEndTime;
	}

	/** Constructor */
	MovementPosition()
		: m_iStartTime(0), m_iEndTime(0)
		, m_iStartX(0), m_iStartY(0)
		, m_iEndX(0), m_iEndY(0)
		, m_iCurrentX(0), m_iCurrentY(0)
	{
	}

	/** Set up movement - start and finish coordinates and time */
	inline void Setup( int iXStart, int iYStart, int iXEnd, int iYEnd, int iStartTime, int iEndTime )
	{
		m_iStartX = iXStart;
		m_iStartY = iYStart;
		m_iEndX = iXEnd;
		m_iEndY = iYEnd;
		m_iStartTime = iStartTime;
		m_iEndTime = iEndTime;
		// Initially put position at start
		m_iCurrentX = m_iStartX;
		m_iCurrentY = m_iStartY;
	}

	/** Calculate current position, for the current time */
	inline void Calculate( int iCurrentTime )
	{
		// At start position until start time
		if ( iCurrentTime <= m_iStartTime )
		{
			m_iCurrentX = m_iStartX;
			m_iCurrentY = m_iStartY;
			return;
		}
		// At end position after end time
		if ( iCurrentTime >= m_iEndTime )
		{
			m_iCurrentX = m_iEndX;
			m_iCurrentY = m_iEndY;
			return;
		}
		// Calculate the current position while mid-movement
		m_iCurrentX = m_iStartX 
			+ ((iCurrentTime-m_iStartTime) * (m_iEndX-m_iStartX))/(m_iEndTime-m_iStartTime);
		m_iCurrentY = m_iStartY 
			+ ((iCurrentTime-m_iStartTime) * (m_iEndY-m_iStartY))/(m_iEndTime-m_iStartTime);
	}

	/** Get calculated X coordinate */
	inline int GetX() { return m_iCurrentX; }

	/** Get calculated Y coordinate */
	inline int GetY() { return m_iCurrentY; }

	/** Check whether movement has ended */
	inline bool HasMovementFinished( int iCurrentTime ) { return iCurrentTime >= m_iEndTime; }
};

#endif

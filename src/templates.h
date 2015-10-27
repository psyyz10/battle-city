#pragma once

// Grow an array
// Example usage:
//	if ( (m_iFontCount+1) > m_iArraySize )
//		m_pArrayFonts = GrowArray( m_pArrayFonts, m_iArraySize, 10 );

template <class T> 
T* GrowArray( T* pOldArray, int& iSize, int iGrowBy )
{
	T* pNewArray = new T[iSize+iGrowBy];
	if ( pOldArray > 0 )
	{
		for ( int i = 0 ; i < iSize ; i++ )
		{
			pNewArray[i] = pOldArray[i];
		}
		delete[] pOldArray;
	}
	iSize += iGrowBy;
	return pNewArray;
}

// Template function to swap two values
template <typename T>
inline void Swap( T& v1, T& v2 )
{
	T t = v1;
	v1 = v2;
	v2 = t;
}


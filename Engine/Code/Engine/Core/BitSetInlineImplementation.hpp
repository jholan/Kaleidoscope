#include "Engine/Core/BitSet.hpp"



// -----------------------------------------------------------------
// AreBitsSet
// -----------------------------------------------------------------
inline bool AreBitsSet(uchar bitFlags8, uchar flagsToCheck)
{
	bool isSet = (bitFlags8 & flagsToCheck) == flagsToCheck;
	return isSet;
}


inline bool AreBitsSet(ushort bitFlags16, ushort flagsToCheck)
{
	bool isSet = (bitFlags16 & flagsToCheck) == flagsToCheck;
	return isSet;
}


inline bool AreBitsSet(uint bitFlags32, uint flagsToCheck)
{
	bool isSet = (bitFlags32 & flagsToCheck) == flagsToCheck;
	return isSet;
}


inline bool AreBitsSet(ulonglong bitFlags64, ulonglong flagsToCheck)
{
	bool isSet = (bitFlags64 & flagsToCheck) == flagsToCheck;
	return isSet;
}



// -----------------------------------------------------------------
// SetBits
// -----------------------------------------------------------------
inline void SetBits(uchar& bitFlags8, uchar flagsToSet)
{
	bitFlags8 = bitFlags8 | flagsToSet;
}


inline void SetBits(ushort& bitFlags16, ushort flagsToSet)
{
	bitFlags16 = bitFlags16 | flagsToSet;
}


inline void SetBits(uint& bitFlags32, uint flagsToSet)
{
	bitFlags32 = bitFlags32 | flagsToSet;
}


inline void SetBits(ulonglong& bitFlags64, ulonglong flagsToSet)
{
	bitFlags64 = bitFlags64 | flagsToSet;
}



// -----------------------------------------------------------------
// ClearBits
// -----------------------------------------------------------------
inline void ClearBits(uchar& bitFlags8, uchar flagToClear)
{
	bitFlags8 = bitFlags8 & (~flagToClear);
}


inline void ClearBits(ushort& bitFlags16, ushort flagToClear)
{
	bitFlags16 = bitFlags16 & (~flagToClear);
}


inline void ClearBits(uint& bitFlags32, uint flagToClear)
{
	bitFlags32 = bitFlags32 & (~flagToClear);
}


inline void ClearBits(ulonglong& bitFlags64, ulonglong flagToClear)
{
	bitFlags64 = bitFlags64 & (~flagToClear);
}
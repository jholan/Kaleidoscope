#pragma once

#include "Engine/Core/Types.hpp"



bool AreBitsSet(uchar bitFlags8, uchar flagsToCheck);
bool AreBitsSet(ushort bitFlags16, ushort flagsToCheck);
bool AreBitsSet(uint bitFlags32, uint flagsToCheck);
bool AreBitsSet(ulonglong bitFlags64, ulonglong flagsToCheck);


void SetBits(uchar& bitFlags8, uchar flagsToSet);
void SetBits(ushort& bitFlags16, ushort flagsToSet);
void SetBits(uint& bitFlags32, uint flagsToSet);
void SetBits(ulonglong& bitFlags64, ulonglong flagsToSet);


void ClearBits(uchar& bitFlags8, uchar flagToClear);
void ClearBits(ushort& bitFlags8, ushort flagToClear);
void ClearBits(uint& bitFlags32, uint flagToClear);
void ClearBits(ulonglong& bitFlags64, ulonglong flagToClear);




#include "Engine/Core/BitSetInlineImplementation.hpp"
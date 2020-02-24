#include "kbase.h"

#ifndef FADE_H
#define FADE_H

/*	--	LUTs	--	*/
extern u16 lu_fade[0x10]; // LUT for fillp fading

/*	--	inlines	--	*/
INLINE u16 lu_fade_lerp(u32 i)
{ return lu_fade[(i&0xFFFF)>>12]; }

#endif

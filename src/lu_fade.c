#include "lu_fade.h"

const u16 fade_p[0x10] = // LUT for fillp fading.
{
	0x8000,0x8020,0xA020,0xA0A0,
	0xA4A0,0xA5A0,0xA5A4,0xA5A5,
	0xADA5,0xAFA5,0xAFAD,0xAFAF,
	0xEFAF,0xFFAF,0xFFEF,0xFFFF
};

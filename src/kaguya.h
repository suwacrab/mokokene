#include "kbase.h"
#include "keine.h"
#include "mokou.h"
#include "kosuzu.h"

#include "player.h"

#ifndef KAGUYA_H
#define KAGUYA_H

/*	--	structs	--	*/
typedef struct
{
	// window vars
	keine *kami;
	mokou *fuji;
	// game vars
	player *p1;
	// asset vars
	mokou **img_bank;
	kosuzu **fnt_bank;
} kaguya;

/*	--	main functions	--	*/
void kaguya_init(kaguya *hime,u32 w,u32 h,char *caption);

/*	--	load functions	--	*/
mokou *kaguya_loadimg(kaguya *hime,u32 index,char *fname);
kosuzu *kaguya_loadfont(kaguya *hime,u32 index,char *fname,u32 w,u32 h);

#endif

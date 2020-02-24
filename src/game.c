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
	uint32_t img_count;
	mokou *img_bank;
	uint32_t fnt_count;
	kosuzu *fnt_bank;
} kaguya;

/*	--	functions	--	*/
void kaguya_init_main(u32 w,u32 h,char *caption);

#endif

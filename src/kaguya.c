#include "kaguya.h"

/*	--	main functions	--	*/
void kaguya_init(kaguya *hime,u32 w,u32 h,char *caption)
{
	// vars
	keine *kami = NULL;
	mokou *fuji = NULL;
	mokou **img_bank = NULL;
	kosuzu **fnt_bank = NULL;
	player *p1 = NULL;
	// mokokene init
	kami = malloc(sizeof(keine));
	fuji = malloc(sizeof(keine));
	keine_init(kami,caption,NULL,w,h);
	mokou_init(fuji,w,h);
	// palette init
	RGBA32* famipal = keine_loadhexpal("pals/famicube.hex",0x40);
	keine_initpal(kami,famipal,0x40);
	free(famipal);
	// image init
	img_bank = malloc(sizeof(mokou*)*0x100);
	fnt_bank = malloc(sizeof(kosuzu*)*0x100);
	for(u32 i=0; i<0x80; i++)
	{
		img_bank[i] = NULL;
		fnt_bank[i] = NULL;
	}
	// player init
	p1 = malloc(sizeof(player));
	// final setting
	hime->kami = kami;
	hime->fuji = fuji;
	hime->img_bank = img_bank;
	hime->fnt_bank = fnt_bank;
	hime->p1 = p1;
}

/*	--	load functions	--	*/
mokou *kaguya_loadimg(kaguya *hime,u32 index,char *fname)
{
	// vars
	mokou **img_bank = hime->img_bank;
	img_bank[index] = malloc(sizeof(mokou));
	mokou *cur_img = img_bank[index];
	// loadin
	mokou_loadimg(cur_img,hime->kami->mainfb,fname);
	return cur_img;
}

kosuzu *kaguya_loadfont(kaguya *hime,u32 index,char *fname,u32 w,u32 h)
{
	// vars
	kosuzu **fnt_bank = hime->fnt_bank;
	fnt_bank[index] = malloc(sizeof(kosuzu));
	kosuzu *cur_fnt = fnt_bank[index];
	// loadin
	kosuzu_init(cur_fnt,hime->kami->mainfb,fname,w,h);
	return cur_fnt;
}

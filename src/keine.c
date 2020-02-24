#include "keine.h"


/*	--	init funcs	--	*/
void keine_init(keine *kami,char *caption,char *icon,u32 w,u32 h)
{
	// initializing SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{ printf("couldn't init sdl... (%s)\n",SDL_GetError()); }
	IMG_Init(IMG_INIT_PNG);
	// initializing surfaces
	s32 window_flags = SDL_SWSURFACE | SDL_HWPALETTE;
	kami->window = SDL_SetVideoMode(w,h,8,window_flags);
	kami->mainfb = SDL_CreateRGBSurface(0,w,h,8, 0,0,0,0);
	kami->w = w; kami->h = h;
	SDL_WM_SetCaption(caption,icon);
	// initializing palettes
	size_t pal_size = sizeof(SDL_Color)*0x100;
	kami->palette = malloc(pal_size);
	// initializing misc
	kami->framerate = 60;
	kami->do_quit = false;
}

void keine_initpal(keine *kami,RGBA32 *pal,u32 pallen)
{
	s32 palflags = SDL_LOGPAL;
	SDL_SetPalette(kami->window,palflags,(SDL_Color*)pal,0,pallen);
	SDL_SetPalette(kami->mainfb,palflags,(SDL_Color*)pal,0,pallen);
}

/*	--	load funcs	--	*/
RGBA32 *keine_loadhexpal(char *fname,u32 pallen)
{
	// init
	RGBA32 *pal = calloc(pallen,sizeof(RGBA32));
	// loading
	FILE *palfile = fopen(fname,"r");
	for(u32 c=0; c<pallen; c++)
	{
		u32 clr_int;
		fscanf(palfile,"%x\n",&clr_int);
		pal[c].r = (clr_int)>>16;
		pal[c].g = (clr_int>>8)&0xFF;
		pal[c].b = (clr_int)&0xFF;
	}
	fclose(palfile);
	// returnin
	return pal;
}

/*	--	blit funcs	--	*/
void keine_mokou(keine *kami,mokou *fuji)
{
	// copying moko to keine
	u32 x,y;
	SDL_Rect copyrect = { 0,0,1,1 };
	for(y = 0; y < fuji->h; y++)
	{
		for(x = 0; x < fuji->w; x++)
		{
			copyrect.x = x; copyrect.y = y;
			u32 px = mokou_pget(fuji,x,y);
			SDL_FillRect(kami->mainfb,&copyrect,px);
		}
	}
	// blitting keine to window
	SDL_BlitSurface(kami->mainfb,NULL,kami->window,NULL);
	SDL_Flip(kami->window);
	// waiting
	SDL_Delay( SDL_SECOND/kami->framerate );
	kami->time++;
}

/*	--	event funcs	--	*/
void keine_checkquit(keine *kami)
{
	bool quit = false;
	SDL_Event *evnt = &kami->inpevnt;
	if(evnt->type == SDL_QUIT) quit = true;
	if(evnt->type == SDL_KEYDOWN)
		if(evnt->key.keysym.sym == SDLK_ESCAPE) quit = true;
	kami->do_quit = quit;
}

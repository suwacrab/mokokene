#include "kbase.h"
#include "mokou.h"

/*	--	main funcs	--	*/
void mokou_init(mokou *fujiwara,u32 w,u32 h) // init empty framebuffer
{
	fujiwara->w = w;
	fujiwara->h = h;
	fujiwara->fillp = 0xFFFF;
	size_t fb_size = sizeof(u8)*(w*h);
	fujiwara->fb = malloc(fb_size);
}
void mokou_free(mokou *fuji) // free framebuffer
{ free(fuji->fb); fuji->fb = NULL; }
void mokou_clear(mokou *fuji,u32 pix) // clear framebuffer
{ memset(fuji->fb,pix&0xFF,sizeof(u8)*(fuji->w*fuji->h)); }

/*	--	loading funcs	--	*/
void mokou_loadimg(mokou *fuji,SDL_Surface *sdl_fb,char *fname)
{
	// loading, convertin
	SDL_Surface *fimg = NULL;
	fimg = IMG_Load(fname);
	if(fimg == NULL)
	{ printf("couldn't load image '%s': %s\n",fname,IMG_GetError()); }
	u32 w = fimg->w;
	u32 h = fimg->h;
	fimg = SDL_ConvertSurface(fimg,sdl_fb->format,0);
	// copying, freeing
	mokou_init(fuji,w,h); // fuji framebuffer setup
	memcpy(fuji->fb,fimg->pixels,sizeof(pix8)*(w*h)); // image copyin
	SDL_FreeSurface(fimg);
}

/*	--	pixel funcs	--	*/
pix8 *mokou_pread(mokou *fuji,u32 x,u32 y)
{	return fuji->fb + (x+(y*fuji->w)); }
pix8 mokou_pget(mokou *fuji,u32 x,u32 y)
{ return *mokou_pread(fuji,x,y); }
void mokou_pset(mokou *fuji,u32 x,u32 y,u8 pix)
{
	u32 ind = (x&3)+((y&3)*4);
	u32 pat_pix = (fuji->fillp>>ind)&1;
	if((pix!=0) && in_range(x,0,fuji->w-1) && in_range(y,0,fuji->h-1))
		if(pat_pix) (*mokou_pread(fuji,x,y)) = pix;
}

/*	--	fill funcs	--	*/
void mokou_rect(mokou *fuji,s32 x,s32 y,s32 w,s32 h,u32 pix)
{
	for(s32 ly=y; ly<(y+h); ly++)
		for(s32 lx=x; lx<(x+w); lx++)
			mokou_pset(fuji,lx,ly,pix);
}
void mokou_trifilltop(mokou *fuji,VEC2 *v1,VEC2 *v2,VEC2 *v3,pix8 c);

void mokou_trifillbot(mokou *fuji,VEC2 *v1,VEC2 *v2,VEC2 *v3,pix8 c)
{
	float inv1 = (float)(v2->x-v1->x) / (float)(v2->y-v1->y);
	float inv2 = (float)(v3->x-v1->x) / (float)(v3->y-v1->y);
	printf("%f %f\n",inv1,inv2);
	float x1 = (float)(v1->x);
	float x2 = (float)(v1->x);

	for(s32 scany = v1->y; scany<=v2->y; scany++)
	{
		// draw line from x1 to x2
		s32 inc = 1;
		s32 start = (s32)x1;
		s32 end = (s32)x2;
		if(x1 > x2) {inc = -1; start = (s32)x2; end = (s32)x1; }
		for(s32 x = start; x!=end; x += inc)
		{ mokou_pset(fuji,x,scany,c); }
		if(x1 > x2) { printf("? (%f,%f)\n",x1,x2); exit(-1); }
		x1 += inv1;
		x2 += inv2;
	}
}

void mokou_trifill(mokou *fuji,VEC2 *v1,VEC2 *v2,VEC2 *v3,pix8 c);

/*	--	img funcs	--	*/
void mokou_blit(mokou *src,SDL_Rect *srcrect,mokou *dst,s32 dx,s32 dy)
{
	u32 x,y,w,h;
	SDL_Rect blitrect = { 0,0,src->w,src->h };
	if(srcrect == NULL) srcrect = &blitrect;
	x = srcrect->x; y = srcrect->y;
	w = srcrect->w; h = srcrect->h;

	for(s32 oy=0; oy<(s32)h; oy++)
	{
		s32 ly = oy+dy;
		for(s32 ox=0; ox<(s32)w; ox++)
		{
			s32 lx = ox+dx;
			mokou_pset(dst,lx,ly,mokou_pget(src,x+ox,y+oy));
			// if lx is out of dst or ox is out of src's range, exit.
			//if((lx>dst->w) || (ox>src->w)) break;
		}
		//if((ly>dst->h) || (oy>src->h)) break;
	}
}



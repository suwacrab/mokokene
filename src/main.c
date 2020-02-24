/* basic shmup
	* TODO: get movement system before 16:00.
	* TODO: get shooting done before 18:00.
*/

#include "kbase.h"
#include "kaguya.h"
#include "mokou.h"
#include "keine.h"
#include "kosuzu.h"
#include "player.h"

// standard1 is 320x240
// standard2 is 256x192
// standard3 is 160x144
// widescreen1 is 480x270
// widescreen2 is 424x240
// widescreen3 is 384x216
#define WIDTH (114)
#define HEIGHT (160)

// eiyashou team
kaguya *hime = NULL;
mokou *fuji = NULL;
keine *kami = NULL;

// img vars
typedef struct { char *fname;mokou *img; } mokou_img;
mokou_img img_bank[] = // array of images
{
	{ "gfx/testtile.png",NULL },
	{ NULL,NULL }
};
kosuzu font_bank[] = // array of fonts
{
	{ 4,6,NULL,"gfx/borefont.png" },
	{ 8,8,NULL,"gfx/bobofont.png" },
	{ 0,0,NULL,NULL }
};
kosuzu *borefont = &font_bank[0];
kosuzu *bobofont = &font_bank[1];
// game vars
player *plrs = NULL;
player *p1 = NULL;
// misc vars
u32 revs = 0; // revision number
const u16 fade_p[0x10] = // LUT for fillp fading.
{
	0x8000,0x8020,0xA020,0xA0A0,
	0xA4A0,0xA5A0,0xA5A4,0xA5A5,
	0xADA5,0xAFA5,0xAFAD,0xAFAF,
	0xEFAF,0xFFAF,0xFFEF,0xFFFF
};

// funcs
void init();

void load_imgs();
void load_font();

void update();
void draw();

// main function
int main()
{
	// init
	init_kene();
	init_game();

	// main loop
	while( !(kami->do_quit) )
	{
		// updating
		update();
		// drawing
		draw();
		// final blit
		keine_mokou(kami,fuji);
	}
	// exit
	return 0;
}

void init_kene()
{
	// main mokokene setup
	kami = malloc(sizeof(keine));
	fuji = malloc(sizeof(mokou));
	keine_init(kami,"mokokene engine",NULL,WIDTH,HEIGHT);
	mokou_init(fuji,WIDTH,HEIGHT);
	// palette copying
	RGBA32 *famipal = keine_loadhexpal("pals/famicube.hex",0x40);
	keine_initpal(kami,famipal,0x40);
	free(famipal);
	// image/font loading
	load_imgs();
	load_font();
}

void init_game()
{
	// player init
	plrs = malloc(sizeof(player)*4);
	for(u32 i=0; i<4; i++)
	{
		player_init(&plrs[i],kami,fuji); 
	}
	p1 = &plrs[0];
}

void load_imgs()
{
	for(u32 imgid = 0; img_bank[imgid].fname != NULL; imgid++)
	{
		mokou_img *curimg = &img_bank[imgid]; // the current image struct
		char *fname = curimg->fname;
		curimg->img = malloc(sizeof(mokou)); // mallocate it's image...
		mokou_loadimg(curimg->img,kami->mainfb,fname); // then load using keine's fb.
		u32 w = curimg->img->w;
		u32 h = curimg->img->h;
		printf("loaded img '%s'! [SIZE: %d,%d] [ID: %02X]\n",fname,w,h,imgid);
	}
}
void load_font()
{
	for(u32 fntid = 0;font_bank[fntid].fname != NULL; fntid++)
	{
		kosuzu *curfont = &font_bank[fntid]; // current font struct
		char *fname = curfont->fname;
		u32 w,h;
		w = curfont->w; h = curfont->h;
		kosuzu_init(curfont,kami->mainfb,fname,w,h);
		printf("loaded font '%s'! [SIZE: %d,%d] [ID: %02X]\n",fname,w,h,fntid);
	}
}
void update()
{
	// main update
	player_updt(p1);
}

void draw()
{
	// clearing
	fuji->fillp = 0xFFFF;
	mokou_clear(fuji,7);
	// main drawin
	player_draw(p1);
}

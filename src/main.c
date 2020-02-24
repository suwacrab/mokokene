/* basic shmup
	* suwacrab 2020-02-22
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
mokou **img_bank = NULL; // LUT for images
kosuzu **fnt_bank = NULL; // LUT for fonts.
kosuzu *borefont = NULL; // basic font
kosuzu *bobofont = NULL;
// game vars
player *p1 = NULL;
// misc vars
const u16 fade_p[0x10] = // LUT for fillp fading.
{
	0x8000,0x8020,0xA020,0xA0A0,
	0xA4A0,0xA5A0,0xA5A4,0xA5A5,
	0xADA5,0xAFA5,0xAFAD,0xAFAF,
	0xEFAF,0xFFAF,0xFFEF,0xFFFF
};

// funcs
void init_eys();
void init_asset();

void update();
void draw();

// main function
int main()
{
	// init
	init_eys();
	init_asset();

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

void init_eys()
{
	// main init
	hime = malloc(sizeof(kaguya));
	kaguya_init(hime,WIDTH,HEIGHT,"huh?");
	kami = hime->kami;
	fuji = hime->fuji;
}

void init_asset()
{
	// img loading
	kaguya_loadimg(hime,0,"gfx/testtile.png");
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
	// hope this works
}

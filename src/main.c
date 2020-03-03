/* basic shmup
	* suwacrab 2020-02-22
*/

#include "kbase.h"
#include "kaguya.h"
#include "player.h"

#include "fade.h"

// standard1 is 320x240
// standard2 is 256x192
// standard3 is 160x144
// widescreen1 is 480x270
// widescreen2 is 424x240
// widescreen3 is 384x216
#define WIDTH (256)
#define HEIGHT (256)

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
	printf("all set!\n");
	// main loop
	while( !(kami->do_quit) )
	{
		// updating
		update();
		// drawin
		draw();
		// trifillin
		fuji->fillp = lu_fade[0xF>>1];
		mokou_rect(fuji,0,0,32,32,1);
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
	// eiyashou team
	kami = hime->kami;
	fuji = hime->fuji;
	p1 = hime->p1;
}

void init_asset()
{
	// img loading
	kaguya_loadimg(hime,0,"gfx/testtile.png");
	kaguya_loadimg(hime,1,"gfx/player-proto.png");
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

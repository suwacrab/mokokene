#include "player.h"

/*	--	main functions	--	*/
void player_init(player *plr,keine *kami,mokou *fuji)
{
	// initializin
	plr->hp = 3;
	vec2_set(&plr->pos,0,0);
	vec2_set(&plr->dir,0,0);
	plr->last_shotframe = 0;
	
	plr->kami = kami;
	plr->fuji = fuji;
	// debug
	printf("initialized player. [ADDR: %p]\n",plr);
}

void player_updt(player *plr)
{
	player_updtinp(plr);
}

void player_draw(player *plr)
{
	player_drawship(plr);
}

/*	--	update functions	--	*/
void player_updtinp(player *plr)
{
	// vars
	keine *kami = plr->kami;
	SDL_Event *evnt = &kami->inpevnt;
	// inp updating
	kami->keystate = SDL_GetKeyState(NULL);
	player_updtmove(plr);
	while(SDL_PollEvent(evnt))
	{
		keine_checkquit(kami);
	}
}

void player_updtmove(player *plr)
{
	// vars
	keine *kami = plr->kami;
	uint8_t *k_state = kami->keystate;
	VEC2 *pos = &plr->pos;
	VEC2 *dir = &plr->dir;
	s32 spd = 1<<8;
	// dir setting
	vec2_set(dir,0,0);
	if(k_state[SDLK_UP]) dir->y -= spd;
	if(k_state[SDLK_DOWN]) dir->y += spd;
	if(k_state[SDLK_LEFT]) dir->x -= spd;
	if(k_state[SDLK_RIGHT]) dir->x += spd;

	vec2_add(pos,dir);
}

/*	--	draw functions	--	*/
void player_drawship(player *plr)
{
	// vars
	VEC2 *pos = &plr->pos;
	VEC2 *dir = &plr->dir;
	s32 dx = pos->x>>8;
	s32 dy = pos->y>>8;	
	// drawin
	mokou_rect(plr->fuji,dx-8,dy-8,16,16,1);
	// debug
	char posstr[0x20]; vec2_str(pos,posstr);
	char dirstr[0x20]; vec2_str(dir,dirstr);
	printf("pos: %s\ndir: %s\n",posstr,dirstr);
}


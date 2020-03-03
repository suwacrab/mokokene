#include "player.h"

/*	--	main functions	--	*/
void player_init(player *plr,kaguya *hime)
{
	// initializin
	plr->hp = 3;
	vec2_set(&plr->pos,0,0);
	vec2_set(&plr->dir,0,0);
	plr->shottimer = 0;
	// EYS vars
	plr->hime = hime;
	plr->kami = hime->kami;
	plr->fuji = hime->fuji;
	// setup shot list
	plr->shotcount = 0;
	plr->shot0 = link_new(NULL,NULL);
	plr->lastshot = plr->shot0;
	link *shot0 = plr->shot0;
	shot0->d = malloc(sizeof(plr_shot));
	plr_shot *shotdat = (plr_shot*)shot0->d;
	
	vec2_set(&shotdat->pos,0,0);
	vec2_set(&shotdat->dir,0,0);
	// debug
	printf("initialized player. [ADDR: %p]\n",plr);
}

void player_updt(player *plr)
{
	player_updtinp(plr);
	player_updtmove(plr);
	player_updtshot(plr);
}

void player_draw(player *plr)
{
	player_drawship(plr);
	player_drawshot(plr);
}

/*	--	update functions	--	*/
void player_updtinp(player *plr)
{
	// vars
	keine *kami = plr->kami;
	SDL_Event *evnt = &kami->inpevnt;
	// inp updating
	kami->keystate = SDL_GetKeyState(NULL);
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

void player_updtshot(player *plr)
{
	// vars
	keine *kami = plr->kami;
	uint8_t *k_state = kami->keystate;
	// shot adding
	plr->shottimer++;
	bool shot_press = k_state[SDLK_z];
	if(shot_press && (plr->shottimer > 4) )
	{
		// creation
		link *nshot = link_addnext(plr->lastshot);
		nshot->d = malloc(sizeof(plr_shot));
		plr_shot *shotdat = (plr_shot*)nshot->d;
		// movement
		vec2_set(&shotdat->pos,plr->pos.x,plr->pos.y);
		vec2_set(&shotdat->dir,0,(1<<8) * (-3) );
		// final set
		plr->shottimer = 0;
		plr->lastshot = nshot;
	}
	// moving all shots, getting count
	link *curshot = plr->shot0->next;
	u32 shotcount = 0;
	for(; curshot != NULL; shotcount++)
	{
		// var
		plr_shot *shotdat = (plr_shot*)curshot->d;
		VEC2 *updir = &shotdat->dir;
		// movin
		vec2_add(&shotdat->pos,updir);
		// OOB handlin
		if(shotdat->pos.y < -8)
		{
			// if lastshot == curshot,just use last.
			if(plr->lastshot == curshot) plr->lastshot = curshot->last;
			free(shotdat);
			link_del(curshot);
		}
		curshot = curshot->next;
	}
	plr->shotcount = shotcount;
}

/*	--	draw functions	--	*/
void player_drawship(player *plr)
{
	// vars
	VEC2 *pos = &plr->pos;
	s32 dx = (pos->x>>8)-8;
	s32 dy = (pos->y>>8)-8;	
	// drawin
	mokou *plr_img = plr->hime->img_bank[1];
	mokou_blit(plr_img,NULL,plr->fuji,dx,dy);
}

void player_drawshot(player *plr)
{
	// vars
	kosuzu *borefont = plr->hime->fnt_bank[0];
	link *curshot = plr->shot0->next;
	u32 shotcount = 0;
	// draw
	for(; curshot != NULL; shotcount++)
	{
		// vars
		plr_shot *shotdat = (plr_shot*)curshot->d;
		VEC2 pos = shotdat->pos;
		pos.x >>= 8;
		pos.y >>= 8;
		// drawin
		mokou_rect(plr->fuji,pos.x-4,pos.y-4,8,8,1);
		curshot = curshot->next;
	}
	// debug
	char text[0x20];
	sprintf(text,"COUNT: %04X\n",shotcount);
	kosuzu_blit(borefont,text,plr->fuji,8,8,strlen(text));
}

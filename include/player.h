/* main player defs
	* suwacrab 2020-02-23
*/

#include "kbase.h"
#include "link.h"
#include "fade.h"
#include "mokou.h"
#include "keine.h"
#include "kaguya.h"

#ifndef PLAYER_H
#define PLAYER_H

/*	--	structs	--	*/
typedef struct plr_shot {
	VEC2 pos,dir;
} plr_shot;

typedef struct player {
	// basic vars
	VEC2 pos,dir; // vectors in 24.8 fixed point fmt
	s8 hp;
	// shot vars
	link *shot0;
	link *lastshot;
	u32 shotcount;
	u32 shottimer;
	// EYS vars
	kaguya *hime;
	keine *kami;
	mokou *fuji;
} player;

/*	--	main functions	--	*/
extern void player_init(player *plr,kaguya *hime);
extern void player_updt(player *plr);
extern void player_draw(player *plr);

/*	--	update functions	--	*/
extern void player_updtinp(player *plr);
extern void player_updtmove(player *plr);
extern void player_updtshot(player *plr);

/*	--	draw functions	--	*/
extern void player_drawship(player *plr);
extern void player_drawshot(player *plr);

#endif

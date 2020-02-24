/* main player defs
	* suwacrab 2020-02-23
*/

#include "kbase.h"
#include "mokou.h"
#include "keine.h"

#ifndef PLAYER_H
#define PLAYER_H

/*	--	structs	--	*/
typedef struct
{
	// basic vars
	VEC2 pos,dir;
	s8 hp;
	// input vars
	u32 last_shotframe;
	// fb vars
	keine *kami;
	mokou *fuji;
} player;

/*	--	main functions	--	*/
extern void player_init(player *plr,keine *kami,mokou *fuji);
extern void player_updt(player *plr);
extern void player_draw(player *plr);

/*	--	update functions	--	*/
extern void player_updtinp(player *plr);
extern void player_updtmove(player *plr);

/*	--	draw functions	--	*/
extern void player_drawship(player *plr);

#endif
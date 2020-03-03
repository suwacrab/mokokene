#include "link.h"

link *link_new(link *last,link *next)
{
	link *l = malloc(sizeof(link));
	l->last = last;
	l->next = next;
	return l;
}

void link_del(link *l)
{
	// vars
	link *last = l->last;
	link *next = l->next;
	// deletin
	if(last) last->next = next;
	if(next) next->last = last;
	free(l);
}

void link_print(link *l)
{
	link *cur_link = l;
	u32 i = 0;
	while(cur_link != NULL)
	{
		void *data = cur_link->d;
		u32 n = 0;
		if(data != NULL) n = *(u32*)data;
		printf("%p [%02d] (%08X)\n",cur_link,i,n);
		
		cur_link = cur_link->next;
		i++;
	}
}

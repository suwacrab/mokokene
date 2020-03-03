#include "kbase.h"

#ifndef LINK_H
#define LINK_H

/*	--	structs	--	*/
typedef struct link {
	struct link *last; // last link
	struct link *next; // next link
	void *d; // data
} link;

/*	--	functions	--	*/
extern link *link_new(link *last,link *next);
extern void link_del(link *l);
extern void link_print(link *l);

/*	--	inline functions	--	*/
INLINE link *link_addnext(link *l)
{
	link *nlink = link_new(l,NULL);
	l->next = nlink;
	return nlink;
}

#endif

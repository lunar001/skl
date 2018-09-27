#ifndef SKL_H
#define SKL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SKL_MXLVL 4 /* The max height of skiplist node*/

static ssize_t SKL_RNL[] = 
{
	4, 2, 3, 2, 3, 1, 2, 1, 2, 3, 3, 4, 1, 1, 1, 3, 4, 2, 1, 2,
	4, 2, 3, 2, 3, 1, 2, 1, 2, 3, 3, 4, 1, 1, 1, 3, 4, 2, 1, 2,
	4, 2, 3, 2, 3, 1, 2, 1, 2, 3, 3, 4, 1, 1, 1, 3, 4, 2, 1, 2,
	4, 2, 3, 2, 3, 1, 2, 1, 2, 3, 3, 4, 1, 1, 1, 3, 4, 2, 1, 2,
	4, 2, 3, 2, 3, 1, 2, 1, 2, 3, 3, 4, 1, 1, 1, 3, 4, 2, 1, 2,
	4, 2, 3, 2, 3, 1, 2, 1, 2, 3, 3, 4, 1, 1, 1, 3, 4, 2, 1, 2,
	4, 2, 3, 2, 3, 1, 2, 1, 2, 3, 3, 4, 1, 1, 1, 3, 4, 2, 1, 2,
	4, 2, 3, 2, 3, 1, 2, 1, 2, 3, 3, 4, 1, 1, 1, 3, 4, 2, 1, 2,
	4, 2, 3, 2, 3, 1, 2, 1, 2, 3, 3, 4, 1, 1, 1, 3, 4, 2, 1, 2,
	4, 2, 3, 2, 3, 1, 2, 1, 2, 3, 3, 4, 1, 1, 1, 3, 4, 2, 1, 2
};

typedef struct skl_header
{
	ssize_t skl_level; /* The current max level of skiplist */
	struct skl_node * tail;

} SklHdr;

typedef struct skl_node
{
	unsigned long key;
	struct  skl_node * back;
	/* Level pointers, use zero-length array to store the forward ptr, the zero-length array occupy no memory*/
	struct  skl_node * frwrd[];
}SklNode;

ssize_t GetLevel();
struct skl_header * CreateSkl();
void InsertSkl(SklHdr * hdr, SklNode * node, ssize_t level);
SklNode * DeleteSkl(SklHdr * hdr, unsigned long key);
void SklTrav(SklHdr * hdr);
#endif

#include "skl.h"

ssize_t GetLevel()
{
	return (SKL_RNL[rand() % 200]);
}

struct skl_header * CreateSkl()
{
	struct skl_header * hdr = NULL;
	ssize_t hdrlen = sizeof(struct skl_header) + sizeof(struct skl_node) + SKL_MXLVL * sizeof(void *);
	hdr = (struct skl_header *)malloc(hdrlen);
	memset((void*)hdr, 0, hdrlen);

	hdr->tail = (void*)hdr + sizeof(struct skl_header);
	return hdr;
}

void DestroySkl(SklHdr * hdr)
{
	if(hdr)
		free(hdr);
	return;
}

void InsertSkl(SklHdr * hdr, SklNode * node, ssize_t level)
{
	SklNode * head = (void *)hdr + sizeof(SklHdr);
	SklNode * update[SKL_MXLVL - 1] = {NULL};

	/* skl_level - 1 is transform to index */
	ssize_t i = hdr->skl_level - 1;

	for(; i >= 0; i--)
	
	{
		while(head != NULL && head->frwrd[i] != NULL &&
				head->frwrd[i]->key <= node->key)
		{
			if(head->frwrd[i]->key == node->key)
			{
				printf("repeat node insert\n");
				return;
			}
			head = head->frwrd[i];
		}
		update[i] = head;
	}

	/* the new insert node's level is higher than the current max height of skiplist */
	if(level > hdr->skl_level)
	{
		for(i = level - 1; i > hdr->skl_level - 1; i--)
			update[i] = (void *)hdr + sizeof(SklHdr);
		
		hdr->skl_level = level;
	}

	/* attention: level is num of level of newly insert node, the index should minus one*/
	for(i = level-1; i >= 0; i--)
	{
		node->frwrd[i] = update[i]->frwrd[i];
		update[i]->frwrd[i] = node;
	}

	update[0]->frwrd[0]->back = node;
	node->back = update[0];

	return;
}


void SklTrav(SklHdr * hdr)
{
	ssize_t i = SKL_MXLVL - 1;
	struct skl_node * head = (void *)hdr + sizeof(struct skl_header);
	struct skl_node * tmp = head;

	for(; i >= 0; i--)
	{
		printf("In level %ld\n", i);
		tmp = head;
		while(tmp)
		{
			printf("%lu->", tmp->key);
			tmp = tmp->frwrd[i];
		}
		printf("\n");

	}
}








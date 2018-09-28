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
SklNode * DeleteSkl(SklHdr * hdr, unsigned long key)
{
	/* Delete node whose key equals key from the skip list*/
	SklNode * head = (void *)hdr + sizeof(SklHdr);

	SklNode * update[SKL_MXLVL] = { NULL };

	/* node store the deleted node and return caller */
	SklNode * node = NULL; 
	
	/* minusing one transform level to index */
	ssize_t i = hdr->skl_level - 1; 

	for(; i>= 0; i--)
	{
		while(head != NULL && head->frwrd[i] != NULL
				&&head->frwrd[i]->key < key)
			head = head->frwrd[i];

		update[i] = head;
	}

	/* not like insert, we don't need to update all the level list */

	/* to here, head is must points the previous element of node   *
	 * otherwise, node is not exist in this skip list              */
	if (head->frwrd[0] != NULL && head->frwrd[0]->key == key)
	{
		/* first update the lowest list, the list in this level is doubly linked list*/
		head = update[0]->frwrd[0];
		node = head;
		update[0]->frwrd[0] = head->frwrd[0];
		if(head->frwrd[0] != NULL)
			head->frwrd[0]->back = update[0];
		/* second update all the higher leveles, the list in those level are single list*/
		for(i = 1; i < hdr->skl_level; i++)
		{
			/* for every level, check if the forward node is the deleted node or not */
			head = update[i]->frwrd[i];
			if(head != NULL && head->key == key)
				/* of course, head->frwrd[i] may equals NULL*/
				update[i]->frwrd[i] = head->frwrd[i]; 
		}
		
		return  node;
	}
	else
		/* node is not include in this skip list */
		return NULL;

}

SklNode * SearchNode(SklHdr * hdr, unsigned long key)
{
	/* search the node whose's key equals to key */
	/* if not find the target node, return NULL */
	SklNode * head = (void *)hdr + sizeof(struct skl_header);
	SklNode * target = NULL;
	ssize_t i = hdr->skl_level - 1;
	for(; i >= 0; i--)
	{
		while(head->frwrd[i] != NULL &&
				head->frwrd[i]->key < key)
			head = head->frwrd[i];
		
		if(head->frwrd[i] == NULL ||
				head->frwrd[i]->key > key)
			continue;
		else
			/* find the target node */
			target = head->frwrd[i];
	}
	return target;
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








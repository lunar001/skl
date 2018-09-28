#include "skl.h"
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
struct Node{
	int value;
	struct skl_node node;
};

int main()
{
	struct skl_header * hdr = CreateSkl();
	unsigned long array[10] = {2, 3, 8, 1, 9, 4, 5, 6, 7, 11};
	int i = 0;
	printf("%d\n", sizeof(int));
	printf("%d\n", offsetof(struct Node, node));
	for(i = 0; i < 10; i++)
	{
		ssize_t level = GetLevel();
		/* When allocate memory for Node, don't forget the zeor-length array*/
		struct Node * node = (struct Node * )malloc(sizeof(struct Node) + level * sizeof(void*));
		node->value = i;
		node->node.key = array[i];
		printf("Insert node = %x, node->value = %d, node->node.key = %lu, level = %ld\n", 
				node, node->value, node->node.key, level);
		InsertSkl(hdr, &(node->node), level);
		printf("Insert node = %x\n", &(node->node)); 

	}

	SklTrav(hdr);	

	SklNode * ps = SearchNode(hdr, array[9]);

	if(ps == NULL)
		printf("Can't find %d in skiplist \n", array[9]);
	else
	{
		printf("%d, array[9] = %d\n", ps->key, array[9]);
		struct Node * pp = (struct Node * )((void*)ps - offsetof(struct Node, node));
		printf("The vale of %d is %d\n", array[9], pp->value);
	}
	for (i = 1; i < 10; i = i + 2)
	{
		struct SklNode  * node = DeleteSkl(hdr, array[i]);
		if(node != NULL)
		{
			struct Node * pnode = (void *)node - offsetof(struct Node, node); 
		    printf("The delete node is %x, pnode->value = %d, pnode->node.key = %lu\n", 
					pnode, pnode->value, pnode->node.key);

		}
		
	}
	SklTrav(hdr);
	return 0;

}

/*
Jessica Guo
Christine Do

CS214 Assignment01 due October 14, 2016 @ 11:55PM

*/

#ifndef MYMALLOC_H
#define MYMALLOC_H

#define malloc(x) mymalloc(x)
#define free(x) myfree(x)


static char myblock[5000]; 
static int initialized = 0; /*to keep track if mymalloc() has been called before*/

/*linked list*/
typedef struct memoryNode{

	unsigned int size;
	unsigned int isfree; 
	/* isfree =1, !isfree=0 */

	struct memoryNode *next, *prev;
} memoryNode;

static const int memSize = (5000)/sizeof(memoryNode) + 1; /*size of the memory nodes*/
static void *memPtr[5000/ (sizeof(memoryNode)+1)] = {0}; /*pointer to the memory nodes*/


void *mymalloc(unsigned int size);
void myfree(void *ptr);

#endif
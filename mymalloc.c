/*Jessica Guo
Christine Do

CS214 Assignment01 due October 14, 2016 @ 11:55PM

*/

#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

/*main for basic testing/compilation */

int main(){
	int* p = malloc(4900);
    printf("malloc worked\n");
    *p = 5;
    printf("address: %p, value: %d\n",p, *p);

    free(p);

    printf("free worked\n");

	return 0;
} 


/*Gets the first index that is not in use*/
static int getFreeIndex(){
	int i;
		for (i=0; i < memSize; i++){
			if(memPtr[i]==0)
					return i;
		}
	return 1;
}

void * mymalloc(unsigned int size){

	struct memoryNode *ptr;
	struct memoryNode *next;

	static struct memoryNode *root;
	
	/*Asking to allocate 0 bytes of memory*/
	if(size==0){
		fprintf(stderr, "why would you ask to allocate 0 memory like??? in FILE: \"%s\" LINE: '%d'\n", __FILE__ , __LINE__);
		return 0;
	}

	/*first time calling mymalloc()*/
	if(initialized ==0){

		root = (struct memoryNode*) myblock;
		root->prev = root->next =0;
		root->size = 5000 - sizeof(struct memoryNode);
		root->isfree = 1; /*is free*/
		initialized =1;

		memPtr[getFreeIndex()]= myblock;
	}

	ptr = root;

	while(ptr!=0){

		/*the size is to small or the space isn't free*/
		if(ptr->size <size || !ptr->isfree){ 
			ptr=ptr->next;
		}

		/*exactly enough space, not enough for a new head node*/
		else if(ptr->size < (size + sizeof(struct memoryNode))){
			ptr->isfree=0;
			return (char*)ptr + sizeof(struct memoryNode);
		}
		/*allocate space and new head node*/
		else{
			next = (struct memoryNode*)((char*)ptr +sizeof(struct memoryNode)+size);
			next->prev = ptr;
			next->next = ptr->next;
			next->size = ptr->size - sizeof(struct memoryNode)-size;
			next->isfree=1;
			memPtr[getFreeIndex()] = next;
			ptr->size = size;
			ptr->isfree=0;
			ptr->next = next;

			return(char*)ptr + sizeof(struct memoryNode);

		}
	} 
	/*full or not enough space*/
	fprintf(stderr, "Not enough memory: '%d'bytes FILE: \"%s\"  LINE'%d'\n", size, __FILE__, __LINE__);
	return 0;
}



void myfree(void *ptr){

	struct memoryNode *p;
	struct memoryNode *prev;
	struct memoryNode *next;

	if(ptr == NULL){
		fprintf(stderr, "ERROR: NULL pointer, free() failed in FILE:\"%s\"  LINE: '%d'", __FILE__, __LINE__);
		return;
	}

	p = (struct memoryNode*)((char*)ptr - sizeof(struct memoryNode));

	/*check for valid memPtr*/
	int i;
	int valid =0;
	for (i =0; i< memSize; i++){
		if(p==memPtr[i] && !p->isfree){
			valid =1;
			break;
		}
	}

	if(valid ==0){
		fprintf(stderr, "ERROR: cannot free pointer that was not malloc() on LINE '%d' FILE \"%s\" ", __LINE__, __FILE__);
		return;
	}

	/*merge w/ prev nodes that are free*/
	if((prev = p->prev)!=0 && prev->isfree){
		prev->size += sizeof(struct memoryNode)+ p->size;
		memPtr[i] = 0;
	}

	else{
		p ->isfree =1;
		prev = p;
	}
	/*merge w/ following nodes that are free*/
	if((next = p->next)!=0 && next ->isfree){
		prev->size += sizeof(struct memoryNode)+ next->size;
		prev->next = next->next;

		for (i=0; i<memSize; i++){
			if(next==memPtr[i]){
				memPtr[i]=0;
				break;
			}
		}
	}
	return;

}
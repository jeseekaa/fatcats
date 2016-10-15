/*Jessica Guo
Christine Do

CS214 Assignment01 due October 14, 2016 @ 11:55PM

*/

#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

static char myblock[5000]; 
static int initialized = 0; /*to keep track if mymalloc() has been called before*/

static void *memPtr[5000/ (sizeof(memoryNode)+1)] = {0}; 

/*main for basic testing/compilation:
the following works: */


/*int main(){
	char* p1 = malloc(1);
	*p1=3;
	printf("address: %p, value: %d\n", p1, *p1);
	char* p2 = malloc(1);
	*p2 = 4;
	printf("address: %p, value: %d\n", p2, *p2);
	char* p3 = malloc(3000);
	printf("address: %p \n", p3);
	char* p4 = malloc(1);
	printf("address: %p \n", p4);
	char* p5 = malloc(1);
	printf("address: %p \n", p5);
	char* p6 = malloc(1);
	printf("address: %p \n", p6);
	char* p7 = malloc(1);
	printf("address: %p \n", p7);
	char* p8 = malloc(1);
	printf("address: %p \n", p8);
	char* p9 = malloc(1);
	printf("address: %p \n", p9);
	char* p10 = malloc(1);
	printf("address: %p \n", p10);

	free(p1);
	printf("myfree worked\n");
	free(p2);
	printf("myfree worked\n");
	free(p3);
	printf("myfree worked\n");
		free(p4);
	printf("myfree worked\n");
		free(p5);
	printf("myfree worked\n");
		free(p6);
	printf("myfree worked\n");
		free(p7);
	printf("myfree worked\n");
		free(p8);
	printf("myfree worked\n");
		free(p9);
	printf("myfree worked\n");
		free(p10);
	printf("myfree worked\n");
}*/


// 	int* p1;
// 	free(p1);
// 	printf("myfree worked\n");

// 	int* p2 = malloc(sizeof(int));
// 	printf("mymalloc worked\n");

// 	*p2 = 5;
// 	printf("address: %p, value: %d\n", p2, *p2);

// 	free(p2);
// 	free(p2);
// 	/*should return an error*/
// 	printf("myfree worked\n");

// 	int* p2a = malloc(sizeof(int));
// 	*p2a = 7;
// 	/*since the previous one was freed, the address should be the same*/
// 	printf("address: %p, value: %d\n", p2a, *p2a);
// 	printf("mymalloc worked\n");

// 	free(p2a);
// 	printf("myfree worked\n");

// 	int* p3 = malloc(0);
// 	printf("mymalloc worked \n");

// 	free(p3);
// 	printf("myfreeworked\n");
// 	return 0; }
 


/*Gets the first index that is not in use*/
static int getFreeIndex(){
	int i;
		for (i=0; i < memSize; i++){
			if(memPtr[i]==0)
					return i;
		}
	return 1;
}

/*mymalloc function*/
void * mymalloc(unsigned int size){

	memoryNode *ptr;
	memoryNode *next;

	static memoryNode *root;
	
	/*Asking to allocate 0 bytes of memory*/
	if(size==0){
		fprintf(stderr, "ERROR: cannot malloc 0 bytes LINE %d FILE: \"%s\" \n", __LINE__ , __FILE__);
		return 0;
	}

	/*first time calling mymalloc()*/
	if(initialized ==0){

		root = (memoryNode*) myblock;
		root->prev = root->next =0;
		root->size = 5000 - sizeof(memoryNode);
		root->isfree = 1; /*is free*/
		initialized =1;

		memPtr[getFreeIndex()]= myblock;
	}

	/*mymalloc() has been called before*/

	ptr = root;

	while(ptr!=0){

		/*the size is to small or the space isn't free, keep moving along*/
		if(ptr->size <size || !ptr->isfree){ 
			ptr=ptr->next;
		}

		/*exactly enough space, not enough for a new head node*/
		else if(ptr->size < (size + sizeof(memoryNode))){
			ptr->isfree=0;
			return (char*)ptr + sizeof(memoryNode);
		}

		/*allocate space and new head node*/
		else{
			next = (memoryNode*)((char*)ptr +sizeof(memoryNode)+size);
			next->prev = ptr;
			next->next = ptr->next;
			next->size = ptr->size - sizeof(memoryNode)-size;
			next->isfree=1;

			memPtr[getFreeIndex()] = next;
			ptr->size = size;
			ptr->isfree=0;
			ptr->next = next;

			return(char*)ptr + sizeof(memoryNode);

		}
	} 

	/*full or not enough space*/
	fprintf(stderr, "ERROR: Not enough memory: %d bytes LINE: %d FILE: \"%s\"\n", size, __LINE__, __FILE__);
	return 0;
}


/*myfree funtion*/
void myfree(void *ptr){

	memoryNode *p;
	memoryNode *prev;
	memoryNode *next;

	if(ptr == NULL){
		fprintf(stderr, "ERROR: NULL pointer: LINE: %d FILE:\"%s\"  \n", __LINE__, __FILE__);
		return;
	}

	p = (memoryNode*)((char*)ptr - sizeof(memoryNode));

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
		fprintf(stderr, "ERROR: cannot free pointer that was not malloc() on LINE: %d FILE: \"%s\"\n ", __LINE__, __FILE__);
		return;
	}

	/*merge w/ prev nodes that are free*/
	if((prev = p->prev)!=0 && prev->isfree){
		prev->size += sizeof(memoryNode)+ p->size;
		memPtr[i] = 0;
	}

	else{
		p ->isfree =1;
		prev = p;
	}
	/*merge w/ following nodes that are free*/
	if((next = p->next)!=0 && next ->isfree){
		prev->size += sizeof(memoryNode)+ next->size;
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


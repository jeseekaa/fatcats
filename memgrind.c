#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mymalloc.h"



int main(){
	int randomSelect[] = {0,1};
	srand(time(0));
	int randomNumber = randomSelect[rand()%2];

	int* p1;
	free(p1);
	printf("1: myfree worked\n");

	int* p2 = malloc(sizeof(int));
	printf("2: mymalloc worked\n");

	*p2 = 5;
	printf("3: address: %p, value: %d\n", p2, *p2);

	free(p2);
	free(p2);
	/*should return an error*/
	printf("4: myfree worked\n");

	int* p2a = malloc(sizeof(int));
	*p2a = 7;
	/*since the previous one was freed, the address should be the same*/
	printf("address: %p, value: %d\n", p2a, *p2a);
	printf("mymalloc worked\n");

	free(p2a);
	printf("myfree worked\n");

	int* p3 = malloc(0);
	printf("mymalloc worked \n");

	free(p3);
	printf("myfreeworked\n");
	return 0;
}

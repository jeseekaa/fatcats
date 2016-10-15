/*
Christine Do
Jessica Guo

CS214 Assignment01 due October 14, 2016 @ 11:55PM

*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "mymalloc.h"



int main(){
	struct timeval t1, t2;
	double elapsedTime;
	int instruct;
	int randomSelect[] = {0,1};
	srand(time(0));

	void * plswork[3000];

	//printf("random worked: %d %d %d %d \n", randomSelect[rand()%2],randomSelect[rand()%2],randomSelect[rand()%2],randomSelect[rand()%2]);
	printf("Input test case: 1-6\n");
	scanf("%d", &instruct);

	switch(instruct) {
		case 1: {

			printf(" malloc() 1 byte 3000 times, then free() the 3000 1 byte pointers one by one\n");
						
			int testCounter =0;
			float sum = 0;
			float avg = 0;
			int i;

			//for some reason only works once

			//for (testCounter = 0; testCounter < 100; testCounter++){
				gettimeofday(&t1, NULL);

				for(i=0; i<3000; i++){
					plswork[i] = malloc(1);
				}

				for(i=0; i<3000; i++){
					free(plswork[i]);
				}

				gettimeofday(&t2, NULL);

    			// compute and print the elapsed time in millisec
				elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
				elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
				sum = sum + elapsedTime;

				//printf("sum as of now: %.6f", sum);
				printf("test count: %d\n time: %f\n\n", testCounter, elapsedTime);

				if(testCounter==99){
					avg = sum/100;
					printf("Average time: %.6f\n", avg);
				}
			//}

			printf(" malloc() 1 byte 3000 times, then free() the 3000 1 byte pointers one by one\n");
		}
		break;

		case 2: {
			int testCounter;
			float sum = 0;
			float avg = 0;

			for (testCounter = 0; testCounter < 100; testCounter++){
				gettimeofday(&t1, NULL);
				int i;
				for(i = 0; i < 3000; i++) {
					char *test = malloc(1);
					free(test);
				} 
				gettimeofday(&t2, NULL);
    			// compute and print the elapsed time in millisec
				elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
				elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
				sum = sum + elapsedTime;
				//printf("sum as of now: %.6f", sum);
				printf("test count: %d\n time: %f\n\n", testCounter, elapsedTime);
				if(testCounter==99){
					avg = sum/100;
					printf("Average time: %.6f\n", avg);
				}
			}
			printf(" malloc() 1 byte and immediately free it 3000 times in a row\n");
		}
		break;

		case 3: {

			int mallocTracker = 0;
			int successfulMalloc = 0;
			int testCounter = 0;
			float sum = 0;
			float avg = 0;
			void *testArray[100];

<<<<<<< HEAD
			for (testCounter = 0; testCounter < 100; testCounter++) { 

				gettimeofday(&t1, NULL);

				while(mallocTracker < 3000) {

					int randomCase = randomSelect[rand()%2];

					//malloc a byte
					if (randomCase == 0 || successfulMalloc == 0) {
						testArray[successfulMalloc] = malloc(1);
						mallocTracker++;
						successfulMalloc++;
						printf("MALLOC CHOOSEN %d\n", mallocTracker);
					} else {
						//free a random byte on the array
						int randomFree = rand() % 100;
						free(testArray[randomFree]);
						printf("FREE CHOSEN: %d\n",randomFree);
						successfulMalloc--;
					} 
				}
				//free all good mallocs 
				while (successfulMalloc > 0) {

					free(testArray[successfulMalloc - 1]);
					successfulMalloc--;
				}

				//calculate stuff

				gettimeofday(&t2, NULL);
				elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
				elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
				sum = sum + elapsedTime;
				printf("test count: %d\n time: %f\n\n", testCounter, elapsedTime);
				if(testCounter==99){
					avg = sum/100;
					printf("Average time: %.6f\n", avg);
				}


			} 

			printf(" Randomly choose between a 1 byte malloc() or free() 6000 times\n");
		}
		break;

		case 4: {
			int testCounter;
			float sum = 0;
			float avg = 0;

			int r;
			r = randomSelect[rand()%2];

		for(testCounter=0; testCounter <100; testCounter++){
			gettimeofday(&t1, NULL);
				int i;
				//fill in shit here
			//use randomgen, if 1= malloc, 0 = free
			//random gen any number from 1-100 to malloc()
			//if malloc is error then free
			//if free is error then malloc
				
				gettimeofday(&t2, NULL);
    			// compute and print the elapsed time in millisec
				elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
				elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
				sum = sum + elapsedTime;
				printf("test count: %d\n time: %f\n\n", testCounter, elapsedTime);

				if(testCounter==99){
					avg = sum/100;
					printf("Average time: %.6f\n", avg);
				}

			}

			printf("Randomly choose between a randomly-sized malloc() or free 6000 times\n");
		}
		break;

		case 5: {
			int testCounter;
			float sum = 0;
			float avg = 0;

		for(testCounter=0; testCounter <100; testCounter++){
			gettimeofday(&t1, NULL);
				int i;
				
				//the things go here
				
				gettimeofday(&t2, NULL);
    			// compute and print the elapsed time in millisec
				elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
				elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
				sum = sum + elapsedTime;
				printf("test count: %d\n time: %f\n\n", testCounter, elapsedTime);

				if(testCounter==99){
					avg = sum/100;
					printf("Average time: %.6f\n", avg);
				}

			}
			printf("workload 1 of choosing\n");

		}
		break;

		case 6: { //different types and their values
			int testCounter;
			float sum = 0;
			float avg = 0;
			
		for(testCounter=0; testCounter <100; testCounter++){
			gettimeofday(&t1, NULL);
				int i;
				
				//the shit goes here
				
				gettimeofday(&t2, NULL);
    			// compute and print the elapsed time in millisec
				elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
				elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
				sum = sum + elapsedTime;
				printf("test count: %d\n time: %f\n\n", testCounter, elapsedTime);

				if(testCounter==99){
					avg = sum/100;
					printf("Average time: %.6f\n", avg);
				}

			}
			printf ("workload 2 of choosing: different types and their values\n");
		}
		break;

		default:
			printf("real input pls");
	}
	// int* p1;
	// free(p1);
	// printf("1: myfree worked\n");

	// int* p2 = malloc(sizeof(int));
	// printf("2: mymalloc worked\n");

	// *p2 = 5;
	// printf("3: address: %p, value: %d\n", p2, *p2);

	// free(p2);
	// free(p2);
	// /*should return an error*/
	// printf("4: myfree worked\n");

	// int* p2a = malloc(sizeof(int));
	// *p2a = 7;
	// /*since the previous one was freed, the address should be the same*/
	// printf("address: %p, value: %d\n", p2a, *p2a);
	// printf("mymalloc worked\n");

	// free(p2a);
	// printf("myfree worked\n");

	// int* p3 = malloc(0);
	// printf("mymalloc worked \n");

	// free(p3);
	// printf("myfreeworked\n");
	return 0;
} //end of main

void case1(int i){

	void * omg[3000];

	for(i=0; i<3000; i++){
		omg[i] = malloc(1);
		}

	for(i=0; i<3000; i++){
		free(omg[i]);
	}
	return;
}
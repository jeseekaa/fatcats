Jessica Guo, Christine Do
CS214: Systems Programming 
Assignment01: A better malloc() and free() due October 14, 2016

mymalloc.c implementation
This assignment used a static char array, myblock[5000] to simulate the heap. This is where we will allocate the dynamic memory called up by mymalloc(). Another void* array is initialized to hold the memory entries requested by the user (the metadata). All elements are initialized to 0, signifying that it is not in use.  When mymallo() is called, a section of space is given corresponding to the requested size. Preceding the space in memoryNode struct head which helps keep track of how much space is used or available. Mymalloc() will return the pointer, the section of memory, and the pointer to the memoryNode struct is stored in the memPtr array. When free() is called, the size of memoryNode is subtracted from the address contained in the pointer. It is then check against the memPtr for validity. If it is a valid pointer, then the space is freed and merged with adjacent free blocks. If the pointer is not valid, an error message is returned. 

As the number of time mmalloc() is increases, the memoryNodes that are required for us to iterate through to find a block increase proportionally. This holds for myfree() as well; therefore, mymalloc() and myfree() have a time complexity of O(n).

Detectable Errors:
Memgrind.c
To test any of the cases in memgrind.c. input a number 1-6 when prompted corresponding to:
1.	malloc() 1 byte 3000 times, then free() 3000 1 byte pointers one by one
2.	malloc() 1 byte and immediately free it 3000 times in a row
3.	Randomly choose between a 1 byte malloc() or free() 6000 times
4.	Randomly choose between a randomly sized malloc() or free 6000 times
5.	Work load 1
6.	Work load 2

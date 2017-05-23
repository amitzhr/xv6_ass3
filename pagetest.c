#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

#define PGSIZE 4096

int
main(int argc, char *argv[]){

#ifdef LIFO

	int i;
	char *arr[14];
	char input[10];
	
	// Fill all physical memory
	for (i = 0; i < 12; ++i) {
		arr[i] = sbrk(PGSIZE);
		printf(1, "arr[%d]=0x%x\n", i, arr[i]);
	}
	printf(1, "Called sbrk(PGSIZE) 12 times - all physical pages taken.\nPress any key...\n");
	gets(input, 10);

	arr[12] = sbrk(PGSIZE);
	printf(1, "arr[12]=0x%x\n", arr[12]);
	printf(1, "Called sbrk(PGSIZE) for the 13th time, One page in swap file.\nPress any key...\n");
	gets(input, 10);

	arr[13] = sbrk(PGSIZE);
	printf(1, "arr[13]=0x%x\n", arr[13]);
	printf(1, "Called sbrk(PGSIZE) for the 14th time. Two pages in swap file.\nPress any key...\n");
	gets(input, 10);

	for (i = 11; i <= 13; i++) {
		arr[i][5] = 'a';
	}
	printf(1, "3 page faults should have occurred.\nPress any key...\n");
	gets(input, 10);

	if (fork() == 0) {
		printf(1, "Child code running.\n");
		printf(1, "View statistics for pid %d, then press any key...\n", getpid());
		gets(input, 10);

		arr[11][0] = 't';
		printf(1, "A page fault should have occurred in the child process.\nPress any key to exit the child code.\n");
		gets(input, 10);

		exit();
	}
	else {
		wait();

		/*
		Deallocate all the pages.
		*/
		sbrk(-14 * PGSIZE);
		printf(1, "Deallocated all extra pages.\nPress any key to exit the father code.\n");
		gets(input, 10);
	}

#elif SCFIFO
	int i, j;
	char *arr[14];
	char input[10];

	printf(1, "Testing SCFIFO... \n");

	// Fill all physical memory
	for (i = 0; i < 12; ++i) {
		arr[i] = sbrk(PGSIZE);
		printf(1, "arr[%d]=0x%x\n", i, arr[i]);
	}
	printf(1, "Called sbrk(PGSIZE) 12 times - all physical pages taken.\nPress any key...\n");
	gets(input, 10);

	arr[12] = sbrk(PGSIZE);
	printf(1, "arr[12]=0x%x\n", arr[12]);
	printf(1, "Called sbrk(PGSIZE) for the 13th time. One page in swap file.\nPress any key...\n");
	gets(input, 10);

	arr[13] = sbrk(PGSIZE);
	printf(1, "arr[13]=0x%x\n", arr[13]);
	printf(1, "Called sbrk(PGSIZE) for the 14th time. Two pages in swap file.\nPress any key...\n");
	gets(input, 10);

	for (i = 0; i < 5; i++) {
		for (j = 0; j < PGSIZE; j++)
			arr[i][j] = 'k';
	}
	printf(1, "5 page faults should have occurred.\nPress any key...\n");
	gets(input, 10);

	if (fork() == 0) {
		printf(1, "Child code running.\n");
		printf(1, "View statistics for pid %d, then press any key...\n", getpid());
		gets(input, 10);

		arr[5][0] = 'k';
		printf(1, "A page fault should have occurred in the child process.\nPress any key to exit the child code.\n");
		gets(input, 10);

		exit();
	}
	else {
		wait();

		sbrk(-14 * PGSIZE);
		printf(1, "Deallocated all extra pages.\nPress any key to exit the father code.\n");
		gets(input, 10);
	}


#elif LAP
	
	int i;
	char *arr[27];
	char input[10];

	printf(1, "Testing LAP... \n");

	// Fill all physical memory
	for (i = 0; i < 12; ++i) {
		arr[i] = sbrk(PGSIZE);
		printf(1, "arr[%d]=0x%x\n", i, arr[i]);
	}
	printf(1, "Called sbrk(PGSIZE) 12 times - all physical pages taken.\nPress any key...\n");
	gets(input, 10);

	arr[12] = sbrk(PGSIZE);
	printf(1, "arr[12]=0x%x\n", arr[12]);
	printf(1, "Called sbrk(PGSIZE) for the 13th time. Page 1 should be paged out.\nPress any key...\n");
	gets(input, 10);

	for (i = 0; i < 12; i++) {
		if (i != 5)
			arr[i][0] = 'j';
	}
	sleep(1);

	arr[13] = sbrk(PGSIZE);
	printf(1, "arr[13]=0x%x\n", arr[13]);
	printf(1, "Called sbrk(PGSIZE) for the 14th time. Page of arr[5] should be paged out.\nPress any key...\n");
	gets(input, 10);

	for (i = 0; i < 12; i++)
		if (i != 5)
			arr[i][0] = 'a';

	arr[5][0] = 'a';
	sleep(1);
	arr[12][0] = 'b';
	sleep(1);
	arr[13][0] = 'c';
	sleep(1);
	arr[5][0] = 'd';
	sleep(1);
	arr[12][0] = 'e';

	printf(1, "5 page faults should have occurred.\nPress any key...\n");
	gets(input, 10);

	if (fork() == 0) {
		printf(1, "Child code running.\n");
		printf(1, "View statistics for pid %d, then press any key...\n", getpid());
		gets(input, 10);

		arr[13][0] = 'k';
		printf(1, "Page fault should have occurred in child proccess.\nPress any key to exit the child code.\n");
		gets(input, 10);

		exit();
	}
	else {
		wait();

		sbrk(-14 * PGSIZE);
		printf(1, "Deallocated all extra pages.\nPress any key to exit the father code.\n");
		gets(input, 10);
	}


#else
	char* arr[50];
	int i = 50;
	printf(1, "Testing default paging policy.\nNo page faults should occur.\n");
	for (i = 0; i < 50; i++) {
		arr[i] = sbrk(PGSIZE);
		printf(1, "arr[%d]=0x%x\n", i, arr[i]);
	}
#endif
	exit();
}

#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
	char *b  = 0;
	for (int i = 0; i < 27; i++) {
		printf(1, "Alloc page %d\n", i);
		char *a = sbrk(4096);
		if (i == 14)
			b = a;
		if (i == 15)
			*b = 'c';
	}

	*b = '0';
	printf(1, "Exiting..\n");
	exit();
	return 0;
}
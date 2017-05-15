#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
	for (int i = 0; i < 27; i++) {
		printf(1, "Alloc page %d\n", i);
		char *a = sbrk(4096);
		if (i % 2 == 1) {
			*a = 'a';
			*(a + 1) = 'b';
		}
	}
	printf(1, "Exiting..\n");
	exit();
	return 0;
}
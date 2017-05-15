#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
	for (int i = 0; i < 27; i++) {
		printf(1, "Alloc page %d\n", i);
		sbrk(4096);
	}
	printf(1, "Exiting..\n");
	exit();
	return 0;
}
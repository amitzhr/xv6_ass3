#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
	for (int i = 0; i < 15; i++)
		malloc(4096);
	printf(1, "Exiting..\n");
	exit();
	return 0;
}
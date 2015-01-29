#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sysfs.h"

#define VERBOSE 1
#define QUIET 0

int verbose = QUIET;

#define SYSFS_CLASS "/sys/class"
int main(int argc, char * argv[])
{
	char sysfs[120];
	char test[20];

	if (argc > 1) {
		sprintf(test,"%s",argv[1]);
	}
	else
	{
		printf("Enter test sysfs node: ");
		scanf("%19s",test);
	}
	printf("test: '%s'\n",test);

	sprintf(sysfs,SYSFS_CLASS "/%s",test);

	printf("sysfs: '%s'\n",sysfs);

	int H = test_sysfs_node(sysfs);

	printf("H: %d\n",H);

	if (H == 1)
		exit(0);
	else
		exit(1);
}

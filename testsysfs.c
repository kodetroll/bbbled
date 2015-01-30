#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sysfs.h"

// Usage: $0 <SYSFS NODE> <VERBOSE {0|1}>
#define VERBOSE 1
#define QUIET 0

int verbose = QUIET;

#define SYSFS_CLASS "/sys/class"
int main(int argc, char * argv[])
{
	int i =1;
	char sysfs[120];
	char test[20];

	if (argc > i)
		sprintf(test,"%s",argv[i++]);
	if (argc > i)
		verbose = atoi(argv[i++]);


	if (i < 2)
	{
		printf("Enter test sysfs node: ");
		scanf("%19s",test);
	}

	if (verbose)
		printf("test: '%s'\n",test);

	//sprintf(sysfs,SYSFS_CLASS "/%s",test);
	sprintf(sysfs,"%s",test);
	
	if (verbose)
		printf("sysfs: '%s'\n",sysfs);

	int H = test_sysfs_node(sysfs);

	if (verbose)
		printf("H: %d\n",H);
	else
		printf("%d",H);

	if (H == 1)
		exit(0);
	else
		exit(1);
}

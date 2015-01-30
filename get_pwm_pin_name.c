#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sysfs.h"

#define VERBOSE 1
#define QUIET 0

int verbose = QUIET;

int main(int argc, char * argv[])
{
	int i,pin;
	char name[120];

	i = 1;
	if (argc > i)
		pin = atoi(argv[i++]);

	if (verbose)
		printf("pin: '%d'\n",pin);

	i = get_pwm_pin_name(pin, name);

	if (verbose)
		printf("name: '%s'\n",name);
	else
		printf("%s\n",name);

	exit(0);
}

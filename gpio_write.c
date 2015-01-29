/*************************************************************************
 * gpio_write.c - A c program to control the specified gpio pin state 
 * using sysfs from userspace on the Beagle Bone Black. To use:
 * 'setgpio <PIN#> <STATE>' Where: PIN# is the new style gpio pin number
 * (e.g. '44' for 'gpio44') and <STATE> is 0 or 1 for LOW or HIGH.
 *
 * (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: January 2015
 *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "sysfs.h"

#define VERBOSE 1
#define QUIET 0

int verbose = QUIET;

//#define UNEXPORT_ON_EXIT

int main(int argc, char * argv[])
{
	int pin, state, i;

	// Set default Pin # to use if one is not 
	// supplied on the command line.
	pin = 23;

	// Set the default pin state to use if one
	// is not supplied on the command line.
	state = 1;

	// Start with debugging set to quiet
	verbose = QUIET;

	// If debugging, print the command line args
	if (verbose) {
		printf("argc: %d\n",argc);
		for (i=0;i<argc;i++)
			printf("argv[%d]: '%s'\n",i,argv[i]);
	}

	// if at least one arg is supplied, use it as
	// a pin number. Note, no attempt is made to
	// verify that the argument is valid for use 
	// with atoi()
	if (argc > 1)
		pin = atoi(argv[1]);

	// If a second arg is supplied, then use it as 
	// the pin state. Note, no attempt is made to
	// verify that the argument is valid for use 
	// with atoi()
	if (argc > 2)
		state = atoi(argv[2]);

	// If debugging, show the pin# and state.
	if (verbose) {
		printf("pin: '%d'\n",pin);
		printf("state: '%d'\n",state);
	}

	// Check if gpio pin is already exported, if not, export it
	if (gpio_is_exported(pin) == IS_EXPORTED) {
		if (verbose)
			printf("pin '%d' already exported!\n",pin);
	} else {
		// Pin was not exported, so we Export it!
		if (verbose)
			printf("Exporting pin '%d'!\n",pin);
		if (gpio_export(pin) < ERROR_OK) {
			printf("Error exporting pin '%d'\n",pin);
			exit(1);
		}
	}

	// Set the specified pin direction to 'out'
	if (gpio_write_dir(pin,OUT) < ERROR_OK) {
		printf("Error setting pin '%d' direction\n",pin);
		exit(1);
	}
    
	// Write desired value to pin
	if (gpio_write(pin,state) < ERROR_OK) {
		printf("Error writing pin '%d'\n",pin);
		exit(1);
	}
   
#ifdef UNEXPORT_ON_EXIT
	
	// Check if gpio pin is already exported, if so, unmap
	if (gpio_is_exported(pin) != IS_EXPORTED) {
		if (verbose)
			printf("pin '%d' already unexported!\n",pin);
	} else {
		if (verbose)
			printf("Un-exporting pin '%d'!\n",pin);
		if (gpio_unexport(pin) < ERROR_OK) {
			printf("Error unexporting pin '%d'\n",pin);
			exit(1);
		}
	}
#endif

	exit(0);
}


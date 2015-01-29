/*************************************************************************
 * gpio_test.c - A c program to test controlling (writing/reading) gpio 
 * pins using sysfs from userspace on the Beagle Bone Black.
 *
 * (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: January 2015
 *
 * TO control a GPIO Pin via sysfs:
 * 1) Export the pin: echo PIN# > /sys/class/gpio/export
 * 2) To set value: echo VALUE > /sys/class/gpio/gpioPIN#/value
 * 3) To read value: cat /sys/class/gpio/gpioPIN#/value
 * 4) Unexport the pin: echo PIN# > /sys/class/gpio/unexport
 *
 * This program will set dir to input, read the specified pin, 
 * set dir to output, set then reset the output, then read the pin.
 * 
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "sysfs.h"

//#define UNEXPORT_ON_EXIT

int main(int argc, char * argv[])
{
	int pin, state, i, val;

	// Set default Pin # to use if one is not 
	// supplied on the command line.
	pin = 23;

	// Set the default pin state to use if one
	// is not supplied on the command line.
	state = 1;

	// Start with debugging set to quiet
	verbose = QUIET;
	//verbose = VERBOSE;

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
		printf("pin '%d' already exported!\n",pin);
	} else {
		// Export
		printf("Exporting pin '%d'!\n",pin);
		if (gpio_export(pin) < ERROR_OK) {
			printf("Error exporting pin '%d'\n",pin);
			exit(1);
		}
	}
	
	// Set the specified pin direction to 'out'
	printf("Setting pin '%d' dir to IN!\n",pin);
	if (gpio_write_dir(pin,IN) < ERROR_OK) {
		printf("Error setting pin '%d' direction\n",pin);
		exit(1);
	}
    
	printf("Reading pin '%d' value!\n",pin);
	val = gpio_read(pin);

	printf("Pin '%d': %d!\n",pin,val);
	
	// Set the specified pin direction to 'out'
	printf("Setting pin '%d' dir to OUT!\n",pin);
	if (gpio_write_dir(pin,OUT) < ERROR_OK) {
		printf("Error setting pin '%d' direction\n",pin);
		exit(1);
	}

	// Write desired value to pin
	printf("Writing '%d' to pin '%d'!\n",state,pin);
	if (gpio_write(pin,state) < ERROR_OK) {
		printf("Error writing pin '%d'\n",pin);
		exit(1);
	}

	//verbose = VERBOSE;
    
	printf("Reading pin '%d' value!\n",pin);
	val = gpio_read(pin);

	printf("Pin '%d': %d!\n",pin,val);
	
#ifdef UNEXPORT_ON_EXIT
	
	// Check if gpio pin is already exported, if so, unmap
	printf("Checking pin pin '%d' for Unexport!\n",pin);
	if (gpio_is_exported(pin) != IS_EXPORTED) {
		printf("pin '%d' already unexported!\n",pin);
	} else {
		printf("Un-exporting pin '%d'!\n",pin);
		if (gpio_unexport(pin) < ERROR_OK) {
			printf("Error unexporting pin '%d'\n",pin);
			exit(1);
		}
	}
#endif

	printf("Exiting!\n");

	exit(0);
}


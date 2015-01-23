/*************************************************************************
 * gpio.c - A c program to test controlling gpio pin state using sysfs 
 * from userspace on the Beagle Bone Black
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
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "sysfs.h"

//#define UNEXPORT_ON_EXIT

int main(int argc, char * argv[])
{
    int pin, state, i;

    pin = 23;
    state = 1;

    VERBOSE=0;

    if (VERBOSE) {
        printf("argc: %d\n",argc);
        for (i=0;i<argc;i++)
            printf("argv[%d]: '%s'\n",i,argv[i]);
    }

    if (argc > 1)
        pin = atoi(argv[1]);
    if (argc > 2)
        state = atoi(argv[2]);

    if (VERBOSE) {
        printf("pin: '%d'\n",pin);
        printf("state: '%d'\n",state);
    }
	
	// Check if gpio pin is already exported, if not, export it
	if (gpio_is_exported(pin) == 0) {
		if (VERBOSE)
			printf("pin '%d' already exported!\n",pin);
	} else {
		// Export
		if (VERBOSE)
			printf("Exporting pin '%d'!\n",pin);
		if (gpio_export(pin) < 0) {
			printf("Error exporting pin '%d'\n",pin);
			exit(1);
		}
    }
	
    if (gpio_write(pin,OUT) < 0) {
        printf("Error setting pin '%d' direction\n",pin);
        exit(1);
    }
    
	// Write desired value to pin
    if (gpio_write(pin,state) < 0) {
        printf("Error writing pin '%d'\n",pin);
        exit(1);
    }

    int l = gpio_read(pin,state);

#ifdef UNEXPORT_ON_EXIT
	
	// Check if gpio pin is already exported, if so, unmap
	if (gpio_is_exported(pin) == 0) {
		if (VERBOSE)
			printf("pin '%d' already exported!\n",pin);
	} else {
		if (VERBOSE)
			printf("Exporting pin '%d'!\n",pin);
		if (gpio_unexport(pin) < 0) {
			printf("Error unexporting pin '%d'\n",pin);
			exit(1);
		}
    }
#endif

    exit(0);
}


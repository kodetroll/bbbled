/*************************************************************************
 * testgpio.c - A c program to test gpio pin state using sysfs from
 * userspace.
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

//int VERBOSE = 0;

int main(int argc, char * argv[])
{
    int pin, state, i;

    pin = 23;
    state = 1;

    VERBOSE=1;

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
//        printf("gpio: '%s'\n",gpio);
        printf("pin: '%d'\n",pin);
        printf("state: '%d'\n",state);
    }

    if (gpio_export(pin) < 0) {
        printf("Error exporting pin '%d'\n",pin);
        exit(1);
    }

    if (gpio_write(pin,state) < 0) {
        printf("Error writing pin '%d'\n",pin);
        exit(1);
    }

    if (gpio_unexport(pin) < 0) {
        printf("Error unexporting pin '%d'\n",pin);
        exit(1);
    }

    exit(0);
}


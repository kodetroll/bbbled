/*************************************************************************
 * pwm.c - A c program to test setting pwm pin state using sysfs from
 * userspace on the Beagle Bone Black
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

int main(int argc, char * argv[])
{
    int pin, state, i;

    pin = 23;
    duty = 1;
    period = 1;

    VERBOSE=1;

    if (VERBOSE) {
        printf("argc: %d\n",argc);
        for (i=0;i<argc;i++)
            printf("argv[%d]: '%s'\n",i,argv[i]);
    }

    if (argc > 1)
        pin = atoi(argv[1]);
    if (argc > 2)
        duty = atoi(argv[2]);
    if (argc > 3)
        period = atoi(argv[3]);

    if (VERBOSE) {
        printf("pin: '%d'\n",pin);
        printf("duty: '%d'\n",duty);
        printf("period: '%d'\n",period);
    }


    exit(0);
}


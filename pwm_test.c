/*************************************************************************
 * pwm_test.c - A c program to test controlling (writing/reading) pwm
 * pins using sysfs from userspace on the Beagle Bone Black.
 *
 * (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: January 2015
 *
 * TO control a GPIO Pin via sysfs:
 * 1) Find capemgr # N
 * 2) Find ocp # O
 * 3) request am3559_pwm from capemgr.N/slots 'echo am33xx_pwm > $SLOTS'
 * 4) request pwm pin from capemgr.N/slots 'echo ${PWMPIN} > $SLOTS'
 * 5) Find pwm pin from ocp.O
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

int main(int argc, char * argv[])
{
	int pin, state, i, val;
	char name[24];

	// Start with debugging set to quiet
	verbose = QUIET;

	// Set default Pin # to use if one is not 
	// supplied on the command line.
	pin = 23;
	
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
		
	// If debugging, show the pin# and state.
	if (verbose) {
		printf("pin: '%d'\n",pin);
	}

	if (get_pwm_pin_name(pin,name) < ERROR_OK) {
		printf("Error getting pwm pin name!\n");
		exit(1);
	}

	printf("Name: '%s'\n",name);
	
	int cm = get_capemgr_num();
	
	printf("Cape Num: '%d'\n",cm);

	int ocp = get_ocp_num();
	
	printf("OCP Num: '%d'\n",ocp);

	if (request_pwm(cm) < ERROR_OK) {
		printf("Error requesting pwm functions!\n");
		exit(1);
	}

	if (request_pwm_pin(cm,name) < ERROR_OK) {
		printf("Error requestuing pwm pin name!\n");
		exit(1);
	}
	
//	verbose = VERBOSE;	
	
	int pwm_pin = get_pwm_pin_num(name);
	
	printf("pwm_pin: '%d'\n",pwm_pin);
	
	long period = 1000000;
	long duty = 990000;
	
	printf("Setting period to '%ld' on '%s'\n",period,name);
	
	if (pwm_write_period(name,period) < ERROR_OK) {
		printf("Error setting pwm period for '%s'!\n",name);
		exit(1);
	}
	
	printf("Setting duty to '%ld' on '%s'\n",period,name);
	
	if (pwm_write_duty(name,duty) < ERROR_OK) {
		printf("Error setting pwm duty for '%s'!\n",name);
		exit(1);
	}
	
	verbose = VERBOSE;	

	int dutycycle = 10; 	// in percent

	if (pwm_write_duty_cycle(name,dutycycle) < ERROR_OK) {
		printf("Error setting pwm duty cycle for '%s'!\n",name);
		exit(1);
	}

	verbose = QUIET;	

	period = pwm_read_period(name);

	printf("period: '%ld'\n",period);

	duty = pwm_read_duty(name);

	printf("duty: '%ld'\n",duty);

	printf("Exiting!\n");

	exit(0);
}


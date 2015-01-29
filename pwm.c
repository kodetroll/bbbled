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

#define VERBOSE 1
#define QUIET 0

int init_pwm(char * name);
int idle_pwm(char * name, int dutycycle);

int verbose = QUIET;

int init_pwm(char * name) 
{
	if (verbose)
		printf("Enumerating CapeMgr Number!\n");
	
	int cm = get_capemgr_num();
	
	if (verbose)
		printf("CapeMgr Num: '%d'\n",cm);

	if (verbose)
		printf("Enumerating OCP Number!\n");
	
	int ocp = get_ocp_num();
	
	if (verbose)
		printf("OCP Num: '%d'\n",ocp);

	if (verbose)
		printf("Requesting PWM (am35xx_pwm) functions!\n");
	
	if (request_pwm(cm) < ERROR_OK) {
		printf("Error requesting pwm functions!\n");
		return(ERROR);
	}

	if (verbose)
		printf("Requesting PWM Pin Function for Pin: '%s'!\n",name);

	if (request_pwm_pin(cm,name) < ERROR_OK) {
		printf("Error requesting pwm pin name!\n");
		return(ERROR);
	}
	
	if (verbose)
		printf("Enumerating PWM Pin Number for pin '%s'!\n",name);
	
	int pwm_pin = get_pwm_pin_num(name);
	
	if (verbose)
		printf("pwm_pin: '%d'\n",pwm_pin);

	return(pwm_pin);
}

int idle_pwm(char * name, int dutycycle)
{
	
	long period = 1000000;
	long duty = 990000;
	
	printf("Setting period to '%ld' on '%s'\n",period,name);
	
	if (pwm_write_period(name,period) < ERROR_OK) {
		printf("Error setting pwm period for '%s'!\n",name);
		return(ERROR);
	}
	
	printf("Setting duty to '%ld' on '%s'\n",duty,name);
	
	if (pwm_write_duty(name,duty) < ERROR_OK) {
		printf("Error setting pwm duty for '%s'!\n",name);
		return(ERROR);
	}
	
	if (dutycycle < 0)
		dutycycle = 10; 	// in percent

	if (pwm_write_duty_cycle(name,dutycycle) < ERROR_OK) {
		printf("Error setting pwm duty cycle for '%s'!\n",name);
		return(ERROR);
	}
	
	return(dutycycle);
}

int main(int argc, char * argv[])
{
    int pin, pwm_pin, i;

    pin = 23;
    long duty = 990000;
    long period = 1000000;
    char name[24];

    verbose = QUIET;

    if (verbose) {
        printf("argc: %d\n",argc);
        for (i=0;i<argc;i++)
            printf("argv[%d]: '%s'\n",i,argv[i]);
    }

	i = 1;
    if (argc > i)
        pin = atoi(argv[i++]);
    if (argc > i)
        duty = atol(argv[i++]);
    if (argc > i)
        period = atol(argv[i++]);
    if (argc > i)
        verbose = atoi(argv[i++]);

    if (verbose) {
        printf("pin: '%d'\n",pin);
        printf("duty: '%ld'\n",duty);
        printf("period: '%ld'\n",period);
        printf("verbose: '%d'\n",verbose);
    }

	if (verbose)
		printf("Calculating PWM Pin Name from GPIO Pin Number!\n");

	if (get_pwm_pin_name(pin,name) < ERROR_OK) {
		printf("Error getting pwm pin name!\n");
		exit(1);
	}

	if (verbose)
		printf("Name: '%s'\n",name);

	if ((pwm_pin = init_pwm(name)) < ERROR_OK) {
		printf("Error initializing pwm pin '%s'!\n",name);
		exit(1);
	}
	
	if ((idle_pwm(name, 0)) != ERROR_OK) {
		printf("Error setting pwm pin '%s' to idle!\n",name);
		exit(1);
	}
	
	if (verbose)
		printf("Setting period to '%ld' on '%s'\n",period,name);
	
	if (pwm_write_period(name,period) < ERROR_OK) {
		printf("Error setting pwm period for '%s'!\n",name);
		return(ERROR);
	}
	
	if (verbose)
		printf("Setting duty to '%ld' on '%s'\n",duty,name);
	
	if (pwm_write_duty(name,duty) < ERROR_OK) {
		printf("Error setting pwm duty for '%s'!\n",name);
		return(ERROR);
	}

    exit(0);
}


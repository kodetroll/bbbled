/*************************************************************************
 * fader.c - A c program to fade an LED back and forth using PWM 
 * pins using sysfs from userspace on the Beagle Bone Black.
 *
 * (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: January 2015
 *
 * This program will request pwm, then map the pwm pin. Then it will set
 * the period and duty cycle to starting values. Then it runs a pwm fade 
 * cycle with a specified delay. 
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

int init_pwm(char * name);
int idle_pwm(char * name, int dutycycle);

int init_pwm(char * name) 
{
	if (verbose)
		printf("Enumerating CapeMgr Number!\n");
	
	int cm = get_capemgr_num();
	
	if (verbose)
		printf("CapeMgr Num: '%d'\n",cm);

//	if (verbose)
//		printf("Enumerating OCP Number!\n");
//	
//	int ocp = get_ocp_num();
//	
//	if (verbose)
//		printf("OCP Num: '%d'\n",ocp);

	if (verbose)
		printf("Requesting PWM (am35xx_pwm) functions!\n");
	
	if (request_pwm(cm) < ERROR_OK) {
		printf("Error requesting pwm functions!\n");
		return(ERROR);
	}

	if (verbose)
		printf("Requesting PWM Pin Function for Pin: '%s'!\n",name);

	if (request_pwm_pin(name) < ERROR_OK) {
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
	
	if (dutycycle < 0)
		dutycycle = 10; 	// in percent

	if (verbose)
		printf("Setting dutycycle to '%d' on '%s'\n",dutycycle,name);

	if (pwm_write_duty_cycle(name,dutycycle) < ERROR_OK) {
		printf("Error setting pwm duty cycle for '%s'!\n",name);
		return(ERROR);
	}

	if (verbose)
		printf("Idle set on '%s'\n",name);
	
	return(0);
}

int main(int argc, char * argv[])
{
	int pin, pwm_pin, dutycycle, i, val, delay;
	char name[24];

	// Start with debugging set to quiet
	verbose = QUIET;

	// Set default Pin # to use if one is not 
	// supplied on the command line.
	pin = 23;
	
	delay = 100000;
	
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
	i = 1;
	if (argc > i)
		pin = atoi(argv[i++]);
		
	if (argc > i)
		delay = atoi(argv[i++]);
	
	if (argc > i)
		verbose = atoi(argv[i++]);

	if (verbose) {
		printf("GPIO pin #: '%d'\n",pin);
		printf("delay: '%d'\n",delay);
	}

	if (verbose)
		printf("Calculating PWM Pin Name from GPIO Pin Number!\n");

	if (get_pwm_pin_name(pin,name) < ERROR_OK) {
		printf("Error getting pwm pin name!\n");
		exit(1);
	}

	if (verbose)
		printf("Name: '%s'\n",name);

	if (verbose)
		printf("Initializing PWM on '%s'\n",name);

	if ((pwm_pin = init_pwm(name)) < ERROR_OK) {
		printf("Error initializing pwm pin '%s'!\n",name);
		exit(1);
	}
	
	if (verbose)
		printf("Setting idle_pwm dutycycles on '%s'\n",name);

	if ((idle_pwm(name, dutycycle)) != ERROR_OK) {
		printf("Error setting pwm pin '%s' to idle!\n",name);
		exit(1);
	}

	if (verbose)
		printf("Setting pwm run ON on '%s'\n",name);

	if (pwm_pin_run(name) < ERROR_OK) {
		printf("Error setting pwm run to ON for '%s'!\n",name);
		exit(1);
	}

	printf("Running Fader!\n");
	while(1) {
		for (dutycycle=0;dutycycle<100;dutycycle++) {
			if (pwm_write_duty_cycle(name,dutycycle) < ERROR_OK)
				printf("Error setting pwm duty cycle for '%s'!\n",name);
			usleep(delay);
		}
		for (dutycycle=100;dutycycle>0;dutycycle--) {
			if (pwm_write_duty_cycle(name,dutycycle) < ERROR_OK)
				printf("Error setting pwm duty cycle for '%s'!\n",name);
			usleep(delay);
		}
	}

	printf("Exiting!\n");

	exit(0);
}


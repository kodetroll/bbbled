/*************************************************************************
 * pwm_setrgb.c - A c program to set the PWM channel RGB values of an 
 * RGB LED on a Beagle Bone Black board using the sysfs on the pwm 
 * subsystem.
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
#include "colors.h"

#define VERBOSE 1
#define QUIET 0

// Map the LED Colors to GPIO pins. These values are converted to
// sysfs pin mappings in the sysfs module. 
#define REDLED 23
#define BLULED  2
#define GRNLED 50

// Gamma correction
#define RGAM 5
#define GGAM 4
#define BGAM 2

// This defines that the PWM channel is driven low to turn ON the RGB
// LED (Common Anode).
#define LED_IS_COMMON_ANODE	

int verbose = QUIET;

int init_pwm(char * name);
int idle_pwm(char * name, int dutycycle);
int init_pin(int pin);
int set_led(int pin, unsigned char value);
int set_color(unsigned char red,unsigned char green,unsigned char blue);

int init_pwm(char * name) 
{
	if (verbose)
		printf("Enumerating CapeMgr Number!\n");
	
	int cm = get_capemgr_num();
	
	if (verbose)
		printf("CapeMgr Num: '%d'\n",cm);

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

int init_pin(int pin) {

	int pwm_pin, dutycycle;
	char name[24];
		
	dutycycle = 99;
	if (verbose)
		printf("Calculating PWM Pin Name from GPIO Pin Number!\n");

	if (get_pwm_pin_name(pin,name) < ERROR_OK) {
		printf("Error getting pwm pin name!\n");
		return(ERROR);
	}

	if (verbose)
		printf("Name: '%s'\n",name);

	if (verbose)
		printf("Initializing PWM on '%s'\n",name);

	if ((pwm_pin = init_pwm(name)) < ERROR_OK) {
		printf("Error initializing pwm pin '%s'!\n",name);
		return(ERROR);
	}
	
	if (verbose)
		printf("Setting idle_pwm dutycycles on '%s'\n",name);

	if ((idle_pwm(name, dutycycle)) != ERROR_OK) {
		printf("Error setting pwm pin '%s' to idle!\n",name);
		return(ERROR);
	}

	if (verbose)
		printf("Setting pwm run ON on '%s'\n",name);

	if (pwm_pin_run(name) < ERROR_OK) {
		printf("Error setting pwm run to ON for '%s'!\n",name);
		return(ERROR);
	}
	
	return(ERROR_OK);
}

int set_led(int pin, unsigned char value)
{
	int dutycycle = value * 100 / 255;
	char name[24];
		
	if (verbose)
		printf("Calculating PWM Pin Name from GPIO Pin Number!\n");

	if (get_pwm_pin_name(pin,name) < ERROR_OK) {
		printf("Error getting pwm pin name!\n");
		return(ERROR);
	}
	
#ifdef LED_IS_COMMON_ANODE	
	dutycycle = (100 - dutycycle);
#endif
	
	if (pwm_write_duty_cycle(name,dutycycle) < ERROR_OK) {
		printf("Error setting pwm duty cycle for '%s'!\n",name);
		return(ERROR);
	}
	return(ERROR_OK);
}

int set_color(unsigned char r,unsigned char g,unsigned char b) 
{
	unsigned char red,green,blue;
	
	if (verbose)
		printf("Raw R G B: 0x%02x 0x%02x 0x%02x\n",r,g,b);

	red = r / RGAM;
	green = g / GGAM;
	blue = b / BGAM;

	if (verbose)
		printf("Gamma R G B: 0x%02x 0x%02x 0x%02x\n",red,green,blue);
	
	if (verbose)
		printf("Setting Red LED (gpio%d) to '0x%02x'\n",REDLED,red);
		
	if (set_led(REDLED,red)) {
		printf("Error setting color value for RED LED ('gpio%d')!\n",REDLED);
		return(ERROR);
	}

	if (verbose)
		printf("Setting Green LED (gpio%d) to '0x%02x'\n",GRNLED,green);

	if (set_led(GRNLED,green)) {
		printf("Error setting color value for GRN LED ('gpio%d)'!\n",GRNLED);
		return(ERROR);
	}

	if (verbose)
		printf("Setting Blue LED (gpio%d) to '0x%02x'\n",BLULED,blue);

	if (set_led(BLULED,blue)) {
		printf("Error setting color value for BLU LED ('gpio%d')!\n",BLULED);
		return(ERROR);
	}

	return(ERROR_OK);
}

int main(int argc, char * argv[])
{
	int pin, pwm_pin, dutycycle, i, val, delay;
	char tmpval[24];
	unsigned char red,green,blue;

	// Start with debugging set to quiet
	verbose = QUIET;

	// Set default Pin # to use if one is not 
	// supplied on the command line.
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
		red = atoi(argv[i++]);

	if (argc > i)
		green = atoi(argv[i++]);

	if (argc > i)
		blue = atoi(argv[i++]);
		
	if (argc > i)
		verbose = atoi(argv[i++]);

	if (verbose)
		printf("R G B: 0x%02x 0x%02x 0x%02x\n",red,green,blue);

	if (verbose)
		printf("Initializing RED LED pin 'gpio%d'!\n",REDLED);
		
	if (init_pin(REDLED) != ERROR_OK) {
		printf("Error initializing RED LED pin 'gpio%d'!\n",REDLED);
		exit(1);
	}
	
	if (verbose)
		printf("Initializing GRN LED pin 'gpio%d'!\n",GRNLED);

	if (init_pin(GRNLED) != ERROR_OK) {
		printf("Error initializing GRN LED pin 'gpio%d'!\n",GRNLED);
		exit(1);
	}

	if (verbose)
		printf("Initializing BLU LED pin 'gpio%d'!\n",BLULED);

	if (init_pin(BLULED) != ERROR_OK) {
		printf("Error initializing BLU LED pin 'gpio%d'!\n",BLULED);
		exit(1);
	}

	if (set_color(red,green,blue) != ERROR_OK) {
		printf("Error setting RGB: 0x%02x 0x%02x 0x%02x\n",red,green,blue);
		exit(1);
	}
		
	if (verbose)
		printf("Exiting!\n");

	exit(0);
}


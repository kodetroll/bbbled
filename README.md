Beagle Bone Black LED/GPIO Scripts and C programs using sysfs.

Not very sophisticated. Certainly not idiot proof. This is a collection of
a series of bash scripts and c programs that will control GPIO (read/write)
and PWM (duty/period) pins on the BeagleBone Black board from circuitco using
the sysfs method.

I made a simple attempt to abstract the sysfs calls in a single module:
sysfs.c, with a header (sysfs.h) for the c programs. Bash scripts have
functions embedded in the functions.sh shell script fragment. Look through
the sources for more information.

To build the c program examples, just type 'make'

GPIO control based on info from http://www.circuidipity.com/bbb-led.html, PWM
control based on multiple sources of information.

Note; this library currently requires the beaglebone capemanager application, 
implying kernel versions no later than 3.8.


The Tools/examples are:

Bash Scripts

 * blink.sh - Toggles specified GPIO pin at defined rate (.5 Hz)
 * colors2.sh - Cycles through colors on RGB LED using GPIO calls.
 * color.sh - Sets color of RGB LED (using GPIO calls) by name.
 * colors.sh - Cycles through colors on RGB LED using GPIO calls.
 * digitalread.sh - Reads specified GPIO pin value and prints to screen
 * digitalwrite.sh - Write specified value to specified GPIO Pin
 * fade.sh - PWM Up/Down cycle (fade) of LED on specified PWM pin.
 * functions.sh - Function library
 * getdirection.sh - Reads direction register and prints to screen
 * gpio-blink.sh - blinks specified GPIO pin.
 * pinname.sh - returns a string with the sysfs path for the specified GPIO pin
 * pwm.sh - Sets perdio and duty of specified PWM pin.
 * pwmtest.sh - Examples of how to init, call and control PWM functions.
 * rnd.sh - generates a single random signed integer.
 * setdirection.sh - Sets direction register of specified GPIO PIN
 * setduty.sh - Sets duty cycle of specified PWM pin.
 * strobe.sh - toggles twice the specified GPIO pin value
 * toggle.sh - toggles once, the specified GPIO pin value
 * unxport.sh - unexports the specified GPIO pin
 * usrled.sh - sets or resets the specified usrLED value
 * xport.sh - exports the specified GPIO pin

C Programs
 * fader.c - Runs a PWM up/down cycle (fader) on specified pin.
 * gpio_test.c - Examples of calling GPIO pin functions in sysfs module.
 * gpio_write.c - writes a value to specified GPIO pin.
 * pwm.c - writes period and duty values to specified PWM pin.
 * pwm_test.c - Examples of calling PWM pin functions in sysfs module.
 * sysfs.c - sysfs functions module 
 * test2.c - simple sysfs node writing example.
 * testsysfs.c - tests whether sysfs nodes exists. 
 * usrled.c - Controls usr LED states (does not use the sysfs module).



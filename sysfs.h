/*************************************************************************
 * sysfs.h - A simple c library to implement gpio pin control using sysfs
 * from userspace on the Beagle Bone Black.
 *
 * (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: January 2015
 *
 *************************************************************************/

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <fcntl.h>

//	/sys/class/leds/beaglebone\:green\:${LED}/trigger
//extern char gpio[] = "/sys/class/gpio";
//extern char sysfs[120];
//extern char valset[20];

extern int VERBOSE;
int write_sysfs_node(char * sysfs, char * value);
int gpio_export(int pin);
int gpio_unexport(int pin);
int gpio_write(int pin, int state);


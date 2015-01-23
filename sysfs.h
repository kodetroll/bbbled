/*************************************************************************
 * sysfs.h - A simple c library to implement gpio pin control using sysfs
 * from userspace on the Beagle Bone Black.
 *
 * (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: January 2015
 *
 *************************************************************************/


#ifndef SYSFS_H
#define SYSFS_H

#ifdef  __cplusplus
extern "C" {
#endif

extern int VERBOSE;

#define HIGH 1
#define LOW 0
#define ON 1
#define OFF 0

#define OUT 1
#define IN 0

int test_sysfs_node(char * sysfs);
int read_sysfs_node(char * sysfs, char * buffer);
int write_sysfs_node(char * sysfs, char * value);
int gpio_export(int pin);
int gpio_unexport(int pin);
int gpio_write_dir(int pin, int state);
int gpio_write(int pin, int state);

#endif	// SYSFS_H

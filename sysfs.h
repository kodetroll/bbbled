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

int test_sysfs_node(char * sysfs);
int write_sysfs_node(char * sysfs, char * value);
int gpio_export(int pin);
int gpio_unexport(int pin);
int gpio_write(int pin, int state);

#endif	// SYSFS_H

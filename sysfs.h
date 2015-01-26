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

#define VERBOSE 1
#define QUIET 0

#define HIGH 1
#define LOW 0
#define ON 1
#define OFF 0

#define OUT 1
#define IN 0

#define TEST_USES_STAT

#define PIN_BANK_SIZE 32

#define IS_EXPORTED 0

#define SYSFS_CLASS "/sys/class"
#define SYSFS_GPIO "/sys/class/gpio"
#define SYSFS_DEV "/sys/devices"
#define SYSFS_OCP "/sys/devices/ocp"
#define SYSFS_CAPE "/sys/devices/capemgr"


#define ERROR_OK 0

/* Parameter to control debug printing */
extern int verbose;


/* Function to test whether sysfs node exists. Returns 0 for 
 * available, -1 for does not exist. Can use stat() or access()
 * for the test. Defaults to access(), hoever, defining 
 * TEST_USES_STAT above will force a compile with stat()
 * instead.
 */
int test_sysfs_node(char * sysfs);

/* Function to read string from specified sysfs path. String
 * value of node at path 'sysfs' will be returned in the buffer
 * pointed to by 'buffer'. Return value is the size of the buffer.
 * -1 is returned for errors. 
 */
int read_sysfs_node(char * sysfs, char * buffer);

/* Function to write specified string value to the sysfs node at
 * the specified sysfs path. Return is 0 for OK, -1 for error during
 * read or open.
 */
int write_sysfs_node(char * sysfs, char * value);

/* Function to export specified GPIO pin via the mapper. Return is 
 * -1 for error, 0 for OK. Availibility or existance of the sysfs
 * node created by the export is not tested before hand.
 */
int gpio_export(int pin);

/* Function un-export specified GPIO pin via the mapper. Return is 
 * -1 for error, 0 for OK. This works, but seems to lock further use
 * of the gpio pin.
 */
int gpio_unexport(int pin);

/* Function to set the direction register for the specified pin 
 * by writing to the '/direction' branch of the sysfs node. 
 * Value is integer 1 for OUTPUT, 0 for INPUT. Return is -1 for
 * error during write or open of sysfs node, 0 for OK.
 */
int gpio_write_dir(int pin, int state);

/* Function to set the value of the specified pin by writing to 
 * the '/value' branch of the sysfs node. Value is integer 1 
 * for 1 and 0 for 0. Return is -1 for error during write or 
 * open of sysfs node, 0 for OK.
 */
int gpio_write(int pin, int state);

/* Function to read the value of direction register for the 
 * specified pin by reading from the '/direction' branch of 
 * the sysfs node. Value returned is integer 1 for OUTPUT, 
 * 0 for INPUT. Return is -1 for error during write or open 
 * of sysfs node.
 */
int gpio_read_dir(int pin);

/* Function to read the value of the specified pin by reading 
 * from the '/value' branch of the sysfs node. Value returned 
 * is either 1 or 0 representing the values '0' and '1' read
 * from the node. -1 is returned for errors during write or 
 * open of sysfs node.
 */
int gpio_read(int pin);


int get_pin_bank(int pin);

int get_old_pin_num(int pin);

int get_old_pin_name(int pin, char* name);

int get_pin_conn(int pin);

int get_pin_num(int pin);

int get_pwm_pin_name(int pin, char* name);

/* Function to search and return the current capemgr number
 * expressed in the '/sys/devices' branch of sysfs. 
 * Value returned is enumerated value after the '/capemgr.' 
 * sysfs node. -1 is returned for errors during write or 
 * open of sysfs node.
 */
int get_capemgr_num(void);

/* Function to search and return the current ocp number
 * expressed in the '/sys/devices' branch of sysfs. 
 * Value returned is enumerated value after the '/ocp.' 
 * sysfs node. -1 is returned for errors during write or 
 * open of sysfs node.
 */
int get_ocp_num(void);
 
/* Function to search and return the current ocp number
 * expressed in the '/sys/devices' branch of sysfs. 
 * Value returned is enumerated value after the '/ocp.' 
 * sysfs node. -1 is returned for errors during write or 
 * open of sysfs node.
 */
int get_pwm_num(int ocpnum,int pin);

/* Function to request PWM from the '/slots' node of the 
 * specified capmgr sysfs node. -1 is returned for 
 * errors during write or open of sysfs node.
 */
int request_pwm(int capemgrnum);

/* Function to read the duty cycle value of the specified pin 
 * by reading from the '/duty' branch of the sysfs pwm node. 
 * Value returned is timer value representing the duty cycle
 * based on the current value of 'period'. -1 is returned for 
 * errors during write or open of sysfs node.
 */
int pwm_read_duty(int pin);

#endif	// SYSFS_H

/*************************************************************************
 * sysfs.c - A simple c library to implement gpio pin control using sysfs
 * from userspace on the Beagle Bone Black.
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
#include <sys/types.h>
#include <dirent.h>

#include "sysfs.h"

//	/sys/class/gpio/...

//char gpio[] = "/sys/class/gpio";
char sysfs[120];
char valset[20];

int debug = OFF;


/* Function to test whether sysfs node exists. Returns ERROR_OK
 * (0) for available, ERROR (-1) for does not exist. Can use
 * either stat() or access() for the test (see defines).
 * Defaults to access(), hoever, defining TEST_USES_STAT above
 * will force a compile with stat() instead.
 */
int test_sysfs_node(char * sysfs)
{
#ifdef TEST_USES_STAT
	struct stat   buffer;
#endif

	if (debug >= DEBUG_VERB_HI) {
		printf("test_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
    }

#ifdef TEST_USES_STAT

	return (stat (sysfs, &buffer) == ERROR_OK);

#else

	if (access(sysfs, F_OK ) == ERROR) {
		if (debug >= DEBUG_VERB_LO) {
			printf("test_sysfs_node: ERROR\n");
		}
		return(ERROR);
	}

	if (debug >= DEBUG_VERB_LO) {
		printf("test_sysfs_node: ERROR_OK\n");
	}
	return(ERROR_OK);
#endif

}

/* Function to read string from specified sysfs path. String
 * value of node at path 'sysfs' will be returned in the buffer
 * pointed to by 'buffer'. Return value is the size of the buffer.
 * ERROR (-1) is returned for errors.
 */
int read_sysfs_node(char * sysfs, char * buffer)
{
    int fd,len;
	char buf[50];

    if (debug >= DEBUG_VERB_HI) {
		printf("read_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
    }

#ifdef SYSFS_READ_USES_FCNTL
    fd = open(sysfs, O_RDONLY);
    if (fd < ERROR_OK) {
        fprintf(stderr, "Error opening node '%s'\n",sysfs);
        return(ERROR);
    }
    len = read (fd, &buf, sizeof(buf));
    close(fd);
#else
    FILE* f = fopen(sysfs, "w");
    if (f == NULL) {
        fprintf(stderr, "Error writing node '%s'\n",sysfs);
        return(ERROR);
    }

    len = fread(buf,1,sizeof(buf),f);
    fclose(f);
#endif

	strncpy(buffer,buf,strlen(buf)-1);

    if (debug >= DEBUG_VERB_MED) {
		printf("buf: '%s'\n",buf);
	}
	if (debug >= DEBUG_VERB_LO) {
		printf("read_sysfs_node: Return\n");
		printf("read_sysfs_node: buffer: '%s'\n",buffer);
		printf("read_sysfs_node: len: '%d'\n",len);
	}
    return(len);
}

/* Function to write specified string value to the sysfs node at
 * the specified sysfs path. Return is ERROR_OK (0) for OK, ERROR_OK
 * (-1) for error during read or open.
 */
int write_sysfs_node(char * sysfs, char * value)
{
    int fd;

    if (debug >= DEBUG_VERB_HI) {
		printf("write_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
        printf("value: '%s'\n",value);
    }

#ifdef USE_FCNTL
    fd = open(sysfs, O_WRONLY);
    if (fd < ERROR_OK) {
        fprintf(stderr, "Error writing node '%s'\n",sysfs);
        return(ERROR);
    }
    write (fd, &value, strlen(value));
    close(fd);
#else
    FILE* f = fopen(sysfs, "w");
    if (f == NULL) {
        fprintf(stderr, "Error writing node '%s'\n",sysfs);
        return(ERROR);
    }

    fprintf(f, "%s", value);
    fprintf(f, "\n");
    fclose(f);
#endif
    return(ERROR_OK);
}

/* Function to test whether specified GPIO pin is currently exported
 * via the mapper. Return is ERROR (-1) for not exported and ERROR_OK
 * (0) for exported. Availibility or existance of the sysfs
 * node created by the export is not tested before hand. Uses the
 * test_sysfs_node() function.
 */
int gpio_is_exported(int pin)
{
    if (debug >= DEBUG_VERB_HI) {
		printf("gpio_is_exported\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d",pin);

    if (test_sysfs_node(sysfs) == 0) {
		return(ERROR);
	}
	return(ERROR_OK);
}

/* Function to export specified GPIO pin via the mapper. Return is
 * ERROR_OK (0) for OK, ERROR (-1) for error. Availibility or
 * existance of the sysfs node created by the export is not tested
 * before hand.
 */
int gpio_export(int pin)
{
    if (debug >= DEBUG_VERB_HI) {
		printf("gpio_export\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/export");

    sprintf(valset,"%d",pin);

    if (debug >= DEBUG_VERB_MED) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error exporting pin '%d' to node '%s/export'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    return(ERROR_OK);
}

/* Function un-export specified GPIO pin via the mapper. Return is
 * ERROR_OK (0) for OK, ERROR (-1) for error. This works, but seems
 * to lock further use of the gpio pin.
 */
int gpio_unexport(int pin)
{
    if (debug >= DEBUG_VERB_HI) {
		printf("gpio_unexport\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/unexport");
    sprintf(valset,"%d",pin);

    if (debug >= DEBUG_VERB_MED) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error unexporting pin '%d' to node '%s/unexport'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    return(ERROR_OK);
}

/* Function to set the direction register for the specified pin
 * by writing to the '/direction' branch of the sysfs node.
 * Value is integer 1 for OUTPUT, 0 for INPUT. Return is ERROR_OK
 * (0) for OK, ERROR (-1) for error during write or open of sysfs
 * node.
 */
int gpio_write_dir(int pin, int state)
{
    if (debug >= DEBUG_VERB_HI) {
		printf("gpio_write_dir\n");
        printf("pin: '%d'\n",pin);
        printf("state: '%d'\n",state);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/direction",pin);
	if (state == 1)
		sprintf(valset,"out");
	else
		sprintf(valset,"in");

    if (debug >= DEBUG_VERB_MED) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing to pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    return(ERROR_OK);
}

/* Function to set the value of the specified pin by writing to
 * the '/value' branch of the sysfs node. Value is integer 1
 * for 1 and 0 for 0. Return is ERROR (-1) for error during write
 * or open of sysfs node, ERROR_OK (0) for OK.
 */
int gpio_write(int pin, int state)
{
    if (debug >= DEBUG_VERB_HI) {
		printf("gpio_write\n");
        printf("pin: '%d'\n",pin);
        printf("state: '%d'\n",state);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/value",pin);

    sprintf(valset,"%d",state);

    if (debug >= DEBUG_VERB_MED) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing to pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    return(ERROR_OK);
}

/* Function to read the value of direction register for the
 * specified pin by reading from the '/direction' branch of
 * the sysfs node. Value returned is integer 1 for OUTPUT,
 * 0 for INPUT. Return is ERROR (-1) for error during write
 * or open of sysfs node, ERROR_OK (0) for OK.
 */
int gpio_read_dir(int pin)
{
	int state,len;
    if (debug >= DEBUG_VERB_HI) {
		printf("gpio_read_dir\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/direction",pin);

    if (debug >= DEBUG_VERB_MED) {
        printf("sysfs: '%s'\n",sysfs);
    }

	memset(valset,0x00,sizeof(valset));

    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    if (debug >= DEBUG_VERB_MED) {
		printf("valset: '%s'\n",valset);
	}
	if (strncmp(valset,"out",3) == 0)
		return(1);

    return(ERROR_OK);
}

/* Function to read the value of the specified pin by reading
 * from the '/value' branch of the sysfs node. Value returned
 * is either 1 or 0 representing the values '0' and '1' read
 * from the node. ERROR (-1) is returned for errors during
 * write or open of sysfs node.
 */
int gpio_read(int pin)
{
	int state,len;
    if (debug >= DEBUG_VERB_HI) {
		printf("gpio_read\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/value",pin);

    if (debug >= DEBUG_VERB_MED) {
        printf("sysfs: '%s'\n",sysfs);
    }

	memset(valset,0x00,sizeof(valset));

    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    if (debug >= DEBUG_VERB_MED) {
		printf("valset: '%s'\n",valset);
	}
	if (strncmp(valset,"1",1) == 0)
		return(1);

    return(ERROR_OK);
}

/* Function to enumerate the old style bank the gpio pin belongs
 * to. Not useful except for converting old style pin names to
 * new style. Returns an int for pin bank, 0 if unknown, ERROR
 * (-1) if there was an error converting.
 */
int get_pin_bank(int pin)
{
	int bank;

    if (debug >= DEBUG_VERB_HI) {
		printf("get_pin_bank\n");
        printf("pin: '%d'\n",pin);
    }

	bank = pin/PIN_BANK_SIZE;

    if (debug >= DEBUG_VERB_MED)
        printf("bank: '%d'\n",bank);

	if (bank < 0 || bank > 5) {
		printf("Pin # '%d' Invalid, Bank '%d' out of range!\n",pin,bank);
		return(ERROR);
	}

	return(bank);
}

/* Function to enumerate the old style pin number the gpio pin
 * belongs to. Not useful except for converting old style pin names
 * to new style. Returns an int for pin number, 0 if unknown, ERROR
 * (-1) if there was an error converting.
 */
int get_old_pin_num(int pin)
{
	int bank,pinnum;

    if (debug >= DEBUG_VERB_HI) {
		printf("get_old_pin_num\n");
        printf("pin: '%d'\n",pin);
    }

	bank = get_pin_bank(pin);

    if (debug >= DEBUG_VERB_MED)
        printf("bank: '%d'\n",bank);

	pinnum = pin - (bank * PIN_BANK_SIZE);

    if (debug >= DEBUG_VERB_MED)
        printf("pinnum: '%d'\n",pinnum);

	if (pinnum < 0 || pinnum > 31) {
		printf("Pin # '%d' Invalid, pinnum '%d' out of range!\n",pin,pinnum);
		return(ERROR);
	}

	return(pinnum);
}

/* Function to enumerate the old style pin name (gpio1_23) the gpio
 * pin (gpio55) maps to. Not useful except for converting old style
 * pin names to new style. Returns the old pin name in the name
 * string buffer. Int return is ERROR_OK (0) if lookup is successful,
 * otherwise ERROR (-1) is returned.
 */
int get_old_pin_name(int pin, char* name)
{
	int bank,pinnum;

    if (debug >= DEBUG_VERB_HI) {
		printf("get_old_pin_name\n");
        printf("pin: '%d'\n",pin);
        printf("name: '%s'\n",name);
    }

	bank = get_pin_bank(pin);

    if (debug >= DEBUG_VERB_MED)
        printf("bank: '%d'\n",bank);

	if (bank < 0 || bank > 5) {
		printf("Pin # '%d' Invalid, Bank '%d' out of range!\n",pin,bank);
		return(ERROR);
	}

	pinnum = get_old_pin_num(pin);

    if (debug >= DEBUG_VERB_MED)
        printf("pinnum: '%d'\n",pinnum);

	if (pinnum < 0 || pinnum > 31) {
		printf("Pin # '%d' Invalid, pinnum '%d' out of range!\n",pin,pinnum);
		return(ERROR);
	}

	sprintf(name,"P%d_%d",bank,pinnum);

    if (debug >= DEBUG_VERB_MED) {
        printf("name: '%s'\n",name);
    }

	return(ERROR_OK);
}

/* Function to enumerate the cape connector that the gpio pin maps
 * to. Useful except for converting gpio pin style names (gpio23) to
 * pwm style (P8_13). This returns either 8 or 9 for valid gpio pins,
 * else 0 for unknown or ERROR (-1) for an error during conversion.
 */
int get_pin_conn(int pin)
{
	int conn;

//    if (debug >= DEBUG_VERB_HI) {
//		printf("get_pin_conn\n");
//        printf("pin: '%d'\n",pin);
//    }

	conn = conn_map[pin];

//    if (debug >= DEBUG_VERB_MED)
//        printf("conn: '%d'\n",conn);

	return(conn);
}

/* Function to enumerate the cape pin number that the gpio pin maps
 * to. Useful except for converting gpio pin style names (gpio23) to
 * pwm style (P8_13). This returns either the pin number as an int for
 * valid gpio pins, else 0 for unknown or ERROR (-1) for an error during
 * conversion.
 */
int get_pin_num(int pin)
{
	int bank,pinnum;

//    if (debug >= DEBUG_VERB_HI) {
//		printf("get_pin_num\n");
//        printf("pin: '%d'\n",pin);
//    }

	pinnum = pin_map[pin];

//    if (debug >= DEBUG_VERB_MED)
//        printf("pinnum: '%d'\n",pinnum);

	return(pinnum);
}

/* Function to map the gpio style pin number (gpio23) to pwm style
 * (P8_13). This takes the gpio pin numeric value and returns
 * a string containing the pwm style pin name ('P8_13') pass through
 * the name parameter. The return value is either the size of the
 * string returned, 0 for unknown, or ERROR (-1) for an error during
 * conversion.
 */
int get_pwm_pin_name(int pin, char* name)
{
	int conn,pinnum;

    if (debug >= DEBUG_VERB_HI) {
		printf("get_pwm_pin_name\n");
        printf("pin: '%d'\n",pin);
        //printf("name: '%s'\n",name);
    }

	conn = get_pin_conn(pin);

    if (debug >= DEBUG_VERB_MED)
        printf("conn: '%d'\n",conn);

	if (conn < 8 || conn > 9) {
		printf("Pin # '%d' Invalid, conn '%d' out of range!\n",pin,conn);
		return(ERROR);
	}

	pinnum = get_pin_num(pin);

    if (debug >= DEBUG_VERB_MED)
        printf("pinnum: '%d'\n",pinnum);

	if (pinnum < 0 || pinnum > 46) {
		printf("Pin # '%d' Invalid, pinnum '%d' out of range!\n",pin,pinnum);
		return(ERROR);
	}

	sprintf(name,"P%d_%d",conn,pinnum);

    if (debug >= DEBUG_VERB_MED) {
        printf("name: '%s'\n",name);
    }

	return(ERROR_OK);
}

/* Function to search and return the current capemgr number
 * expressed in the '/sys/devices' branch of sysfs.
 * Value returned is enumerated value after the '/capemgr.'
 * sysfs node. ERROR (-1) is returned for errors during write or
 * open of sysfs node.
 */
int get_capemgr_num(void)
{
	int n = ERROR;
	DIR *dp = NULL;
	char tmp[20];
	char * ptr;
	struct dirent *dptr = NULL;

    if (debug >= DEBUG_VERB_HI) {
		printf("get_capemgr_num\n");
    }

    sprintf(sysfs,SYSFS_DEV);

    if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
	}

	if ((dp = opendir(sysfs)) == NULL) {
        printf("Error opening sysfs node '%s'\n",sysfs);
        return(ERROR);
    }
	sprintf(tmp,"%s","bone_capemgr.");

	while(NULL != (dptr = readdir(dp)) ) {
		//printf(" [%s] ",dptr->d_name);
		if (strncmp(dptr->d_name,tmp,strlen(tmp)) == 0) {
			ptr = strtok(dptr->d_name,".");
			//printf("ptr: '%s'\n",ptr);
			ptr = strtok(NULL,".");
			if (ptr != NULL)
				n = atoi(ptr);
		}
	}

	// Close the directory stream
	closedir(dp);
	return(n);
}

/* Function to search and return the current ocp number expressed in
 * the '/sys/devices' branch of sysfs. Value returned is enumerated
 * value after the '/ocp.' sysfs node. ERROR (-1) is returned for errors
 * during write or open of sysfs node.
 */
 int get_ocp_num(void)
{
	int n = ERROR;
	DIR *dp = NULL;
	char tmp[20];
	char * ptr;
	struct dirent *dptr = NULL;

    if (debug >= DEBUG_VERB_HI) {
		printf("get_ocp_num\n");
    }

    sprintf(sysfs,SYSFS_DEV);

    if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
	}

	if ((dp = opendir(sysfs)) == NULL) {
        printf("Error opening sysfs node '%s'\n",sysfs);
        return(ERROR);
    }
	sprintf(tmp,"%s","ocp.");

	while(NULL != (dptr = readdir(dp)) ) {
		//printf(" [%s] ",dptr->d_name);
		if (strncmp(dptr->d_name,tmp,strlen(tmp)) == 0) {
			ptr = strtok(dptr->d_name,".");
			//printf("ptr: '%s'\n",ptr);
			ptr = strtok(NULL,".");
			if (ptr != NULL)
				n = atoi(ptr);
		}
	}

	// Close the directory stream
	closedir(dp);
	return(n);

}

/* Function to search and return the current ocp sysfs path as found
 * in the '/sys/devices' branch of sysfs. Value returned is a string
 * pointer (char*) representing the discovered ocp path.
 */
char* get_ocp_path(void)
{

	int ocp = get_ocp_num();

    if (debug >= DEBUG_VERB_HI) {
		printf("get_ocp_path\n");
    }

    sprintf(valset,SYSFS_OCP "%d",ocp);

    if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",valset);
	}

	return(valset);
}

/* Function to create and return the current pwm pin sysfs path as found
 * in the '/sys/devices' branch of sysfs based on the supplied pwm pin
 * name. Value returned is a string pointer (char*) representing the
 * discovered pwm path.
 */
char* get_pwm_pin_path(char * pin_name)
{
    if (debug >= DEBUG_VERB_HI) {
		printf("get_pwm_pin_path\n");
		printf("pin_name: '%s'\n",pin_name);
    }

	sprintf(sysfs,"%s",get_ocp_path());

    if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
	}

	int pin_num = get_pwm_pin_num(pin_name);

    if (debug >= DEBUG_VERB_MED) {
		printf("pin: '%d'\n",pin_num);
	}

	sprintf(valset,"%s/pwm_test_%s.%d",sysfs,pin_name,pin_num);

    if (debug >= DEBUG_VERB_MED) {
		printf("valset: '%s'\n",valset);
	}

	return(valset);
}

/* Function to search and return the current pwm pin instance
 * number expressed in the '/sys/devices/ocp.N' branch of sysfs.
 * Value returned is enumerated value after the '/pwm_test_'
 * sysfs node. ERROR (-1) is returned for errors during write or
 * open of sysfs node. (ocp# lookup is performed internally)
 */
int get_pwm_pin_num(char * pin_name)
{
	int n = ERROR;
	DIR *dp = NULL;
	char tmp[20];
	char * ptr;
	struct dirent *dptr = NULL;

    if (debug >= DEBUG_VERB_HI) {
		printf("get_pwm_pin_num\n");
		printf("pin_name: '%s'\n",pin_name);
    }

//	int ocp = get_ocp_num();

    sprintf(sysfs,"%s",get_ocp_path());

    if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
	}

	if ((dp = opendir(sysfs)) == NULL) {
        printf("Error opening sysfs node '%s'\n",sysfs);
        return(ERROR);
    }
	sprintf(tmp,"pwm_test_%s",pin_name);

    if (debug >= DEBUG_VERB_MED) {
		printf("tmp: '%s'\n",tmp);
	}

	while(NULL != (dptr = readdir(dp)) ) {
		//printf(" [%s] ",dptr->d_name);
		if (strncmp(dptr->d_name,tmp,strlen(tmp)) == 0) {
			ptr = strtok(dptr->d_name,".");
			//printf("ptr: '%s'\n",ptr);
			ptr = strtok(NULL,".");
			if (ptr != NULL)
				n = atoi(ptr);
		}
	}

	// Close the directory stream
	closedir(dp);
	return(n);

}

/* Function to request PWM from the '/slots' node of the
 * specified capmgr sysfs node. ERROR (-1) is returned for
 * errors during write or open of sysfs node.
 */
int request_pwm(int capemgrnum)
{
    if (debug >= DEBUG_VERB_HI) {
		printf("request_pwm\n");
        printf("capemgrnum: '%d'\n",capemgrnum);
    }

    sprintf(sysfs,SYSFS_CAPE "%d/slots",capemgrnum);
	sprintf(valset,"%s","am33xx_pwm");

    if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error requesting '%s' at node '%s'\n",valset,sysfs);
        return(ERROR);
    }

    return(ERROR_OK);
}

/* Function to request PWM from the '/slots' node of the
 * enumerated capemgr sysfs node. ERROR (-1) is returned for
 * errors during write or open of sysfs node.
 */
int request_pwm_pin(char * pwm_pin_name)
{
    if (debug >= DEBUG_VERB_HI) {
		printf("request_pwm_pin\n");
        printf("pwm_pin_name: '%s'\n",pwm_pin_name);
	}

	int capemgrnum = get_capemgr_num();

	if (debug >= DEBUG_VERB_MED)
		printf("capemgrnum: '%d'\n",capemgrnum);

	if (get_pwm_pin_num(pwm_pin_name) >= ERROR_OK) {
		if (debug >= DEBUG_VERB_MED)
			printf("PWM Pin is already currently active!\n");
		return(ERROR_OK);
	}

	if (debug >= DEBUG_VERB_MED)
		printf("PWM Pin is not currently active, requesting!\n");

	sprintf(sysfs,SYSFS_CAPE "%d/slots",capemgrnum);
	sprintf(valset,"bone_pwm_%s",pwm_pin_name);

	if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}
	if (write_sysfs_node(sysfs, valset) < 0) {
		printf("Error requesting '%s' at node '%s'\n",valset,sysfs);
		return(ERROR);
	}

    return(ERROR_OK);
}

/* Function to search and return the pwm pin name
 * expressed in the '/sys/devices' branch of sysfs.
 * Value returned is enumerated value after the '/ocp.'
 * sysfs node. ERROR (-1) is returned for errors during write
 * or open of sysfs node.
 */
int get_pwm_num(int ocpnum,int pin)
{
	return(ERROR_OK);
}

/* Function to set 'run' mode of the specified PWM pin.
 * Value returned is ERROR_OK (0) for succesful, ERROR
 * (-1) is returned for errors during write or open of
 * sysfs node.
 */
int pwm_pin_run(char * pwm_pin_name)
{
    if (debug >= DEBUG_VERB_HI) {
		printf("pwm_pin_run\n");
        printf("pwm_pin_name: '%s'\n",pwm_pin_name);
	}

	if (get_pwm_pin_num(pwm_pin_name) < ERROR_OK) {
//		if (debug >= DEBUG_VERB_MED)
			printf("PWM Pin is NOT already currently active!\n");
		return(ERROR);
	}

	if (debug >= DEBUG_VERB_MED)
		printf("PWM Pin is currently active!\n");

	sprintf(sysfs,"%s/run",get_pwm_pin_path(pwm_pin_name));
	sprintf(valset,"%d",1);

	if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}

	if (write_sysfs_node(sysfs, valset) < 0) {
		printf("Error requesting '%s' at node '%s'\n",valset,sysfs);
		return(ERROR);
	}

    return(ERROR_OK);
}

/* Function to set 'stop' mode of the specified PWM pin.
 * Value returned is ERROR_OK (0) for succesful, ERROR
 * (-1) is returned for errors during write or open of
 * sysfs node.
 */
int pwm_pin_stop(char * pwm_pin_name)
{
    if (debug >= DEBUG_VERB_HI) {
		printf("pwm_pin_stop\n");
        printf("pwm_pin_name: '%s'\n",pwm_pin_name);
	}

	if (get_pwm_pin_num(pwm_pin_name) < ERROR_OK) {
//		if (debug >= DEBUG_VERB_MED)
			printf("PWM Pin is NOT already currently active!\n");
		return(ERROR);
	}

	if (debug >= DEBUG_VERB_MED)
		printf("PWM Pin is currently active!\n");

	sprintf(sysfs,"%s",get_pwm_pin_path(pwm_pin_name));
	sprintf(valset,"%d",0);

	if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}

	if (write_sysfs_node(sysfs, valset) < 0) {
		printf("Error requesting '%s' at node '%s'\n",valset,sysfs);
		return(ERROR);
	}

    return(ERROR_OK);
}

/* Function to write the duty cycle value  (in percent) to
 * the specified pin by reading the current period value.
 * Calculating the required duty value and writing to the
 * '/duty' branch of the sysfs pwm node. Value returned is
 * ERROR_OK (0) for succesful, ERROR (-1) is returned for
 * errors during write or open of sysfs node.
 */
int pwm_write_duty_cycle(char* name, int dutycycle)
{
	// OCP/pwm_test_PINNAME.pin
	//echo ${DUTY} > ${PWM}/duty

    if (debug >= DEBUG_VERB_HI) {
		printf("pwm_write_duty_cycle\n");
        printf("name: '%s'\n",name);
        printf("dutycycle: '%d'\n",dutycycle);
    }

	long period = pwm_read_period(name);

    if (debug >= DEBUG_VERB_MED) {
		printf("period: '%ld'\n",period);
	}

	long duty = dutycycle * period / 100;

	duty = period - duty;

    if (debug >= DEBUG_VERB_MED) {
        printf("duty: '%ld'\n",duty);
	}

	if (pwm_write_duty(name,duty) < ERROR_OK) {
        printf("Error writing duty cycle\n");
        return(ERROR);
    }

    return(ERROR_OK);
}

/* Function to write the duty cycle value to the specified pin
 * by writing to the '/duty' branch of the sysfs pwm node.
 * Value returned is ERROR_OK (0) for succesful, ERROR (-1) is
 * returned for errors during write or open of sysfs node.
 */
int pwm_write_duty(char* name, long duty)
{
	// OCP/pwm_test_PINNAME.pin
	//echo ${DUTY} > ${PWM}/duty
    if (debug >= DEBUG_VERB_HI) {
		printf("pwm_write_duty\n");
        printf("name: '%s'\n",name);
        printf("duty: '%ld'\n",duty);
    }

	sprintf(sysfs,"%s/duty",get_pwm_pin_path(name));
	sprintf(valset,"%ld",duty);

    if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing '%s' to node '%s'\n",valset,sysfs);
        return(ERROR);
    }

    return(ERROR_OK);
}

/* Function to write the period value to the specified pin
 * by writing to the '/period' branch of the sysfs pwm node.
 * Value returned is ERROR_OK (0) for succesful, ERROR (-1)
 * is returned for errors during write or open of sysfs node.
 */
int pwm_write_period(char* name, long period)
{
	// OCP/pwm_test_PINNAME.pin
	//echo ${DUTY} > ${PWM}/duty
    if (debug >= DEBUG_VERB_HI) {
		printf("pwm_write_period\n");
        printf("name: '%s'\n",name);
        printf("period: '%ld'\n",period);
    }

	sprintf(sysfs,"%s/period",get_pwm_pin_path(name));
	sprintf(valset,"%ld",period);

    if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing '%s' to node '%s'\n",valset,sysfs);
        return(ERROR);
    }

    return(ERROR_OK);
}

/* Function to read the duty cycle value of the specified pin
 * by reading from the '/duty' branch of the sysfs pwm node.
 * Value returned is timer value representing the duty cycle
 * based on the current value of 'period'. ERROR (-1) is
 * returned for errors during write or open of sysfs node.
 */
long pwm_read_duty(char* name)
{
	int len;

    if (debug >= DEBUG_VERB_HI) {
		printf("pwm_read_duty\n");
        printf("name: '%s'\n",name);
    }

	sprintf(sysfs,"%s/duty",get_pwm_pin_path(name));

    if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
	}

	memset(valset,0x00,sizeof(valset));

    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading node '%s'\n",sysfs);
        return(ERROR);
    }

    if (debug >= DEBUG_VERB_MED) {
		printf("valset: '%s'\n",valset);
	}

	long duty = atol(valset);

	if (debug >= DEBUG_VERB_MED)
		printf("duty: '%ld'\n",duty);

    return(duty);
}

/* Function to read the period value of the specified pin
 * by reading from the '/period' branch of the sysfs pwm node.
 * Value returned is timer value representing the duty cycle
 * based on the current value of 'period'. ERROR (-1) is
 * returned for errors during write or open of sysfs node.
 */
long pwm_read_period(char* name)
{
	int len;

    if (debug >= DEBUG_VERB_HI) {
		printf("pwm_read_period\n");
        printf("name: '%s'\n",name);
    }

	sprintf(sysfs,"%s/period",get_pwm_pin_path(name));

    if (debug >= DEBUG_VERB_MED) {
		printf("sysfs: '%s'\n",sysfs);
	}

	memset(valset,0x00,sizeof(valset));

    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading node '%s'\n",sysfs);
        return(ERROR);
    }

    if (debug >= DEBUG_VERB_MED) {
		printf("valset: '%s'\n",valset);
	}

	long period = atol(valset);

	if (debug >= DEBUG_VERB_MED)
		printf("period: '%ld'\n",period);

    return(period);
}


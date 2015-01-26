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

int verbose = QUIET;

int test_sysfs_node(char * sysfs)
{
#ifdef TEST_USES_STAT	
	struct stat   buffer;   
#endif

    if (verbose) {
		printf("test_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
    }

#ifdef TEST_USES_STAT	

  return (stat (sysfs, &buffer) == 0);

#else
  
  if (access(sysfs, F_OK ) == -1)
		return(-1);
		
	return(0);
#endif

}

int read_sysfs_node(char * sysfs, char * buffer)
{
    int fd,len;
	char buf[50];
    if (verbose) {
		printf("read_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
    }

//#ifdef USE_FCNTL
    fd = open(sysfs, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error opening node '%s'\n",sysfs);
        return(-1);
    }
    len = read (fd, &buf, sizeof(buf));
    close(fd);
//#else
//    FILE* f = fopen(sysfs, "w");
//    if (f == NULL) {
//        fprintf(stderr, "Error writing node '%s'\n",sysfs);
//        return(-1);
//    }
//
//    len = fread(buf,1,sizeof(buf),f);
//    fclose(f);
//#endif
	strncpy(buffer,buf,strlen(buf)-1);
	
    if (verbose) {
		printf("buf: '%s'\n",buf);
		printf("buffer: '%s'\n",buffer);
		printf("len: '%d'\n",len);
	}
    return(len);
}

int write_sysfs_node(char * sysfs, char * value)
{
    int fd;

    if (verbose) {
		printf("write_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
        printf("value: '%s'\n",value);
    }

#ifdef USE_FCNTL
    fd = open(sysfs, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Error writing node '%s'\n",sysfs);
        return(-1);
    }
    write (fd, &value, strlen(value));
    close(fd);
#else
    FILE* f = fopen(sysfs, "w");
    if (f == NULL) {
        fprintf(stderr, "Error writing node '%s'\n",sysfs);
        return(-1);
    }

    fprintf(f, "%s", value);
    fprintf(f, "\n");
    fclose(f);
#endif
    return(0);
}

int gpio_is_exported(int pin)
{
    if (verbose) {
		printf("gpio_is_exported\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d",pin);

    if (test_sysfs_node(sysfs) != 0) {
		return(-1);
	}
	return(0);
}

int gpio_export(int pin)
{
    if (verbose) {
		printf("gpio_export\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/export");
    
    sprintf(valset,"%d",pin);

    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error exporting pin '%d' to node '%s/export'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    return(0);
}

int gpio_unexport(int pin)
{
    if (verbose) {
		printf("gpio_unexport\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/unexport");
    sprintf(valset,"%d",pin);

    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error unexporting pin '%d' to node '%s/unexport'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    return(0);
}

int gpio_write_dir(int pin, int state)
{
    if (verbose) {
		printf("gpio_write_dir\n");
        printf("pin: '%d'\n",pin);
        printf("state: '%d'\n",state);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/direction",pin);
	if (state == 1)
		sprintf(valset,"out");
	else
		sprintf(valset,"in");

    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing to pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    return(0);
}

int gpio_write(int pin, int state)
{
    if (verbose) {
		printf("gpio_write\n");
        printf("pin: '%d'\n",pin);
        printf("state: '%d'\n",state);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/value",pin);
    
    sprintf(valset,"%d",state);

    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing to pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    return(0);
}

int gpio_read_dir(int pin)
{
	int state,len;
    if (verbose) {
		printf("gpio_read_dir\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/direction",pin);
   
    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
    }
	
	memset(valset,0x00,sizeof(valset));
	
    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    if (verbose) {
		printf("valset: '%s'\n",valset);
	}
	if (strncmp(valset,"out",3) == 0)
		return(1);

    return(0);
}

int gpio_read(int pin)
{
	int state,len;
    if (verbose) {
		printf("gpio_read\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/value",pin);

    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
    }
	
	memset(valset,0x00,sizeof(valset));
	
    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    if (verbose) {
		printf("valset: '%s'\n",valset);
	}
	if (strncmp(valset,"1",1) == 0)
		return(1);

    return(0);
}

int get_pin_bank(int pin)
{
	int bank;
    
    if (verbose) {
		printf("get_pin_bank\n");
        printf("pin: '%d'\n",pin);
    }
	
	bank = pin/PIN_BANK_SIZE;

    if (verbose)
        printf("bank: '%d'\n",bank);

	if (bank < 0 || bank > 5) {
		printf("Pin # '%d' Invalid, Bank '%d' out of range!\n",pin,bank);
		exit(-1);
	}

	return(bank);
}

int get_pin_num(int pin)
{
	int bank,pinnum;
	
    if (verbose) {
		printf("get_pin_bank\n");
        printf("pin: '%d'\n",pin);
    }

	bank = get_pin_bank(pin);

    if (verbose)
        printf("bank: '%d'\n",bank);
	
	pinnum = pin - (bank * PIN_BANK_SIZE);
	
    if (verbose)
        printf("pinnum: '%d'\n",pinnum);

	if (pinnum < 0 || pinnum > 31) {
		printf("Pin # '%d' Invalid, pinnum '%d' out of range!\n",pin,pinnum);
		exit(-1);
	}

	return(pinnum);
}

int get_pwm_pin_name(int pin, char* name)
{
	int bank,pinnum;
	
    if (verbose) {
		printf("get_pwm_pin_name\n");
        printf("pin: '%d'\n",pin);
        printf("name: '%s'\n",name);
    }
	
	bank = get_pin_bank(pin);

    if (verbose)
        printf("bank: '%d'\n",bank);

	if (bank < 0 || bank > 5) {
		printf("Pin # '%d' Invalid, Bank '%d' out of range!\n",pin,bank);
		exit(-1);
	}
	
	pinnum = get_pin_num(pin);
	
    if (verbose)
        printf("pinnum: '%d'\n",pinnum);

	if (pinnum < 0 || pinnum > 31) {
		printf("Pin # '%d' Invalid, pinnum '%d' out of range!\n",pin,pinnum);
		exit(-1);
	}

	sprintf(name,"P%d_%d",bank,pinnum);

    if (verbose) {
        printf("name: '%s'\n",name);
    }
	
	return(0);
}

int get_capemgr_num(void)
{
	int state,len;
	DIR *dp = NULL;
	struct dirent *dptr = NULL;
	
    if (verbose) {
		printf("get_capemgr_num\n");
    }

    sprintf(sysfs,SYSFS_CAPE);

    if (verbose) {
		printf("sysfs: '%s'\n",sysfs);
	}

	if ((dp = opendir(sysfs)) == NULL) {
        printf("Error opening sysfs node '%s'\n",sysfs);
        return(-1);
    }
	
	while(NULL != (dptr = readdir(dp)) ) {
		printf(" [%s] ",dptr->d_name);
	}

	// Close the directory stream
	closedir(dp);        
	return(0);
}

int pwm_read_duty(int pin)
{
	int state,len;
    if (verbose) {
		printf("pwm_read_duty\n");
        printf("pin: '%d'\n",pin);
    }

    return(0);
}


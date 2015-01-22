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

#define HIGH 1
#define LOW 0
#define ON 1
#define OFF 0

//	/sys/class/leds/beaglebone\:green\:${LED}/trigger
//	/sys/class/gpio/...
char gpio[] = "/sys/class/gpio";
char sysfs[120];
char valset[20];

int VERBOSE = 0;

int write_sysfs_node(char * sysfs, char * value)
{
    int fd;

    if (VERBOSE) {
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

int gpio_export(int pin)
{
    if (VERBOSE) {
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,"%s/export",gpio);
    sprintf(valset,"%d",pin);

    if (VERBOSE) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error exporting pin '%d' to node '%s'\n",pin,gpio);
        return(-1);
    }

    return(0);
}

int gpio_unexport(int pin)
{
    if (VERBOSE) {
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,"%s/unexport",gpio);
    sprintf(valset,"%d",pin);

    if (VERBOSE) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error unexporting pin '%d' to node '%s'\n",pin,gpio);
        return(-1);
    }

    return(0);
}

int gpio_write(int pin, int state)
{
    if (VERBOSE) {
        printf("pin: '%d'\n",pin);
        printf("state: '%d'\n",state);
    }

    sprintf(sysfs,"%s/gpio%d/value",gpio,pin);
    sprintf(valset,"%d",state);

    if (VERBOSE) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing to pin '%d' at node '%s'\n",pin,gpio);
        return(-1);
    }

    return(0);
}


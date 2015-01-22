/***************************************************************************
 * usrled.c - A c program that controls the state of the user (usr) LEDs
 * on the beagle bone black in userspace using sysfs. Build by invoking gcc
 * 'gcc usrled.c -o usrled' No special libs needed.
 *
 * (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: January 2015
 *
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

// Global defines
#define HIGH 1
#define LOW 0
#define ON 1
#define OFF 0

// Method defines

// There are two methods to control writing to a simple file in userspace,
// FCNTL or FILE*. Uncomment the next line to write via FCNTL, else it uses
// FILE* method by default.
#define USE_FCNTL
// There are two ways of controlling the LED state via SYSFS, write a 1/0
// to the 'brightness' node, or 'none/default-on' to the 'trigger' node.
// Uncomment the next line to use 'trigger', else it uses 'brightness'
//#define USE_TRIGGER

// If enabled (set to 1) this parameter will cause the printing of
// much debug info. Use with care.
int VERBOSE = 0;

char gpio[120];
char valset[20];

int write_trigger(char * sysfs_path, int value);
int write_brightness(char * sysfs_path, int value);

/**********************************************
 * write_trigger - This function will write the
 * correct value of either 'none' or 'default-on'
 * to the trigger node of the specified sysfs
 * path, based on the value of 'value'.
 **********************************************/
int write_trigger(char * sysfs_path, int value)
{
  int fd;

  strcat(sysfs_path,"/trigger");
  if (VERBOSE) {
    printf("sysfs: '%s'\n",sysfs_path);
    printf("value: '%d'\n",value);
  }
  memset(valset,0x00,sizeof(valset));
  if ((value & 0x01) == 0)
      strcpy(valset,"none");
  else
      strcpy(valset,"default-on");
  if (VERBOSE)
    printf("valset: '%s'\n",valset);

#ifdef USE_FCNTL
  if (VERBOSE)
    printf("Using FCNTL!\n");
  fd = open(sysfs_path, O_WRONLY);
  if (fd < 0) {
    fprintf(stderr, "Unable to open path for writing\n");
    return -1;
  }
  write (fd, &valset, strlen(valset));
  close(fd);
#else
  if (VERBOSE)
    printf("Using FILE*!\n");
  FILE* f = fopen(sysfs_path, "w");
  if (f == NULL) {
    fprintf(stderr, "Unable to open path for writing\n");
    return -1;
  }
  fprintf(f, valset);
  fprintf(f, "\n");
  fclose(f);
#endif
  return(0);
}

/**********************************************
 * write_brightness - This function will write
 * the value of either '0' or '1' to the brightness
 * node of the specified sysfs path, based on
 * the value of 'value'.
 **********************************************/
int write_brightness(char * sysfs_path, int value)
{
  int fd;

  strcat(sysfs_path,"/brightness");
  if (VERBOSE) {
    printf("sysfs: '%s'\n",sysfs_path);
    printf("value: '%d'\n",value);
  }
  memset(valset,0x00,sizeof(valset));
  sprintf(valset,"%d",(value & 0x01));
  if (VERBOSE)
    printf("valset: '%s'\n",valset);

#ifdef USE_FCNTL
  if (VERBOSE)
    printf("Using FCNTL!\n");
  fd = open(sysfs_path, O_WRONLY);
  if (fd < 0) {
    fprintf(stderr, "Unable to open path for writing\n");
    return -1;
  }
  write (fd, &valset, strlen(valset));
  close(fd);
#else
  if (VERBOSE)
    printf("Using FILE*!\n");
  FILE* f = fopen(sysfs_path, "w");
  if (f == NULL) {
    fprintf(stderr, "Unable to open path for writing\n");
    return -1;
  }
  fprintf(f, valset);
  fprintf(f, "\n");
  fclose(f);
#endif
  return(0);
}

// SYSFS Path: /sys/class/leds/beaglebone\:green\:${LED}/trigger
int main(int argc, char * argv[])
{
    int led, state, i;

    led = 3;
    state = 1;
    if (VERBOSE) {
      printf("argc: %d\n",argc);
      for (i=0;i<argc;i++)
          printf("argv[%d]: '%s'\n",i,argv[i]);
    }

    if (argc > 1)
        led = atoi(argv[1]);
    if (argc > 2)
        state = atoi(argv[2]);

    sprintf(gpio,"/sys/class/leds/beaglebone:green:usr%d",led);

    if (VERBOSE) {
      printf("led: '%d'\n",led);
      printf("state: '%d'\n",state);
      printf("gpio: '%s'\n",gpio);
    }
#ifdef USE_TRIGGER
    if (VERBOSE)
      printf("Using trigger!\n");

    write_trigger(gpio,state);

#else
    if (VERBOSE)
      printf("Using brightness!\n");

    write_brightness(gpio,state);

#endif

}

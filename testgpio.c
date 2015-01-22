#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define HIGH 1
#define LOW 0
#define ON 1
#define OFF 0

char gpio[120];
char valset[20];
void gpio_write(char * sysfs_path, int value);

void gpio_write(char * sysfs_path, int value)
{
  int fd;

  printf("sysfs: '%s'\n",sysfs_path);
  printf("value: '%d'\n",value);
  memset(valset,0x00,sizeof(valset));
  if ((value & 0x01) == 0)
      strcpy(valset,"none");
  else
      strcpy(valset,"default-on");
  printf("valset: '%s'\n",valset);
  fd = open(sysfs_path, O_WRONLY);
  write (fd, &valset, strlen(valset));
  close(fd);
}

int main(int argc, char * argv[])
{
    int led, state, i;
//	/sys/class/leds/beaglebone\:green\:${LED}/trigger

    led = 3;
    state = 1;

    printf("argc: %d\n",argc);
    for (i=0;i<argc;i++)
        printf("argv[%d]: '%s'\n",i,argv[i]);
    if (argc > 1)
        led = atoi(argv[1]);
    if (argc > 2)
        state = atoi(argv[2]);

    printf("led: '%d'\n",led);
    sprintf(gpio,"sys/class/leds/beaglebone:green:usr%d/trigger",led);

    printf("gpio: '%s'\n",gpio);
    printf("state: '%d'\n",state);

    gpio_write(gpio,state);

    printf("led: '%d'\n",led);
    sprintf(gpio,"sys/class/leds/beaglebone:green:usr%d/trigger",led);

    printf("gpio: '%s'\n",gpio);
    printf("state: '%d'\n",state);

    gpio_write(gpio,state);
}

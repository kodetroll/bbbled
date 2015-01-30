#############################################
# 
# Simple makefile for BBB sysfs utilities
#
#IDIR =../include
CC=gcc
#CFLAGS=-I$(IDIR)

CC=gcc
CFLAGS=-I.
DEPS = sysfs.h
#OBJ = sysfs.o gpio.o 
SYSOBJ = sysfs.o 
COLOBJ = colors.o
DEPOBJ = $(SYSOBJ) $(COLOBJ)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: get_pwm_pin_name testsysfs usrled gpio_write gpio_test pwm_test pwm fader

test: testsysfs gpio_test pwm_test testcolors

get_pwm_pin_name: get_pwm_pin_name.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

testcolors: testcolors.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

testsysfs: testsysfs.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

usrled: usrled.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

gpio_write: gpio_write.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

gpio_test: gpio_test.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

pwm_test: pwm_test.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

pwm: pwm.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

fader: fader.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

cleanall:
	rm -f get_pwm_pin_name usrled testsysfs fader gpio_write gpio_test pwm_test pwm *.o *~ core  

clean:
	rm -f *.o *~ core  


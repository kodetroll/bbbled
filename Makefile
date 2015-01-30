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

all: tests pwms gpios

gpios: usrled gpio_write gpio_test

pwms: get_pwm_pin_name pwm_test pwm fader pwm_setcolor pwm_colorfader

tests: testsysfs testcolors

#################
# gpios

usrled: usrled.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

gpio_write: gpio_write.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

gpio_test: gpio_test.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

#################
# pwms

get_pwm_pin_name: get_pwm_pin_name.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

pwm_test: pwm_test.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

pwm: pwm.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

fader: fader.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

pwm_setcolor: pwm_setcolor.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

pwm_colorfader: pwm_colorfader.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

#################
# tests

testcolors: testcolors.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

testsysfs: testsysfs.o $(DEPOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

cleanall:
	rm -f usrled gpio_write gpio_test get_pwm_pin_name pwm_test pwm \
		fader pwm_setcolor pwm_colorfader testsysfs testcolors \
		*.o *~ core  
clean:
	rm -f *.o *~ core  


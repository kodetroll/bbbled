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
OBJWR = sysfs.o gpio_write.o 
OBJTEST = sysfs.o gpio_test.o 
OBJPWMT = sysfs.o pwm_test.o 
OBJPWM = sysfs.o pwm.o 
OBJFADE = sysfs.o fader.o 
OBJTSYS = sysfs.o testsysfs.o
OBJUSR = sysfs.o usrled.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: testsysfs usrled gpio_write gpio_test pwm_test pwm fader

#gpio: $(OBJ)
#	$(CC) -o $@ $^ $(CFLAGS)

testsysfs: $(OBJTSYS)
	$(CC) -o $@ $^ $(CFLAGS)

usrled: $(OBJUSR)
	$(CC) -o $@ $^ $(CFLAGS)

gpio_write: $(OBJWR)
	$(CC) -o $@ $^ $(CFLAGS)

gpio_test: $(OBJTEST)
	$(CC) -o $@ $^ $(CFLAGS)

pwm_test: $(OBJPWMT)
	$(CC) -o $@ $^ $(CFLAGS)

pwm: $(OBJPWM)
	$(CC) -o $@ $^ $(CFLAGS)

fader: $(OBJFADE)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

cleanall:
	rm -f testsysfs fader gpio_write gpio_test pwm_test *.o *~ core  
clean:
	rm -f *.o *~ core  


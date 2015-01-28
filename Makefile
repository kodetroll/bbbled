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
OBJPWM = sysfs.o pwm_test.o 
OBJFADE = sysfs.o fader.o 
OBJTSYS = sysfs.o testsysfs.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: testsysfs gpio_write gpio_test pwm_test fader

#gpio: $(OBJ)
#	$(CC) -o $@ $^ $(CFLAGS)

testsysfs: $(OBJTSYS)
	$(CC) -o $@ $^ $(CFLAGS)

gpio_write: $(OBJWR)
	$(CC) -o $@ $^ $(CFLAGS)

gpio_test: $(OBJTEST)
	$(CC) -o $@ $^ $(CFLAGS)

pwm_test: $(OBJPWM)
	$(CC) -o $@ $^ $(CFLAGS)

fader: $(OBJFADE)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

cleanall:
	rm -f testsysfs fader gpio_write gpio_test pwm_test *.o *~ core  
clean:
	rm -f *.o *~ core  


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


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: gpio_write gpio_test

gpio: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

gpio_write: $(OBJWR)
	gcc -o $@ $^ $(CFLAGS)

gpio_test: $(OBJTEST)
	gcc -o $@ $^ $(CFLAGS)

pwm_test: $(OBJPWM)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

cleanall:
	rm -f gpio_write gpio_test pwm_test *.o *~ core  
clean:
	rm -f *.o *~ core  


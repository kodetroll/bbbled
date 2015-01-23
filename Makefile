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
OBJ = sysfs.o gpio.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: gpio

gpio: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

#pwm: $(OBJPWM)
#	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

cleanall:
	rm -f gpio *.o *~ core  
clean:
	rm -f *.o *~ core  


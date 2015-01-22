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
OBJ = sysfs.o testgpio.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: testgpio

testgpio: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

#hex2asc: $(OBJASC)
#	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

cleanall:
	rm -f testgpio *.o *~ core  
clean:
	rm -f *.o *~ core  


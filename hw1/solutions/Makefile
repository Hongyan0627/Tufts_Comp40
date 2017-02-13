# Makefile for filesnpix (Comp 40 Assignment 1)
# 
# Includes build rules for simlines and brightness
#
# This Makefile is more verbose than necessary. In each assignment
# we will simplify the Makefile using more powerful syntax and implicit rules.
#
# Last updated: January 22, 2016


############## Variables ###############

CC = gcc # The compiler being used

# Updating include path to use current directory
# (which is .), Comp 40 .h files, and CII interfaces
IFLAGS = -I. -I/comp/40/include -I/usr/sup/cii40/include/cii

# Compile flags, used in the compilation step
# Set debugging information, allow the c99 standard,
# max out warnings, and use the updated include path
CFLAGS = -g -std=c99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

# Linking flags, used in the linking step
# Set debugging information and update linking path
# to include course binaries and CII implementations
LDFLAGS = -g -L/comp/40/lib64 -L/usr/sup/cii40/lib64

# Libraries needed for any of the programs that will be linked
# Both programs need cii40 (Hanson binaries) and *may* need -lm (math)
# Only brightness requires the binary for pnmrdr.
LDLIBS = -lpnmrdr -lcii40 -lm


############### Rules ###############

all: brightness simlines

## Compile step (.c files -> .o files)

brightness.o: brightness.c
	$(CC) $(CFLAGS) -c brightness.c -o brightness.o

readaline.o: readaline.c
	$(CC) $(CFLAGS) $(LDLIBS) -c readaline.c -o readaline.o

simlines.o: simlines.c
	$(CC) $(CFLAGS) -c simlines.c -o simlines.o

# If you write any other .o rules, they would have to go here


## Linking step (.o -> executable program)

brightness: brightness.o
	$(CC) $(LDFLAGS) brightness.o -o brightness $(LDLIBS)

simlines: simlines.o readaline.o
	$(CC) $(LDFLAGS) simlines.o readaline.o -o simlines $(LDLIBS)


clean:
	rm -f brightness simlines *.o


# Makefile for UM (Comp 40 Assignment 6)
# 
# Includes build rules for test_segmenter, umlabwrite and um.
#
# This Makefile is more verbose than necessary.  In each assignment
# we will simplify the Makefile using more powerful syntax and implicit rules.
#
# Last updated: April 13, 2016


############## Variables ###############

CC = gcc # The compiler being used

# Updating include path to use Comp 40 .h files and CII interfaces
IFLAGS = -I/comp/40/include -I/usr/sup/cii40/include/cii

# Compile flags
# Set debugging information, allow the c99 standard,
# max out warnings, and use the updated include path
# CFLAGS = -g -std=c99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)
# 
# For this assignment, we have to change things a little.  We need
# to use the GNU 99 standard to get the right items in time.h for the
# the timing support to compile.
# 
CFLAGS = -g -O2 -std=gnu99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

# Linking flags
# Set debugging information and update linking path
# to include course binaries and CII implementations
LDFLAGS = -g -L/comp/40/lib64 -L/usr/sup/cii40/lib64

# Libraries needed for linking
# All programs cii40 (Hanson binaries) and *may* need -lm (math)
#LDLIBS  = -lbitpack -lcii40 -lm -lrt
#LDLIBS = -lbitpack -lcii40-O1 -lnetpbm -lm -lrt
LDLIBS = -lbitpack -lcii40-O2 -lnetpbm -lm -lrt

# Collect all .h files in your directory.
# This way, you can never forget to add
# a local .h file in your dependencies.
#
# This bugs Mark, who dislikes false dependencies, but
# he agrees with Noah that you'll probably spend hours 
# debugging if you forget to put .h files in your 
# dependency list.
INCLUDES = $(shell echo *.h)

############### Rules ###############

all: test_segmenter umlabwrite um 


# Compile step (.c files -> .o files)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@


## Linking step (.o -> executable program)

test_segmenter: test_segmenter_main.o seg.o segmenter_tester.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

umlabwrite: umlabwrite.o umlab.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

um: universal_machine.o UM.o program_loader.o seg.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f test_segmenter umlabwrite um *.o

# Makefile for UM (Comp 40 Assignment 6)
# 
# Includes build rules for UM and testing programs 
# for modules
#
#
# Last updated: April 3rd, 2016
# Last compiling: with 02

############## Variables ###############
#O1 optimization 
#CC = gcc -O1 # The compiler being used

#O2 optimization
CC = gcc -O2

# Updating include path to use Comp 40 .h files and CII interfaces
IFLAGS = -I/comp/40/include -I/usr/sup/cii40/include/cii

# Compile flags
# Set debugging information, allow the c99 standard,
# max out warnings, and use the updated include path
#CFLAGS = -g -std=gnu99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

# For testing/debugging
CFLAGS = -g -std=gnu99 -Wall -Wextra -Werror -pedantic $(IFLAGS)

# Linking flags
# Set debugging information and update linking path
# to include course binaries and CII implementations
LDFLAGS = -g -L/comp/40/lib64 -L/usr/sup/cii40/lib64

# Libraries needed for linking
# All programs cii40 (Hanson binaries) and *may* need -lm (math) 

#O1 optimization 
#LDLIBS = -lcii40-O1 -lbitpack -lcii40 -lm -lum-dis -lcii 
#-larith40 -l40locality -lnetpbm -lrt (netpbm is needed for pnm)

#O2 optimization 
LDLIBS = -lcii40-O2 -lbitpack -lcii40 -lm -lum-dis -lcii 

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

all: um


## Compile step (.c files -> .o files)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c $(INCLUDES)
        $(CC) $(CFLAGS) -c $< -o $@


## Linking step (.o -> executable program)

test_um: umlab.o umlabwrite.o
        $(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

um: um_cycle.o um_memory.o um_loader.o um_main.o
        $(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

test_um_mem: um_memory.o memory_tests.o
        $(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

um_memory: um_memory.o
        $(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)      

um_loader: um_loader.o  
        $(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

um_IO_Device: um_IO_Device.o  
        $(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

um_cycle: um_cycle.o um_memory.o 
        $(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)


clean:
        rm -f um_memory, um_loader, um_IO_Device, um_cycle, *.o
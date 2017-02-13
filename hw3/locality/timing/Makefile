# 	         Makefile for COMP 40 Homework 1
#
#     Author: Noah Mendelsohn (adapted from Norman Ramsey's compile script)
#
#  Maintenance targets:
#
#
#    all                    - (default target) make sure everything's compiled
#    clean                  - clean out all compiled object and executable files
#    testprog               - tests cputiming interface
#

# Executables to built using "make all"

EXECUTABLES = testprog
#
#  The following is a compromise. You MUST list all your .h files here.
#  If any .h file changes, all .c files will be recompiled. To do better,
#  we could make an explicit target for each .o, naming only the .h
#  files it really uses.
#
# Add your own .h files to the right side of the assingment below.

INCLUDES = cputiming.h


#
# Dot o files used by ppmtrans
#

# Do all C compies with gcc (at home you could try clang)
GCC = gcc

# Comp 40 directory

COMP40 = /comp/40

# the next two lines enable you to compile and link against CII40
CIIFLAGS = `pkg-config --cflags cii40`
CIILIBS = `pkg-config --libs cii40`

# the next three lines enable you to compile and link against course software
CFLAGS = -O2 -I. -I$(COMP40)/include $(CIIFLAGS)
LIBS = $(CIILIBS) -lm
LFLAGS = -L$(COMP40)/lib64

# these flags max out warnings and debug info
# NEEDSWORK: we are compiling with std=gnu99 vs. c99 as this causes
# time.h to declare struct timespec, which we need.
FLAGS = -g -O2 -Wall -Wextra -Werror -std=gnu99 -pedantic

# 
#    'make all' will build all executables
#
#    Note that "all" is the default target that make will build
#    if nothing is specifically requested
#
all: $(EXECUTABLES)

# 
#    'make clean' will remove all object and executable files
#
clean:
	rm -f $(EXECUTABLES) *.o *~


# 
#    To get any .o, compile the corresponding .c
#
%.o:%.c $(INCLUDES)
	$(GCC) $(FLAGS) $(CFLAGS) -c $<

#
# Individual executables
#
#    Each executable depends on one or more .o files.
#    Those .o files are linked together to build the corresponding
#    executable.
#
testprog: testprog.o cputiming.o $(INCLUDES)
	$(GCC) $(FLAGS) $(LFLAGS) -o testprog testprog.o cputiming.o \
               $(LIBS) -lrt

echo:
	echo "$(CIIFLAGS)"
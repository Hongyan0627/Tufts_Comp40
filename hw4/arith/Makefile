# Makefile for Arith (Comp 40 Assignment 4)
# 
# Includes build rules for 40image.
#
# Last updated: March 8, 2016


############## Variables ###############

CC = gcc # The compiler being used

# Updating include path to use Comp 40 .h files and CII interfaces
IFLAGS = -I/comp/40/include -I/usr/sup/cii40/include/cii

# Compile flags
# Set debugging information, allow the c99 standard,
# max out warnings, and use the updated include path
CFLAGS = -g -std=c99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

# Linking flags
# Set debugging information and update linking path
# to include course binaries and CII implementations
LDFLAGS = -g -L/comp/40/lib64 -L/usr/sup/cii40/lib64

# Libraries needed for linking
# All programs cii40 (Hanson binaries) and *may* need -lm (math)
# arith40 is a catch-all for this assignment, netpbm is needed for pnm
LDLIBS = -larith40 -l40locality -lnetpbm -lcii40 -lm -lrt 

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

all: 40image-6 ppmdiff


## Compile step (.c files -> .o files)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c $(INCLUDES)
		$(CC) $(CFLAGS) -c $< -o $@


## Linking step (.o -> executable program)

40image-6: 40image.o compress40.o image_io.o cv_codeword_trans.o \
	rgb_cv_trans.o uarray2.o a2plain.o bitpack.o
		$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

ppmdiff: ppmdiff.o uarray2.o a2plain.o
		$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
		rm -f 40image-6 40image ppmdiff *.o

# M-Stack Host Test Software Makefile
#
# This file may be used by anyone for any purpose and may be used as a
# starting point making your own application using M-Stack.
#
# It is worth noting that M-Stack itself is not under the same license as
# this file.  See the top-level README.txt for more information.
#
# Alan Ott
# Signal 11 Software

all: test

test: test.c
	gcc -Wall -g -o test test.c `pkg-config libusb-1.0 --cflags --libs`

clean:
	rm test

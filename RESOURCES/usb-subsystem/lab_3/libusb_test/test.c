/*
 * Libusb Bulk Endpoint Test for M-Stack
 *
 * This file may be used by anyone for any purpose and may be used as a
 * starting point making your own application using M-Stack.
 *
 * It is worth noting that M-Stack itself is not under the same license as
 * this file.  See the top-level README.txt for more information.
 *
 * M-Stack is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  For details, see sections 7, 8, and 9
 * of the Apache License, version 2.0 which apply to this file.  If you have
 * purchased a commercial license for this software from Signal 11 Software,
 * your commerical license superceeds the information in this header.
 *
 * Alan Ott
 * Signal 11 Software
 * 2013-04-09

 */

/* C */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <errno.h>
#include <stdbool.h>

/* Unix */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <pthread.h>
#include <wchar.h>

/* GNU / LibUSB */
#include "libusb.h"

#include <sys/time.h>
#include <signal.h>

int buflen = 512;

static libusb_context *usb_context = NULL;

int main(int argc, char **argv)
{
	libusb_device_handle *handle;
	int i;
	int res = 0;

	/* Init Libusb */
	if (libusb_init(&usb_context))
		return -1;

	handle = libusb_open_device_with_vid_pid(NULL, 0x1a0a, 0xbadd);
	if (!handle) {
		fprintf(stderr, "libusb_open failed\n");
		return 1;
	}

	printf("Device Opened\n");

#if 0
	libusb_set_configuration(handle, 1);
	if (res < 0) {
		fprintf(stderr, "set_configuration(): %s\n", libusb_error_name(res));
		return 1;
	}
#endif

	res = libusb_claim_interface(handle, 0);
	if (res < 0) {
		perror("claim interface");
		return 1;
	}

	printf("Interface Claimed\n");

	/* Synchronous */
	unsigned char *buf = calloc(1, buflen);
	int actual_length;

	memset(buf, 0xa0, buflen);

	printf("Sending one transfer\n");

	/* Send one transfer to the device */
	res = libusb_bulk_transfer(handle, 0x01,
		buf, buflen, &actual_length, 1000);
	if (res < 0) {
		fprintf(stderr, "bulk transfer (out): %s\n", libusb_error_name(res));
		return 1;
	}

	printf("Receiving one transfer\n");

	/* Receive one transfer from the device */
	res = libusb_bulk_transfer(handle, 0x81,
		buf, buflen, &actual_length, 1000);
	if (res < 0) {
		fprintf(stderr, "bulk transfer (in): %s\n", libusb_error_name(res));
		return 1;
	}

	printf("Received data:\n");
	for (i = 0; i < actual_length; i++) {
		printf("%02hhx ", buf[i]);
		if ((i+1) % 8 == 0)
			printf("   ");
		if ((i+1) % 16 == 0)
			printf("\n");
	}
	printf("\n\n");

	return 0;
}

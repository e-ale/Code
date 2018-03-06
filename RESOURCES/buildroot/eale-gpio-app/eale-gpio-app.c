#include <assert.h>
#include <gpiod.h>
#include <stdio.h>

#define NGPIOS 6

int main(void)
{
	struct gpiod_chip *chip;
	struct gpiod_line *lines[NGPIOS];
	int ret;
	int i;

	chip = gpiod_chip_open("/dev/gpiochip4");
	assert(chip != NULL);

	for (i = 0; i < NGPIOS; i++) {
		lines[i] = gpiod_chip_get_line(chip, i);
		assert(lines[i] != NULL);

		ret = gpiod_line_request_output(lines[i], "eale-app",
						false, 1);
		assert(ret == 0);
	}

	i = 0;
	while(1) {
		struct timespec ts = { .tv_nsec = 200 * 1000 * 1000 };
		gpiod_line_set_value(lines[i], 0);
		nanosleep(&ts, NULL);
		gpiod_line_set_value(lines[i], 1);
		if (++i == NGPIOS)
			i = 0;
	}

	return 0;
}

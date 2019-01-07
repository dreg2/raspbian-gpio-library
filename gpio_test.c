#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "gpio.h"


// test 
int main(void)
	{
	const char * fsel_name[] = {"INPUT", "OUTPUT", "ALT5", "ALT4", "ALT0", "ALT1", "ALT2", "ALT3"};

	struct timespec delay = {3, 0}; // delay value

	if (gpio_init() < 0)
		return 1;

	for (uint8_t i = 0; i < 54; i++)
		printf("%.2d   %-9.9s   %d\n", i, fsel_name[gpio_fsel_get(i)], gpio_level(i));

	uint8_t pin = 13;
	uint8_t fsel_save = gpio_fsel_get(pin);
	uint8_t level_save = gpio_level(pin);

	gpio_fsel_set(pin, GPIO_FSEL_OUTPUT);
	gpio_clear(pin);
	printf("pin %d out/low  %-9.9s  %d\n", pin, fsel_name[gpio_fsel_get(pin)], gpio_level(pin));
	nanosleep(&delay, NULL);
	gpio_set(pin);
	printf("pin %d out/high %-9.9s  %d\n", pin, fsel_name[gpio_fsel_get(pin)], gpio_level(pin));
	nanosleep(&delay, NULL);

	gpio_fsel_set(pin, GPIO_FSEL_ALT4);
	printf("pin %d alt4     %-9.9s  %d\n", pin, fsel_name[gpio_fsel_get(pin)], gpio_level(pin));

	gpio_fsel_set(pin, GPIO_FSEL_INPUT);
	gpio_pud_set(pin, GPIO_PUD_DOWN);
	printf("pin %d in/low   %-9.9s  %d\n", pin, fsel_name[gpio_fsel_get(pin)], gpio_level(pin));
	gpio_pud_set(pin, GPIO_PUD_UP);
	printf("pin %d in/high  %-9.9s  %d\n", pin, fsel_name[gpio_fsel_get(pin)], gpio_level(pin));

	if (fsel_save == GPIO_FSEL_INPUT)
		gpio_pud_set(pin, GPIO_PUD_DOWN);
	else
		gpio_pud_set(pin, GPIO_PUD_OFF);
	gpio_fsel_set(pin, fsel_save);
	if (level_save)
		gpio_set(pin);
	else
		gpio_clear(pin);
	printf("pin %d restore  %-9.9s  %d\n", pin, fsel_name[gpio_fsel_get(pin)], gpio_level(pin));

	return 0;
	}

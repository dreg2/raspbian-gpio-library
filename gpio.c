#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <sys/mman.h>
#include <time.h>

#include "gpio.h"

// base pointer
volatile uint32_t *gpio_base = MAP_FAILED;

//----------------------------------------------------------------------------------------------------
// initialize gpio
//----------------------------------------------------------------------------------------------------
int8_t gpio_init(void)
	{
	int fd;
	if ((fd = open("/dev/gpiomem", O_RDWR | O_SYNC)) < 0)
		{
		perror("GPIO: open /dev/gpiomem failed:");
		return -1;
		}

	gpio_base = (uint32_t *)mmap(NULL, 0xB4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);

	if (gpio_base == MAP_FAILED)
		{
		perror("GPIO: mmap failed:");
		return -1;
		}

	return 0;
	}

//----------------------------------------------------------------------------------------------------
// read gpio register value
//----------------------------------------------------------------------------------------------------
uint32_t gpio_read(volatile uint32_t *gpio_reg)
	{
	uint32_t ret = *gpio_reg;
	__sync_synchronize(); // hardware memory barrier
	return ret;
	}

//----------------------------------------------------------------------------------------------------
// write gpio register value
//----------------------------------------------------------------------------------------------------
void gpio_write(volatile uint32_t *gpio_reg, uint32_t value)
	{
	__sync_synchronize(); // hardware memory barrier
	*gpio_reg = value;
	}

//----------------------------------------------------------------------------------------------------
// get gpio pin fsel
//----------------------------------------------------------------------------------------------------
uint8_t gpio_fsel_get(uint8_t pin)
	{
	uint8_t ret = (GPIO_REG_FSEL(pin) >> GPIO_FSEL_SHIFT(pin)) & GPIO_FSEL_MASK;
	__sync_synchronize(); // hardware memory barrier
	return ret;
	}

//----------------------------------------------------------------------------------------------------
// set gpio pin fsel
//----------------------------------------------------------------------------------------------------
void gpio_fsel_set(uint8_t pin, uint8_t fsel)
	{
	__sync_synchronize(); // hardware memory barrier
	GPIO_REG_FSEL(pin) = (GPIO_REG_FSEL(pin) & ~(GPIO_FSEL_MASK << GPIO_FSEL_SHIFT(pin)))
					| ((uint32_t)fsel << GPIO_FSEL_SHIFT(pin));
	}

//----------------------------------------------------------------------------------------------------
// set gpio pud
//----------------------------------------------------------------------------------------------------
void gpio_pud_set(uint8_t pin, uint8_t pud)
	{
	struct timespec delay = {0, 300}; // 300 nsecs

	__sync_synchronize(); // hardware memory barrier
	GPIO_REG_PUD = pud;
	nanosleep(&delay, NULL);
	GPIO_REG_PUDCLK(pin) = GPIO_PIN_MASK(pin);
	nanosleep(&delay, NULL);
	GPIO_REG_PUD = 0;
	GPIO_REG_PUDCLK(pin) = 0;
	}

//----------------------------------------------------------------------------------------------------
// get gpio level
//----------------------------------------------------------------------------------------------------
uint8_t gpio_level(uint8_t pin)
	{
	uint8_t ret = (GPIO_REG_LEV(pin) & GPIO_PIN_MASK(pin)) ? 1 : 0;
	__sync_synchronize(); // hardware memory barrier
	return ret;
	}

//----------------------------------------------------------------------------------------------------
// set gpio high
//----------------------------------------------------------------------------------------------------
void gpio_set(uint8_t pin)
	{
	__sync_synchronize(); // hardware memory barrier
	GPIO_REG_SET(pin) = GPIO_PIN_MASK(pin);
	}

//----------------------------------------------------------------------------------------------------
// set gpio low
//----------------------------------------------------------------------------------------------------
void gpio_clear(uint8_t pin)
	{
	__sync_synchronize(); // hardware memory barrier
	GPIO_REG_CLR(pin) = GPIO_PIN_MASK(pin);
	}

//----------------------------------------------------------------------------------------------------
// get gpio event detect status
//----------------------------------------------------------------------------------------------------
uint8_t gpio_eds(uint8_t pin)
	{
	uint8_t ret = (GPIO_REG_EDS(pin) & GPIO_PIN_MASK(pin)) ? 1 : 0;
	__sync_synchronize(); // hardware memory barrier
	return ret;
	}

//----------------------------------------------------------------------------------------------------
// set gpio rising edge detect enable
//----------------------------------------------------------------------------------------------------
void gpio_ren(uint8_t pin)
	{
	__sync_synchronize(); // hardware memory barrier
	GPIO_REG_REN(pin) = GPIO_PIN_MASK(pin);
	}

//----------------------------------------------------------------------------------------------------
// set gpio falling edge detect enable
//----------------------------------------------------------------------------------------------------
void gpio_fen(uint8_t pin)
	{
	__sync_synchronize(); // hardware memory barrier
	GPIO_REG_FEN(pin) = GPIO_PIN_MASK(pin);
	}

//----------------------------------------------------------------------------------------------------
// set gpio high level detect enable
//----------------------------------------------------------------------------------------------------
void gpio_hen(uint8_t pin)
	{
	__sync_synchronize(); // hardware memory barrier
	GPIO_REG_HEN(pin) = GPIO_PIN_MASK(pin);
	}

//----------------------------------------------------------------------------------------------------
// set gpio low level detect enable
//----------------------------------------------------------------------------------------------------
void gpio_len(uint8_t pin)
	{
	__sync_synchronize(); // hardware memory barrier
	GPIO_REG_LEN(pin) = GPIO_PIN_MASK(pin);
	}

//----------------------------------------------------------------------------------------------------
// set gpio asynchronous rising edge detect enable
//----------------------------------------------------------------------------------------------------
void gpio_aren(uint8_t pin)
	{
	__sync_synchronize(); // hardware memory barrier
	GPIO_REG_AREN(pin) = GPIO_PIN_MASK(pin);
	}

//----------------------------------------------------------------------------------------------------
// set gpio asynchronous falling edge detect enable
//----------------------------------------------------------------------------------------------------
void gpio_afen(uint8_t pin)
	{
	__sync_synchronize(); // hardware memory barrier
	GPIO_REG_AFEN(pin) = GPIO_PIN_MASK(pin);
	}


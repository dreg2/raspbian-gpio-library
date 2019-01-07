#ifndef GPIO_H
#define GPIO_H

/* gpio function select values */
#define GPIO_FSEL_INPUT  0
#define GPIO_FSEL_OUTPUT 1
#define GPIO_FSEL_ALT0   4
#define GPIO_FSEL_ALT1   5
#define GPIO_FSEL_ALT2   6
#define GPIO_FSEL_ALT3   7
#define GPIO_FSEL_ALT4   3
#define GPIO_FSEL_ALT5   2

// pud off, pull-down and pull-up
#define GPIO_PUD_OFF  0
#define GPIO_PUD_DOWN 1
#define GPIO_PUD_UP   2

// pin levels
#define GPIO_PIN_LOW   0
#define GPIO_PIN_HIGH  1

// functions
int8_t  gpio_init(void);
uint8_t gpio_fsel_get(uint8_t pin);
void    gpio_fsel_set(uint8_t pin, uint8_t fsel);
void    gpio_pud_set(uint8_t pin, uint8_t pud);
uint8_t gpio_level(uint8_t pin);
void    gpio_set(uint8_t pin);
void    gpio_clear(uint8_t pin);
uint8_t gpio_eds(uint8_t pin);
void    gpio_ren(uint8_t pin);
void    gpio_fen(uint8_t pin);
void    gpio_hen(uint8_t pin);
void    gpio_len(uint8_t pin);
void    gpio_aren(uint8_t pin);
void    gpio_afen(uint8_t pin);


// register pointers
extern volatile uint32_t *gpio_base; // gpio registers base pointer

// func registers start at 0x00 and hold 10 pin funcs @ 3 bits each, 2 msb are not used
#define GPIO_REG_FSEL(PIN)   (*(volatile uint32_t *)(gpio_base + ((PIN) / 10))) // register address
#define GPIO_FSEL_MASK       ((uint32_t)0x00000007)                             // mask for 3 bits
#define GPIO_FSEL_SHIFT(PIN) (((PIN) % 10) * 3)                                 // shift amount for mask to isolate pin bits

// other registers
// gpio base + offset + register number (0 or 1)
#define GPIO_PIN_MASK(PIN) ((uint32_t)(1 << ((PIN) & 0x1F))) // mask for pin value within register
#define GPIO_REG_SET(PIN)      (*(volatile uint32_t *)(gpio_base +  7 + ((PIN) >> 5)))
#define GPIO_REG_CLR(PIN)      (*(volatile uint32_t *)(gpio_base + 10 + ((PIN) >> 5)))
#define GPIO_REG_LEV(PIN)      (*(volatile uint32_t *)(gpio_base + 13 + ((PIN) >> 5)))
#define GPIO_REG_EDS(PIN)      (*(volatile uint32_t *)(gpio_base + 16 + ((PIN) >> 5)))
#define GPIO_REG_REN(PIN)      (*(volatile uint32_t *)(gpio_base + 19 + ((PIN) >> 5)))
#define GPIO_REG_FEN(PIN)      (*(volatile uint32_t *)(gpio_base + 22 + ((PIN) >> 5)))
#define GPIO_REG_HEN(PIN)      (*(volatile uint32_t *)(gpio_base + 25 + ((PIN) >> 5)))
#define GPIO_REG_LEN(PIN)      (*(volatile uint32_t *)(gpio_base + 28 + ((PIN) >> 5)))
#define GPIO_REG_AREN(PIN)     (*(volatile uint32_t *)(gpio_base + 31 + ((PIN) >> 5)))
#define GPIO_REG_AFEN(PIN)     (*(volatile uint32_t *)(gpio_base + 33 + ((PIN) >> 5)))
#define GPIO_REG_PUD           (*(volatile uint32_t *)(gpio_base + 37))
#define GPIO_REG_PUDCLK(PIN)   (*(volatile uint32_t *)(gpio_base + 38 + ((PIN) >> 5)))

#endif // GPIO_H

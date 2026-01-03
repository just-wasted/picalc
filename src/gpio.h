#pragma once

// pin modes for the function select registers
#define GPIO_INPUT 000  // GPIO Pin is an input
#define GPIO_OUTPUT 001 // GPIO Pin is an output
#define GPIO_ALT0 100   // GPIO Pin takes alternate function 0
#define GPIO_ALT1 101   // GPIO Pin takes alternate function 1
#define GPIO_ALT2 110   // GPIO Pin takes alternate function 2
#define GPIO_ALT3 111   // GPIO Pin takes alternate function 3
#define GPIO_ALT4 011   // GPIO Pin takes alternate function 4
#define GPIO_ALT5 010   // GPIO Pin takes alternate function 5

// pull-up / pull-down resistor states
#define GPIO_NOPUD 00     // No resistor is selected
#define GPIO_PULL_DOWN 01 // Pull up resistor is selected
#define GPIO_PULL_UP 10   // Pull down resistor is selected

#define HIGH 1
#define LOW 0

// returns -1 on error
int gpio_initialize(void);

void gpio_cleanup(void);

// takes a GPIO number and mode to set the pin to
void gpio_set_mode(unsigned gpio, unsigned char mode);

// takes a GPIO number and pull-up/ -down mode to set
void gpio_pud_mode(unsigned gpio, unsigned char pud_mode);

// takes a GPIO number and returns its level: 0 = LOW, 1 = HIGH
int gpio_read(unsigned gpio);

// takes a GPIO number and a level to set the pin
void gpio_write(unsigned gpio, unsigned char level);

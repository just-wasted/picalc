// Values to set pin modes for the function select registers
#define GPIO_INTPUT 000 // GPIO Pin is an input
#define GPIO_OUTPUT 001 // GPIO Pin is an output
#define GPIO_ALT0 100 // GPIO Pin takes alternate function 0
#define GPIO_ALT1 101 // GPIO Pin takes alternate function 1
#define GPIO_ALT2 110 // GPIO Pin takes alternate function 2
#define GPIO_ALT3 111 // GPIO Pin takes alternate function 3
#define GPIO_ALT4 011 // GPIO Pin takes alternate function 4
#define GPIO_ALT5 010 // GPIO Pin takes alternate function 5

// values for pull-up / pull-down resistor states
#define GPIO_NOPUD 00 // No resistor is selected
#define GPIO_PULL_DOWN 01 // Pull up resistor is selected
#define GPIO_PULL_UP 10 // Pull down resistor is selected

int gpioInitialise(void);

int gpioCleanup(void);

// takes a GPIO number and mode to set the pin to
void gpioSetMode(unsigned gpio, unsigned mode);

// Register offsets for pointer to uint32_t according
// to BCM2711 datasheet.
// Example: offset 0x1c -> 28 Byte / 4 = 7

// Register to set Output GPIOs HIGH
#define GPIO_SET_0 7

// Register to set Output GPIOIOs LOW
#define GPIO_CLR_0 10

// Register to read the level of GPIOIOs
#define GPIO_LEV_0 13

// Register to set pull-up / pull-down resistor
// for GPIOIOs 0..15
#define GPIO_PUD_0 57

// Register to set pull-up / pull-down resistor
// for GPIOs 16..31
#define GPIO_PUD_1 58

// Values for the function select registers
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

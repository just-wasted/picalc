#include "gpio.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

// register offsets for pointer to uint32_t according
// to BCM2711 datasheet. Example: offset 0x1c -> 28 Byte / 4 = 7

#define GPSET0 7  // Register to set Output GPIOs HIGH
#define GPCLR0 10 // Register to set Output GPIOs LOW
#define GPLEV0 13 // Register to read the level of GPIOs

// base register to set pull-up / pull-down resistors
// bcm GPIO_PUP_PDN_CNTRL_REG0
#define GPIO_PUD_0 57

// shift to to the desired bit by the gpio nr
// masked with 1F to ensure we stay in bounds
#define GPIO_BIT (1 << (gpio & 0x1F))

// size in Bytes of the memory to map all registers
// up to and including GPIO_PUP_PDN_CNTRL_REG1
#define MAP_SIZE 0xEC

// pointer to mapped gpio memory
static volatile uint32_t *gpio_reg = MAP_FAILED;

int gpio_initialize(void)
{
    // open the file kernel interface, NOTE: O_SYNC unnecessary?
    int gpio_fd = open("/dev/gpiomem", O_RDWR); // | O_SYNC);

    if (gpio_fd < 0)
    {
        fprintf(stderr, "Failed to open /dev/gpiomem\n");
        return -1;
    }
    // map the memory object gpio_fd into our process' adress space
    gpio_reg = (uint32_t *)mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE,
                                MAP_SHARED, gpio_fd, 0);

    close(gpio_fd);

    if (gpio_reg == MAP_FAILED)
    {
        fprintf(stderr, "Failed to map GPIO memory\n");
        return -1;
    }
    return 0;
}

void gpio_cleanup(void)
{
    munmap((void *)gpio_reg, MAP_SIZE);
    gpio_reg = NULL;
}

void gpio_set_mode(unsigned gpio, unsigned char pin_mode)
{
    // register offset for GPFSEL0 function select register
    // each register controls 10 gpios
    unsigned reg = gpio / 10;

    // every gpio has 3 bits in GPFSEL to set the function,
    // shift with a stepping of 3
    unsigned shift = (gpio % 10) * 3;

    // deref the register, set desired pin's mode bits to 0,
    // then set the new mode
    gpio_reg[reg] = (gpio_reg[reg] & ~(7 << shift)) | (pin_mode << shift);
}

unsigned char gpio_read_mode(unsigned gpio)
{
    // register offset for GPFSEL0 function select register
    // each register controls 10 gpios
    unsigned reg = gpio / 10;

    // every gpio has 3 bits in GPFSEL to set the function,
    // shift with a stepping of 3
    unsigned shift = (gpio % 10) * 3;

    // deref the register, apply mask to read mode bits
    unsigned mode = (gpio_reg[reg] & (7 << shift));

    return (unsigned char)(mode >> shift);
}

void gpio_set_pud_mode(unsigned gpio, unsigned char pud_mode)
{
    // register offset for GPIO_PUD_0 function select register
    // each register controls 15 gpios
    unsigned reg = gpio / 15;

    unsigned offset = GPIO_PUD_0 + reg;

    // shift stepping, 2 bits per GPIO pin
    unsigned shift = (gpio % 15) * 2;

    // deref the register, set desired pin's pull-up or -down mode bits to 0,
    // then set the new mode
    gpio_reg[offset] = (gpio_reg[offset] & ~(3 << shift)) | (pud_mode << shift);
}

unsigned char gpio_read_pud_mode(unsigned gpio)
{
    // register offset for GPIO_PUD_0 function select register
    // each register controls 15 gpios
    unsigned reg = gpio / 15;

    unsigned offset = GPIO_PUD_0 + reg;

    // shift stepping, 2 bits per GPIO pin
    unsigned shift = (gpio % 15) * 2;

    // deref the register, apply mask to read mode bits
    unsigned mode = (gpio_reg[offset] & (3 << shift));

    return (unsigned char)(mode >> shift);
}

int gpio_read_level(unsigned gpio)
{
    if ((*(gpio_reg + GPLEV0) & GPIO_BIT) == HIGH)
    {
        return HIGH;
    }
    return LOW;
}

void gpio_write_level(unsigned gpio, unsigned char level)
{
    if (level == LOW)
    {
        *(gpio_reg + GPCLR0) = GPIO_BIT;
    }
    else
    {
        *(gpio_reg + GPSET0) = GPIO_BIT;
    }
}

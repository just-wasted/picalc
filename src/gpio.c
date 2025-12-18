#include "gpio.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

// Register offsets for pointer to uint32_t according
// to BCM2711 datasheet.
// Example: offset 0x1c -> 28 Byte / 4 = 7

// Register to set Output GPIOs HIGH
#define GPIO_SET_0 7

// Register to set Output GPIOs LOW
#define GPIO_CLR_0 10

// Register to read the level of GPIOs
#define GPIO_LEV_0 13

// Register to set pull-up / pull-down resistor
// for GPIOIOs 0..15
#define GPIO_PUD_0 57

// Register to set pull-up / pull-down resistor
// for GPIOs 16..31
#define GPIO_PUD_1 58

// shift to to the desired bit by the gpio nr
// masked with 1F to ensure we stay in bounds
#define GPIO_BIT (1 << (gpio & 0x1F))

// size in Bytes of the memory to map all registers
// up to and including GPIO_PUP_PDN_CNTRL_REG1
#define MAP_SIZE 0xEC

// pointer to mapped gpio memory
static volatile uint32_t *gpioReg = MAP_FAILED;

int gpioInitialise(void)
{
    // open the file kernel interface, NOTE: O_SYNC unnecessary?
    int fd = open("/dev/gpiomem", O_RDWR); // | O_SYNC);

    if (fd < 0)
    {
        fprintf(stderr, "Failed to open /dev/gpiomem\n");
        return -1;
    }

    // map the memory object fd into our process adress space
    gpioReg = (uint32_t *)mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE,
                               MAP_SHARED, fd, 0);

    close(fd);

    if (gpioReg == MAP_FAILED)
    {
        fprintf(stderr, "Bad, mmap failed\n");
        return -1;
    }
    return 0;
}

int gpioCleanup(void)
{
    if (munmap((void *)gpioReg, MAP_SIZE) < 0)
    {
        fprintf(stderr, "Memory deallocation of GPIO registers failed\n");
        return -1;
    }
    return 0;
}

void gpioSetMode(unsigned gpio, unsigned mode)
{
    // calculate register offset for GPFSEL function select register
    // each register controls 10 gpios
    int reg = gpio / 10;

    // every gpio has 3 bits in GPFSEL to set the function
    // shift with a stepping of 3
    int shift = (gpio % 10) * 3;

    // deref the register, set desired pin's mode bits to 0, then set the new
    // mode
    gpioReg[reg] = (gpioReg[reg] & ~(7 << shift)) | (mode << shift);
}

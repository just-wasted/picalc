#include "gpio.h"
#include "lcd.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{

    if (gpio_initialize() == -1)
    {
        return -1;
    }
    if (gpio_cleanup() == -1)
    {
        return -1;
    }
    printf("Hello, pi\n");
    return 0;
}

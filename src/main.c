#include "gpio.h"
#include <stdio.h>

int main(void)
{
    if (gpioInitialise() == -1)
    {
        return -1;
    }
    if (gpioCleanup() == -1)
    {
        return -1;
    }
    printf("Hello, pi");
    return 0;
}

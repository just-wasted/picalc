#include "gpio.h"
#include "keypad.h"
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

    init_keypad();

    gpio_cleanup();
    printf("Hello, pi\n");
    return 0;
}

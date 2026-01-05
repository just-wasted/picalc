#include "gpio.h"
#include "keypad.h"
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    lcd_init();

    if (gpio_initialize() == -1)
    {
        return EXIT_FAILURE;
    }

    keypad_t kp_0 = {
        .keys = {{'1', '2', '3', 'A'},
                 {'4', '5', '6', 'B'},
                 {'7', '8', '9', 'C'},
                 {'E', '0', 'F', 'D'}},

        .gpio_rows = {5, 6, 13, 19},
        .gpio_cols = {26, 16, 20, 21},
    };

    if (keypad_init(&kp_0) == -1)
    {
        return EXIT_FAILURE;
    }

    gpio_cleanup();
    printf("Hello, pi\n");
    return EXIT_SUCCESS;
}

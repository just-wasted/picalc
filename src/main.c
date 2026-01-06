#include "gpio.h"
#include "keypad.h"
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

keypad_t kp_0 = {
    .keys = {{'1', '2', '3', 'A'},
             {'4', '5', '6', 'B'},
             {'7', '8', '9', 'C'},
             {'E', '0', 'F', 'D'}},

    .gpio_rows = {5, 6, 13, 19},
    .gpio_cols = {26, 16, 20, 21},
};

char get_pi_char(void);

int main(void)
{
    lcd_init();

    if (gpio_initialize() == -1)
    {
        return EXIT_FAILURE;
    }

    if (keypad_init(&kp_0) == -1)
    {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 16; i++)
    {
        char val = get_pi_char();
        lcd_write_char(val);
    }

    if (keypad_cleanup(&kp_0) == -1)
    {
        return EXIT_FAILURE;
    }

    lcd_cleanup();
    gpio_cleanup();
    printf("Hello, pi\n");
    return EXIT_SUCCESS;
}

char get_pi_char(void)
{
    char input = 0;

    while (input == 0)
    {
        usleep(200);
        input = read_keypad(&kp_0);
    }
    return input;
}

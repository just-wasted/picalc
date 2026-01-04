#include "keypad.h"
#include "gpio.h"
#include <stdio.h>
#include <unistd.h>

// GPIO numbers for keypad rows
const int gpio_rows[4] = {5, 6, 13, 19};

// GPIO numbers for keypad columns
const int gpio_cols[4] = {26, 16, 20, 21};

int init_keypad(void)
{
    for (int i = 0; i < 4; i++)
    {
        gpio_set_mode(gpio_rows[i], GPIO_OUTPUT);
        gpio_set_mode(gpio_cols[i], GPIO_INPUT);
        gpio_set_pud_mode(gpio_cols[i], GPIO_PULL_DOWN);
    }
    usleep(1000);

    // check if above settings applied successfully
    for (int i = 0; i < 4; i++)
    {
        if (gpio_read_mode(gpio_rows[i]) != GPIO_OUTPUT)
        {
            fprintf(stderr, "Failed to set GPIO %d to OUTPUT", gpio_rows[i]);
            return -1;
        }
        if (gpio_read_mode(gpio_cols[i]) != GPIO_INPUT)
        {
            fprintf(stderr, "Failed to set GPIO %d to INPUT", gpio_cols[i]);
            return -1;
        }
        if (gpio_read_pud_mode(gpio_cols[i]) != GPIO_PULL_DOWN)
        {
            fprintf(stderr, "Failed to set PULL DOWN for GPIO %d",
                    gpio_cols[i]);
            return -1;
        }
    }

    return 0;
}

int get_key(void)
{
    return 0;
}

#include "keypad.h"
#include "gpio.h"

// GPIO numbers for keypad rows
const int gpio_rows[4] = {5, 6, 13, 19};

// GPIO numbers for keypad columns
const int gpio_cols[4] = {26, 16, 20, 21};

void init_keypad(void)
{
    for (int i = 0; i < 4; i++)
    {
        gpio_set_mode(gpio_rows[i], GPIO_OUTPUT);
        gpio_set_mode(gpio_cols[i], GPIO_INPUT);
        gpio_set_pud_mode(gpio_cols[i], GPIO_PULL_DOWN);
    }
}

int get_key(void)
{
    return 0;
}

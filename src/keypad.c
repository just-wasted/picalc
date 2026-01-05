#include "keypad.h"
#include "gpio.h"
#include <stdio.h>
#include <unistd.h>

int keypad_init(keypad_t *kp)
{
    for (int i = 0; i < 4; i++)
    {
        gpio_set_mode(kp->gpio_rows[i], GPIO_OUTPUT);
        gpio_set_mode(kp->gpio_cols[i], GPIO_INPUT);
        gpio_set_pud_mode(kp->gpio_cols[i], GPIO_PULL_DOWN);
    }
    usleep(1000);

    // check if above settings applied successfully
    int ret_val = 0;
    for (int i = 0; i < 4; i++)
    {
        if (gpio_read_mode(kp->gpio_rows[i]) != GPIO_OUTPUT)
        {
            fprintf(stderr, "Failed to set GPIO %d to OUTPUT",
                    kp->gpio_rows[i]);

            ret_val = -1;
        }
        if (gpio_read_mode(kp->gpio_cols[i]) != GPIO_INPUT)
        {
            fprintf(stderr, "Failed to set GPIO %d to INPUT", kp->gpio_cols[i]);

            ret_val = -1;
        }
        if (gpio_read_pud_mode(kp->gpio_cols[i]) != GPIO_PULL_DOWN)
        {
            fprintf(stderr, "Failed to set PULL DOWN for GPIO %d",
                    kp->gpio_cols[i]);

            ret_val = -1;
        }
    }
    return ret_val;
}

int get_key(void)
{
    return 0;
}

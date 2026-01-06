#include "keypad.h"
#include "gpio.h"
#include <stdio.h>
#include <unistd.h>

#define DEBOUNCE_USEC 10000
#define SLEEP_USEC 300

int keypad_init(keypad_t *kp)
{
    for (int i = 0; i < 4; i++)
    {
        gpio_set_mode(kp->gpio_rows[i], GPIO_OUTPUT);
        gpio_set_mode(kp->gpio_cols[i], GPIO_INPUT);
        gpio_set_pud_mode(kp->gpio_cols[i], GPIO_PULL_DOWN);
    }
    usleep(SLEEP_USEC);

    // check if above settings applied successfully
    int ret_val = 0;
    for (int i = 0; i < 4; i++)
    {
        if (gpio_read_mode(kp->gpio_rows[i]) != GPIO_OUTPUT)
        {
            fprintf(stderr, "keypad init: Failed to set GPIO %d to OUTPUT\n",
                    kp->gpio_rows[i]);

            ret_val = -1;
        }
        if (gpio_read_mode(kp->gpio_cols[i]) != GPIO_INPUT)
        {
            fprintf(stderr, "keypad init: Failed to set GPIO %d to INPUT\n",
                    kp->gpio_cols[i]);

            ret_val = -1;
        }
        if (gpio_read_pud_mode(kp->gpio_cols[i]) != GPIO_PULL_DOWN)
        {
            fprintf(stderr,
                    "keypad init: Failed to set PULL DOWN for GPIO %d\n",
                    kp->gpio_cols[i]);

            ret_val = -1;
        }
    }
    return ret_val;
}

int keypad_cleanup(keypad_t *kp)
{
    for (int i = 0; i < 4; i++)
    {
        gpio_write_level(kp->gpio_rows[i], LOW);
        gpio_set_mode(kp->gpio_rows[i], GPIO_INPUT);
        gpio_set_pud_mode(kp->gpio_rows[i], GPIO_PULL_DOWN);
    }
    usleep(SLEEP_USEC);

    // check if above settings applied successfully
    int ret_val = 0;
    for (int i = 0; i < 4; i++)
    {
        if (gpio_read_level(kp->gpio_rows[i]) != LOW)
        {
            fprintf(stderr,
                    "keypad cLeanup: Failed to set GPIO %d to level LOW\n",
                    kp->gpio_rows[i]);

            ret_val = -1;
        }
        if (gpio_read_mode(kp->gpio_rows[i]) != GPIO_INPUT)
        {
            fprintf(stderr, "keypad cLeanup: Failed to set GPIO %d to INPUT\n",
                    kp->gpio_cols[i]);

            ret_val = -1;
        }
        if (gpio_read_pud_mode(kp->gpio_rows[i]) != GPIO_PULL_DOWN)
        {
            fprintf(stderr,
                    "keypad cLeanup: Failed to set PULL DOWN for GPIO %d\n",
                    kp->gpio_cols[i]);

            ret_val = -1;
        }
    }
    return ret_val;
}

char read_keypad(keypad_t *kp)
{
    for (int current_row = 0; current_row < 4; current_row++)
    {
        // set current_row HIGH, all other rows LOW
        for (int i = 0; i < 4; i++)
        {
            if (i == current_row)
            {
                gpio_write_level(kp->gpio_rows[i], HIGH);
            }
            else
            {
                gpio_write_level(kp->gpio_rows[i], LOW);
            }
        }
        usleep(SLEEP_USEC);

        for (int curren_col = 0; curren_col < 4; curren_col++)
        {
            if (gpio_read_level(kp->gpio_cols[curren_col]) == HIGH)
            {
                // wait till button is released
                do
                {
                    usleep(DEBOUNCE_USEC);
                } while (gpio_read_level(kp->gpio_cols[curren_col]) == HIGH);

                // debounce button release
                usleep(DEBOUNCE_USEC);

                return kp->keys[current_row][curren_col];
            }
            usleep(DEBOUNCE_USEC);
        }
    }
    return 0;
}

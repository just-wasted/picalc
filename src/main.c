#include "gpio.h"
#include "history.h"
#include "keypad.h"
#include "lcd.h"
#include "srledit.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

keypad_t kp_0 = {
    .keys = {{'1', '2', '3', 'A'},
             {'4', '5', '6', 'B'},
             {'7', '8', '9', 'C'},
             {'E', '0', 'F', 'D'}},

    .keys_alt = {{0}},

    .gpio_rows = {5, 6, 13, 19},
    .gpio_cols = {26, 16, 20, 21},
};

keypad_t kp_1 = {
    .keys = {{'+', '-', '*', '/'},
             {DEL, '^', SQR, ALT},
             {'(', HUP, ')', '.'},
             {'<', HDO, '>', '='}},

    .keys_alt = {[0] = {0, 0, 0, '%'}, [1] = {0, 0, 0, ALT}},

    .gpio_rows = {4, 17, 27, 22},
    .gpio_cols = {23, 24, 25, 12},
};

int main(void)
{

    if (lcd_init() == -1)
    {
        return EXIT_FAILURE;
    }

    if (gpio_initialize() == -1)
    {
        return EXIT_FAILURE;
    }

    if (keypad_init(&kp_0) == -1)
    {
        return EXIT_FAILURE;
    }

    if (keypad_init(&kp_1) == -1)
    {
        return EXIT_FAILURE;
    }

    char *input = get_input(&kp_0, &kp_1);
    if (input == NULL)
    {
        return EXIT_FAILURE;
    }

    printf("%s\n", input);

    free(input);

    if (keypad_cleanup(&kp_0) == -1)
    {
        return EXIT_FAILURE;
    }

    history_cleanup();
    lcd_cleanup();
    gpio_cleanup();
    return EXIT_SUCCESS;
}

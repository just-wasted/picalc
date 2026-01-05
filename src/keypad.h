#pragma once

typedef struct
{
    const char keys[4][4];  // list of characters assigned to each key
    const int gpio_rows[4]; // GPIO pin numbers wired to keypad rows
    const int gpio_cols[4]; // GPIO pin numbers wired to keypad columns
} keypad_t;
//
// example key layout
// 	'1', '2', '3', 'A',
// 	'4', '5', '6', 'B',
// 	'7', '8', '9', 'C',
// 	'E', '0', 'F', 'D'

// receives a configured keypad_t to setup GPIO, returns -1 on failure
int keypad_init(keypad_t *kp);

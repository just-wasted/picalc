#pragma once

#define KP_WIDTH 4

/*
contains data representing a keypad
*/
typedef struct keypad_t
{
    // list of characters assigned to each key
    const char keys[KP_WIDTH][KP_WIDTH];
    // list of alt chars assigned to each key
    const char keys_alt[KP_WIDTH][KP_WIDTH];
    const int gpio_rows[KP_WIDTH]; // GPIO pin numbers wired to keypad rows
    const int gpio_cols[KP_WIDTH]; // GPIO pin numbers wired to keypad columns
} keypad_t;

/*
receives a keypad_t to setup GPIOs,
returns -1 on failure
*/
int keypad_init(keypad_t *kp);

/*
receives a keypad_t to cleanup GPIOs, returns -1 on failure,
resets GPIOs to default settings (INPUT, PULL_DOWN, level LOW)
*/
int keypad_cleanup(keypad_t *kp);

/*
receives a keypad_t to read pressed keys,
returns the char associated with the pressed key
or 0 if no key was pressed
*/
char read_keypad(keypad_t *kp);

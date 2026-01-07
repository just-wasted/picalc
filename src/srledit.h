#pragma once

#include "keypad.h"

#define INPUT_BUFFER_SIZE 256

/*
custom key codes
*/
#define HDO -12 // search history down
#define HUP -16 // search history up
#define ALT -18 // toggle ALT mode
#define SQR -19 // square root
#define DEL -21 // delete char

typedef struct string_t
{
    char str[INPUT_BUFFER_SIZE]; // string data
    unsigned len;                // the length of data including null terminator
    unsigned cursor_pos;         // index in str of cursor position
} string_t;

/*
receives pointers to input nodes,
returns a string which must be freed,
appends history which must be freed with history_cleanup,
*/
char *get_input(keypad_t *kp_0_ptr, keypad_t *kp_1_ptr);

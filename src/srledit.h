#pragma once

#include "keypad.h"

#define INPUT_BUFFER_SIZE 256

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

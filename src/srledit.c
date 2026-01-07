#include "srledit.h"
#include "history.h"
#include "keypad.h"
#include "lcd.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

string_t *new_input_str(void);

/*
receives buffer and char to insert or append.
apends null terminator.
*/
int insert_char(string_t *buffer, int in_char);

/*
receives a buffer and removes the char before the current cursor position
*/
int remove_char(string_t *buffer);

char *get_input(keypad_t *kp_0_ptr, keypad_t *kp_1_ptr)
{
    string_t *input_str = new_input_str();
    if (input_str == NULL)
    {
        return NULL;
    }

    while (1)
    {

        signed char input_chr = 0;

        while (input_chr == 0)
        {
            usleep(100);
            input_chr = read_keypad(kp_0_ptr);
            if (input_chr)
            {
                break;
            }
            input_chr = read_keypad(kp_1_ptr);
        }

        int flag_processed = 0;

        switch (input_chr)
        {
        case '=':
            char *return_str = malloc(sizeof(char) * input_str->len);
            if (return_str == NULL)
            {
                fprintf(stderr, "Error allocating memory for return_str");
                fflush(stderr);
                return NULL;
            }

            strcpy(return_str, input_str->str);
            history_add(input_str);
            input_str = NULL;
            return return_str;

        case '>':
            lcd_shift_cursor_right();
            flag_processed = 1;
            break;

        case '<':
            lcd_shift_cursor_left();
            lcd_shift_cursor_left();
            flag_processed = 1;
            break;

        case ALT:
            toggle_alt_mode();
            flag_processed = 1;
            break;

        case DEL:
            if (remove_char(input_str) == 0)
            {
                lcd_shift_cursor_left();
                lcd_write_char(' ');
                lcd_shift_cursor_left();
            }
            flag_processed = 1;
            break;
        }

        if (!flag_processed)
        {
            lcd_write_char(input_chr);
            insert_char(input_str, input_chr);
        }
    }
}

int insert_char(string_t *buffer, int in_char)
{
    if (buffer->len >= INPUT_BUFFER_SIZE)
    {
        return 0; // do nothing if the buffer is full
    }

    // check if cursor is at the end of the string
    if (buffer->str[buffer->cursor_pos] == '\0')
    {
        buffer->str[buffer->cursor_pos + 1] = '\0';
        buffer->str[buffer->cursor_pos] = (char)in_char;
        buffer->cursor_pos++;
        buffer->len++;
    }
    // TODO: check if cursor is not at \0 and shift buffer contents accordingly
    return 0;
}

int remove_char(string_t *buffer)
{
    if (buffer->len <= 1)
    {
        return 1; // do nothing of there is no string data to remove
    }

    // check if cursor is at the end of the string
    if (buffer->str[buffer->cursor_pos] == '\0')
    {
        buffer->str[buffer->cursor_pos - 1] = '\0';
        buffer->str[buffer->cursor_pos] = ' ';
        buffer->cursor_pos--;
        buffer->len--;
    }

    // TODO: check if cursor is not at \0 and shift buffer contents accordingly
    return 0;
}

string_t *new_input_str(void)
{
    string_t *new = malloc(sizeof(string_t));
    if (new == NULL)
    {
        fprintf(stderr, "Error allocating memory in new_input_str()");
        fflush(stderr);
        return NULL;
    }
    new->cursor_pos = 0;
    new->len = 1;
    new->str[0] = '\0';
    return new;
}

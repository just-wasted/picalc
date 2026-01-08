#include "srledit.h"
#include "history.h"
#include "keypad.h"
#include "lcd.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEFT 0
#define RIGHT 1

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

void str_move_cursor(string_t *buffer, unsigned direction);

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
            str_move_cursor(input_str, RIGHT);
            flag_processed = 1;
            break;

        case '<':
            str_move_cursor(input_str, LEFT);
            flag_processed = 1;
            break;

        case ALT:
            toggle_alt_mode();
            flag_processed = 1;
            break;

        case DEL:
            remove_char(input_str);
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

void str_move_cursor(string_t *buffer, unsigned direction)
{
    char cursor_char = buffer->str[buffer->cursor_pos];

    switch (direction)
    {
    case LEFT:
        if (buffer->cursor_pos == 0)
        {
            return;
        }
        lcd_shift_cursor_left();
        buffer->cursor_pos--;
        break;

    case RIGHT:
        if (cursor_char == '\0')
        {
            return;
        }
        lcd_shift_cursor_right();
        buffer->cursor_pos++;
        break;
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
    else // shift buffer contents to the right and insert char
    {
        unsigned shift_cursor = buffer->len - 1;
        unsigned stop_cursor = buffer->cursor_pos - 1;

        while (shift_cursor != stop_cursor)
        {
            buffer->str[shift_cursor + 1] = buffer->str[shift_cursor];
            shift_cursor--;
        }
        buffer->str[buffer->cursor_pos] = (char)in_char;
        buffer->cursor_pos++;
        buffer->len++;

        lcd_display_clear();
        lcd_write_str(buffer->str);
        lcd_goto(buffer->cursor_pos, 0);
    }
    return 0;
}

int remove_char(string_t *buffer)
{
    if (buffer->len <= 1)
    {
        return 1; // do nothing of there is no string data to remove
    }

    // delete char if cursor is at the end of the string
    if (buffer->str[buffer->cursor_pos] == '\0')
    {
        buffer->str[buffer->cursor_pos - 1] = '\0';
        buffer->str[buffer->cursor_pos] = ' ';
        buffer->cursor_pos--;
        buffer->len--;
        lcd_shift_cursor_left();
        lcd_write_char(' ');
        lcd_shift_cursor_left();
    }
    else // shift buffer contents to the left
    {
        unsigned shift_cursor = buffer->cursor_pos;
        unsigned stop_cursor = buffer->len;

        while (shift_cursor != stop_cursor)
        {
            buffer->str[shift_cursor - 1] = buffer->str[shift_cursor];
            shift_cursor++;
        }
        buffer->cursor_pos--;
        buffer->len--;

        lcd_display_clear();
        lcd_write_str(buffer->str);
        lcd_goto(buffer->cursor_pos, 0);
    }
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

#include "ui.h"
#include "lcd.h"
#include <stdio.h>
#include <string.h>

#define OUTPUT_BUFFER_SIZE 256

typedef struct line_buffer_t
{
    char data[OUTPUT_BUFFER_SIZE]; // whole content of the buffer
    int frame_start;               // start of view frame
    int len;                       // length of stored string data
} line_buffer_t;

static line_buffer_t eval_buffer;

int ui_store_eval(char *str)
{
    // add 2 for '= '
    int len = (int)strlen(str) + 2;

    if (len > OUTPUT_BUFFER_SIZE)
    {
        fprintf(stderr, "Evaluation too large to fit in output buffer: %d\n",
                len);
        fflush(stderr);

        return -1;
    }

    snprintf(eval_buffer.data, OUTPUT_BUFFER_SIZE, "= %s", str);

    eval_buffer.len = len;

    eval_buffer.frame_start = 0;

    printf("buffer_content: %s", eval_buffer.data);
    return 0;
}

void ui_print_eval(void)
{
    lcd_clear_line(0);

    char print_buffer[LCD_COLS + 1];

    int i = eval_buffer.frame_start;
    int frame_end;

    if (eval_buffer.len > LCD_COLS)
    {
        frame_end = eval_buffer.frame_start + LCD_COLS;
        for (; i < frame_end; i++)
        {
            print_buffer[i] = eval_buffer.data[i];
        }

        print_buffer[LCD_COLS] = '\0';
    }
    else
    {
        frame_end = eval_buffer.frame_start + eval_buffer.len;
        for (; i < frame_end; i++)
        {
            print_buffer[i] = eval_buffer.data[i];
        }

        print_buffer[eval_buffer.len] = '\0';
    }

    lcd_write_str(print_buffer);
}

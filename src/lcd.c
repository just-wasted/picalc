#include "lcd.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LCD_IF "/dev/lcd"

#define BL_ON "\e[L+"
#define BL_OFF "\e[L-"

#define DISPLAY_CLEAR '\f'

#define CURSOR_ON "\e[LC"
#define CURSOR_OFF "\e[Lc"

#define BLINK_ON "\e[LB"
#define BLINK_OFF "\e[Lb"

#define SHIFT_CURSOR_R "\e[Lr"
#define SHIFT_CURSOR_L "\e[Ll"

#define SHIFT_DISPLAY_R "\e[LR"
#define SHIFT_DISPLAY_L "\e[LL"

#define SMALL_FONT "\e[Lf"
#define LARGE_FONT "\e[LF"

#define GO_LINE(y) "\e[Ly" #y ";"
#define GO_COLUMN(x) "\e[Lx" #x ";"

static int lcd_fd = -1;

int lcd_init(void)
{
    int lcd_fd = -1;
    lcd_fd = open(LCD_IF, O_WRONLY);
    if (lcd_fd < 0)
    {
        perror("Error opening display");
        return -1;
    }

    lcd_display_clear();
    lcd_bl_on();
    lcd_cursor_on();

    return 0;
}

void lcd_cleanup(void)
{
    lcd_blink_off();
    lcd_cursor_off();
    lcd_bl_off();
    close(lcd_fd);
}

int lcd_write_str(char *str)
{
    if (write(lcd_fd, str, strlen(str)) == -1)
    {
        fprintf(stderr, "Error writing string to lcd: %s\n", str);
        return -1;
    }
    usleep(200);
    return 0;
}

int lcd_write_char(char chr)
{
    char str[2];
    str[0] = chr;
    str[1] = '\0';

    if (write(lcd_fd, str, strlen(str)) == -1)
    {
        fprintf(stderr, "Error writing char to lcd: %s\n", str);
        return -1;
    }
    usleep(200);
    return 0;
}

void lcd_display_clear(void)
{
    lcd_write_char(DISPLAY_CLEAR);
    usleep(200);
}

void lcd_bl_on(void)
{
    lcd_write_str(BL_ON);
    usleep(200);
}

void lcd_bl_off(void)
{
    lcd_write_str(BL_OFF);
    usleep(200);
}

void lcd_cursor_on(void)
{
    lcd_write_str(CURSOR_ON);
    usleep(200);
}

void lcd_cursor_off(void)
{
    lcd_write_str(CURSOR_OFF);
    usleep(200);
}

void lcd_blink_on(void)
{
    lcd_write_str(BLINK_ON);
    usleep(200);
}

void lcd_blink_off(void)
{
    lcd_write_str(BLINK_OFF);
    usleep(200);
}

void lcd_goto(int x, int y)
{
    char str[32];
    sprintf(str, "\e[Lx%dy%d;", x, y);
    lcd_write_str(str);
}

void lcd_schift_cursor_right(void)
{
    lcd_write_str(SHIFT_CURSOR_R);
}

void lcd_schift_cursor_left(void)
{
    lcd_write_str(SHIFT_CURSOR_L);
}

void lcd_schift_display_right(void)
{
    lcd_write_str(SHIFT_DISPLAY_R);
}

void lcd_schift_display_left(void)
{
    lcd_write_str(SHIFT_DISPLAY_L);
}

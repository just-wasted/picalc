#include "lcd.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LCD_IF "/dev/lcd"

#define BL_ON "\e[L+"
#define BL_OFF "\e[L-"
#define DISPLAY_CLEAR '\f'

static int lcd_fd = -1;

int lcd_init(void)
{
    lcd_fd = open(LCD_IF, O_WRONLY);
    if (lcd_fd < 0)
    {
        perror("Error opening display");
        return -1;
    }

    lcd_display_clear();
    lcd_bl_on();
    return 0;
}

void lcd_cleanup(void)
{
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
    return 0;
}

void lcd_display_clear(void)
{
    lcd_write_char(DISPLAY_CLEAR);
}

void lcd_bl_on(void)
{
    lcd_write_str(BL_ON);
}

void lcd_bl_off(void)
{
    lcd_write_str(BL_OFF);
}

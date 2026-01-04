#include "lcd.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LCD_IF "/dev/lcd"

#define BL_ON "\e[L+"
#define BL_OFF "\e[L-"

static int lcd_fd = -1;

int lcd_init(void)
{
    lcd_fd = open(LCD_IF, O_WRONLY);
    if (lcd_fd < 0)
    {
        perror("Error opening display");
        return 1;
    }

    return 0;
}

void lcd_cleanup(void)
{
    lcd_bl_off();
    close(lcd_fd);
}

void lcd_bl_on(void)
{
    write(lcd_fd, BL_ON, strlen(BL_ON));
}

void lcd_bl_off(void)
{
    write(lcd_fd, BL_OFF, strlen(BL_OFF));
}

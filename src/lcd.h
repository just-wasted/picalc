#pragma once

/*
initializes the lcd,
returns -1 on error
*/
int lcd_init(void);

/*
closes the file descriptor of the lcd,
turn backlight off
*/
void lcd_cleanup(void);

/*
receives a char to write to the lcd fd,
returns -1 on error
*/
int lcd_write_char(char chr);

/*
receives a string to write to the lcd fd,
returns -1 on error
*/
int lcd_write_str(char *str);

void lcd_display_clear(void);

void lcd_bl_on(void);

void lcd_bl_off(void);

#pragma once

/*
initializes the lcd,
returns -1 on error
*/
int lcd_init(void);

/*
closes the file descriptor of the lcd,
disables the cursor,
turns backlight off
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

void lcd_cursor_on(void);
void lcd_cursor_off();

void lcd_blink_on(void);
void lcd_blink_off(void);

/*
moves the cursor to position x y
*/
void lcd_goto(int x, int y);

void lcd_schift_cursor_right(void);
void lcd_schift_cursor_left(void);

void lcd_schift_display_right(void);
void lcd_schift_display_left(void);

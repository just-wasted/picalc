#include "state.h"
#include "lcd.h"

static int alt_mode = 0;

int get_alt_mode(void)
{
    return alt_mode;
}

void toggle_alt_mode(void)
{
    if (!alt_mode)
    {
        alt_mode = 1;
        lcd_blink_on();
    }
    else
    {
        alt_mode = 0;
        lcd_blink_off();
    }
}

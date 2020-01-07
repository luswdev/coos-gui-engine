/**
 *******************************************************************************
 * @file       font.h
 * @version    V0.0.1
 * @date       2019.12.3
 * @brief      Font define file.
 *******************************************************************************
 */ 

#ifndef _COGUI_FONT_H
#define _COGUI_FONT_H

struct cogui_font {
    char *                      family;
    co_uint16_t                 width;
    co_uint16_t                 height;
    const co_uint16_t *         data;
};
typedef struct cogui_font cogui_font_t;

extern cogui_font_t tm_font_7x10;
extern cogui_font_t tm_font_11x18;
extern cogui_font_t tm_font_16x26;

void cogui_lcd_puts(co_uint16_t x, co_uint16_t y, char *str, cogui_font_t *font, cogui_widget_t *widget);
void cogui_lcd_putc(co_uint16_t x, co_uint16_t y, char c, cogui_font_t *font, cogui_widget_t *widget);

#define cogui_tm_7x10_puts(x, y, s, w) cogui_lcd_puts((x), (y), (s), &tm_font_7x10, (w))
#define cogui_tm_11x18_puts(x, y, s, w) cogui_lcd_puts((x), (y), (s), &tm_font_11x18, (w))
#define cogui_tm_16x26_puts(x, y, s, w) cogui_lcd_puts((x), (y), (s), &tm_font_16x26, (w))
#define cogui_tm_16x26_putc(x, y, c, w) cogui_lcd_putc((x), (y), (c), &tm_font_16x26, (w))

#endif /* _COGUI_FONT_H */

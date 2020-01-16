/**
 *******************************************************************************
 * @file       font.h
 * @version    V0.1.0
 * @date       2020.01.15
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

void cogui_lcd_puts(co_uint16_t x, co_uint16_t y, char *str, cogui_font_t *font, cogui_dc_t *dc, cogui_rect_t *rect);
void cogui_lcd_putc(co_uint16_t x, co_uint16_t y, char c, cogui_font_t *font, cogui_dc_t *dc, cogui_rect_t *rect);

#define cogui_tm_7x10_puts(x, y, s, d, r) cogui_lcd_puts((x), (y), (s), &tm_font_7x10, (d), (r))
#define cogui_tm_11x18_puts(x, y, s, d, r) cogui_lcd_puts((x), (y), (s), &tm_font_11x18, (d), (r))
#define cogui_tm_16x26_puts(x, y, s, d, r) cogui_lcd_puts((x), (y), (s), &tm_font_16x26, (d), (r))
#define cogui_tm_16x26_putc(x, y, c, d, r) cogui_lcd_putc((x), (y), (c), &tm_font_16x26, (d), (r))

co_uint32_t cogui_get_text_width(char *str, cogui_font_t *font);
co_uint32_t cogui_get_text_height(char *str, cogui_font_t *font, cogui_rect_t *rect);

#endif /* _COGUI_FONT_H */

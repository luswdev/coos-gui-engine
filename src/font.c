/**
 *******************************************************************************
 * @file       font.c
 * @version    V0.1.1
 * @date       2020.01.15
 * @brief      Font function file.
 *******************************************************************************
 */ 

#include "cogui.h"

cogui_font_t *default_font = &tm_font_7x10;

void cogui_lcd_puts(co_uint16_t x, co_uint16_t y, char *str, cogui_font_t *font, cogui_dc_t *dc, cogui_rect_t *rect)
{
    while (*str) {
        if (*str == '\n') {
			y += font->height;
            x = rect->x1;
			
			str++;
			continue;
		}

        cogui_lcd_putc(x, y, *str++, font, dc, rect);

        x += font->width;

        if (x + font->width > rect->x2) {
            y += font->height;
            x = rect->x1;
	    }
    }
}

void cogui_lcd_putc(co_uint16_t x, co_uint16_t y, char c, cogui_font_t *font, cogui_dc_t *dc, cogui_rect_t *rect)
{	
	co_uint16_t i, j, f;
	for ( i=0; i<font->height; i++) {
		/* first element in font table is "space", which is 32 in ASCII */
		f = font->data[(c - 32)*font->height + i];
		for ( j=0; j<font->width; j++) {
			if ((f << j) & 0x8000) {
				dc->engine->draw_point(dc, x+j, y+i);
			}
		}
	}
}

co_uint32_t cogui_get_text_width(char *str, cogui_font_t *font)
{
    co_uint32_t text_width;
    co_uint64_t str_len = str != Co_NULL ? cogui_strlen(str) : 0;

    COGUI_ASSERT(font != Co_NULL);
    text_width = str_len * font->width;

    return text_width;
}

co_uint32_t cogui_get_text_height(char *str, cogui_font_t *font, cogui_rect_t *rect)
{
    /* how many lines does this text has in this rectangle */
    COGUI_ASSERT(rect != Co_NULL);
    co_uint32_t rect_width = COGUI_RECT_WIDTH(rect);
    co_uint32_t text_width = cogui_get_text_width(str, font);
    co_uint32_t lines = text_width / rect_width + 1;

    /* compute text height */
    co_uint32_t text_height;

    COGUI_ASSERT(font != Co_NULL);
    text_height = lines * font->height;

    return text_height;
}

/**
 *******************************************************************************
 * @file       font.c
 * @version    V0.1.0
 * @date       2019.12.11
 * @brief      Font function file.
 *******************************************************************************
 */ 

#include "cogui.h"

cogui_font_t *default_font = &tm_font_7x10;

void cogui_lcd_puts(co_uint16_t x, co_uint16_t y, char *str, cogui_font_t *font, cogui_widget_t *widget)
{
    cogui_rect_t *rect = &widget->inner_extent;

    while (*str) {
        if (*str == '\n') {
			y += font->height;
            x = rect->x1;
			
			str++;
			continue;
		}

        cogui_lcd_putc(x, y, *str++, font, widget);

        x += font->width;

        if (x + font->width > rect->x2) {
            y += font->height;
            x = rect->x1;
	    }
    }
}

void cogui_lcd_putc(co_uint16_t x, co_uint16_t y, char c, cogui_font_t *font, cogui_widget_t *widget)
{
    cogui_dc_t   *dc   = widget->dc_engine;
	
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

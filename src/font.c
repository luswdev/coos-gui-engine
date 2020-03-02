/**
 *******************************************************************************
 * @file       font.c
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      Font function file.
 *******************************************************************************
 */ 

#include "cogui.h"

cogui_font_t *default_font = &tm_font_7x10;

/**
 *******************************************************************************
 * @brief      Display string to screen.
 * @param[in]  x        Logical x to rect.
 * @param[in]  y        Logical y to rect.
 * @param[in]  *str     String to display.
 * @param[in]  *font    Which font to use.
 * @param[in]  *dc      Using this DC engine.
 * @param[in]  *rect    Where to draw the string.
 * @param[out] None
 * @retval     None 
 *******************************************************************************
 */
void cogui_lcd_puts(uint16_t x, uint16_t y, char *str, cogui_font_t *font, cogui_dc_t *dc, cogui_rect_t *rect)
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

/**
 *******************************************************************************
 * @brief      Display a character to screen.
 * @param[in]  x        Logical x to rect.
 * @param[in]  y        Logical y to rect.
 * @param[in]  c        Character to display.
 * @param[in]  *font    Which font to use.
 * @param[in]  *dc      Using this DC engine.
 * @param[in]  *rect    Where to draw the string.
 * @param[out] None
 * @retval     None 
 *******************************************************************************
 */
void cogui_lcd_putc(uint16_t x, uint16_t y, char c, cogui_font_t *font, cogui_dc_t *dc, cogui_rect_t *rect)
{	
	uint16_t i, j, f;
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

/**
 *******************************************************************************
 * @brief      Get the string width.
 * @param[in]  *str             Which string we are computing.
 * @param[in]  *font            Choosing which font.
 * @param[out] None
 * @retval     text_width       Result of string widget.
 *******************************************************************************
 */
uint32_t cogui_get_text_width(char *str, cogui_font_t *font)
{
    COGUI_ASSERT(font != Co_NULL);

    uint32_t text_width;
    uint64_t str_len = str != Co_NULL ? cogui_strlen(str) : 0;

    /* compute text widget */
    text_width = str_len * font->width;

    return text_width;
}

/**
 *******************************************************************************
 * @brief      Get the string height.
 * @param[in]  *str             Which string we are computing.
 * @param[in]  *font            Choosing which font.
 * @param[in]  *rect            Where are the string.
 * @param[out] None
 * @retval     text_height      Result of string height.
 *******************************************************************************
 */
uint32_t cogui_get_text_height(char *str, cogui_font_t *font, cogui_rect_t *rect)
{
    COGUI_ASSERT(rect != Co_NULL);
    COGUI_ASSERT(font != Co_NULL);

    uint32_t rect_width = COGUI_RECT_WIDTH(rect);
    uint32_t text_width;
    uint32_t text_height;
    uint32_t lines;

    /* how many lines does this text has in this rectangle */
    text_width = cogui_get_text_width(str, font);
    lines = text_width / rect_width + 1;

    /* compute text height */
    text_height = lines * font->height;

    return text_height;
}

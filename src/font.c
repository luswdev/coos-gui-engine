/**
 *******************************************************************************
 * @file       font.c
 * @version    V0.7.3
 * @date       2020.03.25
 * @brief      Font function file.
 *******************************************************************************
 */ 

#include "cogui.h"

font_t *default_font = &tm_font_7x10;

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
void gui_lcd_puts(uint16_t x, uint16_t y, char *str, font_t *font, dc_t *dc, rect_t *rect)
{
    while (*str) {
        if (*str == '\n') {
			y += font->height;
            x = rect->x1;
			
			str++;
			continue;
		}

        gui_lcd_putc(x, y, *str++, font, dc, rect);

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
void gui_lcd_putc(uint16_t x, uint16_t y, char c, font_t *font, dc_t *dc, rect_t *rect)
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
uint32_t gui_get_text_width(char *str, font_t *font)
{
    ASSERT(font != Co_NULL);

    uint32_t text_width;
    uint64_t str_len = str != Co_NULL ? gui_strlen(str) : 0;

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
uint32_t gui_get_text_height(char *str, font_t *font, rect_t *rect)
{
    ASSERT(rect != Co_NULL);
    ASSERT(font != Co_NULL);

    uint32_t rect_width = GUI_RECT_WIDTH(rect);
    uint32_t text_width;
    uint32_t text_height;
    uint32_t lines;

    /* how many lines does this text has in this rectangle */
    text_width = gui_get_text_width(str, font);
    lines = text_width / rect_width + 1;

    /* compute text height */
    text_height = lines * font->height;

    return text_height;
}

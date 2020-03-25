/**
 *******************************************************************************
 * @file       font.h
 * @version    V0.7.3
 * @date       2020.03.25
 * @brief      Font define file.
 *******************************************************************************
 */ 

#ifndef __GUI_FONT_H__
#define __GUI_FONT_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct   cogui_font
 * @brief    font struct
 * @details  This struct is font contains some information.
 */
struct font {
    char *                   family;     /**< Which font family belongs to   */
    uint16_t                 width;      /**< Font width                     */
    uint16_t                 height;     /**< Font height                    */
    const uint16_t *         data;       /**< Real font table pointer        */
};
typedef struct font font_t;

/* extern from tm_stm32f4-fonts.c */
extern font_t tm_font_7x10;
extern font_t tm_font_11x18;
extern font_t tm_font_16x26;

/* extern from symbol.c */
extern font_t tm_symbol_16x16;

/* display text function */
void gui_lcd_puts(uint16_t x, uint16_t y, char *str, font_t *font, dc_t *dc, rect_t *rect);
void gui_lcd_putc(uint16_t x, uint16_t y, char c, font_t *font, dc_t *dc, rect_t *rect);

/* get text attributes */
uint32_t gui_get_text_width(char *str, font_t *font);
uint32_t gui_get_text_height(char *str, font_t *font, rect_t *rect);

#ifdef __cplusplus
}
#endif

#endif /* __GUI_FONT_H__ */

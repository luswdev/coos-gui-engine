/**
 *******************************************************************************
 * @file       font.h
 * @version    V0.7.1
 * @date       2020.02.23
 * @brief      Font define file.
 *******************************************************************************
 */ 

#ifndef __COGUI_FONT_H__
#define __COGUI_FONT_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct   cogui_font
 * @brief    font struct
 * @details  This struct is font contains some information.
 */
struct cogui_font {
    char *                      family;     /**< Which font family belongs to   */
    uint16_t                 width;      /**< Font width                     */
    uint16_t                 height;     /**< Font height                    */
    const uint16_t *         data;       /**< Real font table pointer        */
};
typedef struct cogui_font cogui_font_t;

/* extern from tm_stm32f4-fonts.c */
extern cogui_font_t tm_font_7x10;
extern cogui_font_t tm_font_11x18;
extern cogui_font_t tm_font_16x26;

/* extern from symbol.c */
extern cogui_font_t tm_symbol_16x16;

/* display text function */
void cogui_lcd_puts(uint16_t x, uint16_t y, char *str, cogui_font_t *font, cogui_dc_t *dc, cogui_rect_t *rect);
void cogui_lcd_putc(uint16_t x, uint16_t y, char c, cogui_font_t *font, cogui_dc_t *dc, cogui_rect_t *rect);

/* get text attributes */
uint32_t cogui_get_text_width(char *str, cogui_font_t *font);
uint32_t cogui_get_text_height(char *str, cogui_font_t *font, cogui_rect_t *rect);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_FONT_H__ */

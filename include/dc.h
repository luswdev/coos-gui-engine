/**
 *******************************************************************************
 * @file       dc.h
 * @version    V0.1.0  
 * @date       2019.9.29
 * @brief      Drawable canvas engine header file.	
 *******************************************************************************
 */ 

#ifndef _COGUI_DC_H
#define _COGUI_DC_H

#include "color.h"

#define COGUI_DC(dc)	((cogui_dc_t *)(dc))                /**< Change type to DC pointer      */

#define _int_swap(x, y) {x ^= y; y ^= x; x ^= y;}           /**< Swap two integer               */
#define _int_comp(x, y) { if (x>y) _int_swap(x, y); }       /**< If x larger than y, swap it    */

#define COGUI_DC_FC(dc) (cogui_dc_get_gc(COGUI_DC(dc))->foreground)  /**< Get foreground    */
#define COGUI_DC_BC(dc) (cogui_dc_get_gc(COGUI_DC(dc))->background)  /**< Get background    */

struct cogui_dc;
struct cogui_widget;
struct cogui_graphic_driver;

typedef struct cogui_dc cogui_dc_t;

/**
 * @struct   cogui_gc dc.h	
 * @brief    Graph context struct
 * @details  This struct use to record graph context parameter.
 */
struct cogui_gc
{
    cogui_color_t       foreground;           /**< Foreground and background color */
    cogui_color_t       background;           /**< Boreground and background color */

    //co_uint16_t         textstyle;           /**< Text style  */
    //co_uint16_t         textalign;           /**< Text align */

    //struct cogui_font   *font;               /**< Font */
};

/* dc type define */
#define COGUI_DC_INIT           0x00          /**< DC initial type      */
#define COGUI_DC_HW             0x01          /**< DC hardware type     */
#define COGUI_DC_BUFFER         0x02          /**< DC buffer type       */

/**
 * @struct   cogui_dc_engine dc.h	
 * @brief    DC engine struct
 * @details  This struct is a field to put dc engine interface.
 */
struct cogui_dc_engine
{
    /* interface */
    void (*draw_point)(cogui_dc_t *dc, co_int32_t x, co_int32_t y);
    void (*draw_color_point)(cogui_dc_t *dc, co_int32_t x, co_int32_t y, cogui_color_t color);
    void (*draw_vline)(cogui_dc_t *dc, co_int32_t x, co_int32_t y1, co_int32_t y2);
    void (*draw_hline)(cogui_dc_t *dc, co_int32_t x1, co_int32_t x2, co_int32_t y);
    void (*fill_rect)(cogui_dc_t *dc, cogui_rect_t *rect);

    StatusType (*fini)(cogui_dc_t * dc);
};

/**
 * @struct   cogui_dc dc.h	
 * @brief    DC information struct
 * @details  This struct record DC information.
 */
struct cogui_dc
{
    cogui_uint8_t           type;           /**< type of device context */

    struct cogui_dc_engine  *engine;        /**< DC engine */
};

/**
 * @struct   cogui_dc_hw dc.h	
 * @brief    Hardware DC information struct
 * @details  This struct record hardware DC information.
 */
struct cogui_dc_hw
{
    cogui_dc_t                  parent;         /**< parent DC pointer  */

    struct cogui_widget         *owner;         /**< DC owner widget    */
    struct cogui_graphic_driver *hw_driver;     /**< hardware driver    */
};

/**
 * @struct   cogui_dc_buffer dc.h	
 * @brief    Buffer DC information struct
 * @details  This struct record buffer DC information.
 */
struct cogui_dc_buffer
{
    cogui_dc_t parent;                          /**< parent DC pointer  */

    /*
    struct cogui_gc gc;

    co_uint8_t pixel_format;
    co_uint8_t blend_mode;		

    co_uint16_t width, height;
    co_uint16_t pitch;

    co_uint8_t pixel_alpha;
    co_uint8_t *pixel;*/
};


/* create a hardware DC */
cogui_dc_t *cogui_dc_hw_create(struct cogui_widget *owner);

void cogui_dc_draw_line(cogui_dc_t *dc, co_int32_t x1, co_int32_t y1, co_int32_t x2, co_int32_t y2);
void cogui_dc_draw_rect(cogui_dc_t *dc, cogui_rect_t *rect);
void cogui_dc_draw_shaded_rect(cogui_dc_t *dc, cogui_rect_t *rect, cogui_color_t c1, cogui_color_t c2);
void cogui_dc_fill_rect_forecolor(cogui_dc_t *dc, cogui_rect_t *rect);
//void cogui_dc_draw_round_rect(cogui_dc_t *dc, cogui_rect_t *rect, co_int32_t r);
//void cogui_dc_fill_round_rect(cogui_dc_t *dc, cogui_rect_t *rect, co_int32_t r);

void cogui_dc_draw_horizontal_line(cogui_dc_t *dc, co_int32_t x1, co_int32_t x2, co_int32_t y);
void rtgui_dc_draw_vertical_line(cogui_dc_t *dc, co_int32_t x, co_int32_t y1, co_int32_t y2);

void cogui_dc_draw_border(cogui_dc_t *dc, cogui_rect_t *rect, int flag);

/* get current graph context */
struct cogui_gc *cogui_dc_get_gc(cogui_dc_t *dc);

/* DC usage function */
cogui_dc_t *cogui_dc_begin_drawing(struct cogui_widget *owner);
void cogui_dc_end_drawing(cogui_dc_t *dc);

#endif /* _COGUI_DC_H */

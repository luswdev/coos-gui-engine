/**
 *******************************************************************************
 * @file       dc.h
 * @version    V0.1.1
 * @date       2020.01.04
 * @brief      Drawable canvas engine header file.	
 *******************************************************************************
 */ 

#ifndef _COGUI_DC_H
#define _COGUI_DC_H

#define COGUI_DC(dc)	((cogui_dc_t *)(dc))                /**< Change type to DC pointer      */

#define _int_swap(x, y) {x ^= y; y ^= x; x ^= y;}           /**< Swap two integer               */
#define _int_comp(x, y) { if (x>y) _int_swap(x, y); }       /**< If x larger than y, swap it    */

#define COGUI_DC_FC(dc)         (cogui_dc_get_gc(COGUI_DC(dc))->foreground)  /**< get foreground    */
#define COGUI_DC_BC(dc)         (cogui_dc_get_gc(COGUI_DC(dc))->background)  /**< get background    */
#define COGUI_DC_TA(dc)         (cogui_dc_get_gc(COGUI_DC(dc))->text_align)  /**< get text_align    */
#define COGUI_DC_FONT(dc)       (cogui_dc_get_gc(COGUI_DC(dc))->font)        /**< get font pointer   */
#define COGUI_DC_PADDING(dc)    (cogui_dc_get_gc(COGUI_DC(dc))->padding)        /**< get font pointer   */

/* Border style */
#define COGUI_BORDER_NONE       0x00                        /**< Border style none      */
#define COGUI_BORDER_SIMPLE     0x01                        /**< Border style simple    */

#define COGUI_BORDER_DEFAULT_WIDTH  2                       /**< Default border width   */

extern const cogui_color_t default_foreground;

struct cogui_dc;
struct cogui_widget;
struct cogui_graphic_driver;

typedef struct cogui_dc cogui_dc_t;

#define COGUI_TEXT_ALIGN_NONE           0x00
#define COGUI_TEXT_ALIGN_LEFT           0x01
#define COGUI_TEXT_ALIGN_RIGHT          0x02
#define COGUI_TEXT_ALIGN_CENTER         0x04
#define COGUI_TEXT_ALIGN_TOP            0x08
#define COGUI_TEXT_ALIGN_MIDDLE         0x10
#define COGUI_TEXT_ALIGN_BOTTOM         0x20

/**
 * @struct   cogui_gc dc.h	
 * @brief    Graph context struct
 * @details  This struct use to record graph context parameter.
 */
struct cogui_gc
{
    cogui_color_t       foreground;             /**< foreground and background color */
    cogui_color_t       background;             /**< background and background color */

    struct cogui_font * font;                   /**< font structure pointer         */

    co_uint16_t         text_align;             /**< text alignment                 */
    co_uint64_t         padding;                /**< rectangle padding (for text)   */
};

#define COGUI_PADDING(top, bottom, left, right) ((co_uint64_t)(((top)<<24)|((bottom)<<16)|((left)<<8)|(right)))

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
    co_uint8_t               type;          /**< type of device context */
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

void cogui_dc_draw_line(cogui_dc_t *dc, co_int32_t x1, co_int32_t x2, co_int32_t y1, co_int32_t y2);
void cogui_dc_draw_rect(cogui_dc_t *dc, cogui_rect_t *rect);
void cogui_dc_draw_shaded_rect(cogui_dc_t *dc, cogui_rect_t *rect, cogui_color_t c1, cogui_color_t c2);
void cogui_dc_fill_rect_forecolor(cogui_dc_t *dc, cogui_rect_t *rect);
//void cogui_dc_draw_round_rect(cogui_dc_t *dc, cogui_rect_t *rect, co_int32_t r);
//void cogui_dc_fill_round_rect(cogui_dc_t *dc, cogui_rect_t *rect, co_int32_t r);

void cogui_dc_draw_horizontal_line(cogui_dc_t *dc, co_int32_t x1, co_int32_t x2, co_int32_t y);
void rtgui_dc_draw_vertical_line(cogui_dc_t *dc, co_int32_t x, co_int32_t y1, co_int32_t y2);

void cogui_dc_draw_border(cogui_dc_t *dc, cogui_rect_t *rect);

void cogui_dc_draw_text(cogui_dc_t *dc, cogui_rect_t *rect, char *str);

void cogui_dc_draw_button(cogui_dc_t *dc, co_int16_t flag);
void cogui_dc_draw_title(cogui_dc_t *dc);

/* get current graph context */
struct cogui_gc *cogui_dc_get_gc(cogui_dc_t *dc);

struct cogui_widget *cogui_dc_get_owner(cogui_dc_t *dc);

/* DC usage function */
cogui_dc_t *cogui_dc_begin_drawing(struct cogui_widget *owner);
void cogui_dc_end_drawing(cogui_dc_t *dc);

#endif /* _COGUI_DC_H */

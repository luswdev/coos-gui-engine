/**
 *******************************************************************************
 * @file       dc.h
 * @version    V0.7.3
 * @date       2020.03.25
 * @brief      Drawable canvas engine header file.	
 *******************************************************************************
 */ 

#ifndef __GUI_DC_H__
#define __GUI_DC_H__

#ifdef __cplusplus
extern "C" {
#endif

#define GUI_DC(dc)	((dc_t *)(dc))                /**< change type to DC pointer      */

#define _int_swap(x, y) {x ^= y; y ^= x; x ^= y;}           /**< swap two integer               */
#define _int_comp(x, y) { if (x>y) _int_swap(x, y); }       /**< if x larger than y, swap it    */

#define GUI_DC_FC(dc)         (gui_dc_get_gc(GUI_DC(dc))->foreground)         /**< get foreground     */
#define GUI_DC_BC(dc)         (gui_dc_get_gc(GUI_DC(dc))->background)         /**< get background     */
#define GUI_DC_TA(dc)         (gui_dc_get_gc(GUI_DC(dc))->text_align)         /**< get text_align     */
#define GUI_DC_FONT(dc)       (gui_dc_get_gc(GUI_DC(dc))->font)               /**< get font pointer   */
#define GUI_DC_PADDING(dc)    (gui_dc_get_gc(GUI_DC(dc))->padding)            /**< get font pointer   */

/* border style */
#define GUI_BORDER_NONE       0x00         /**< border style none      */
#define GUI_BORDER_SIMPLE     0x01         /**< border style simple    */

#define GUI_BORDER_DEFAULT_WIDTH  2        /**< default border width   */

extern const color_t default_foreground;

struct dc;
struct widget;
struct graphic_driver;

typedef struct dc dc_t;

/* text align style */
#define GUI_TEXT_ALIGN_NONE           0x00        /**< no aligning                    */
#define GUI_TEXT_ALIGN_LEFT           0x01        /**< horizontal align to left       */
#define GUI_TEXT_ALIGN_CENTER         0x04        /**< horizontal align to center     */
#define GUI_TEXT_ALIGN_RIGHT          0x02        /**< horizontal align to right      */
#define GUI_TEXT_ALIGN_TOP            0x08        /**< vertical align to top          */
#define GUI_TEXT_ALIGN_MIDDLE         0x10        /**< vertical align to middle       */
#define GUI_TEXT_ALIGN_BOTTOM         0x20        /**< vertical align to bottom       */

/**
 * @struct   cogui_gc dc.h	
 * @brief    Graph context struct
 * @details  This struct use to record graph context parameter.
 */
struct gc
{
    color_t       foreground;             /**< foreground and background color */
    color_t       background;             /**< background and background color */

    struct font * font;                   /**< font structure pointer         */

    uint16_t         text_align;             /**< text alignment                 */
    uint64_t         padding;                /**< rectangle padding (for text)   */
};

#define GUI_PADDING(top, bottom, left, right) ((uint64_t)(((top)<<24)|((bottom)<<16)|((left)<<8)|(right)))
#define GUI_PADDING_SIMPLE(pa)                ((uint64_t)(((pa)<<24)|((pa)<<16)|((pa)<<8)|(pa)))

/* dc type define */
#define GUI_DC_INIT           0x00          /**< DC initial type      */
#define GUI_DC_HW             0x01          /**< DC hardware type     */
#define GUI_DC_BUFFER         0x02          /**< DC buffer type       */

/**
 * @struct   cogui_dc_engine dc.h	
 * @brief    DC engine struct
 * @details  This struct is a field to put dc engine interface.
 */
struct dc_engine
{
    /* interface */
    void (*draw_point)(dc_t *dc, int32_t x, int32_t y);
    void (*draw_color_point)(dc_t *dc, int32_t x, int32_t y, color_t color);
    void (*draw_vline)(dc_t *dc, int32_t x, int32_t y1, int32_t y2);
    void (*draw_hline)(dc_t *dc, int32_t x1, int32_t x2, int32_t y);
    void (*fill_rect)(dc_t *dc, rect_t *rect);

    StatusType (*fini)(dc_t * dc);
};

/**
 * @struct   dc dc.h	
 * @brief    DC information struct
 * @details  This struct record DC information.
 */
struct dc
{
    uint8_t               type;          /**< type of device context */
    struct dc_engine  *engine;        /**< DC engine */
};

/**
 * @struct   dc_hw_t dc.h	
 * @brief    Hardware DC information struct
 * @details  This struct record hardware DC information.
 */
struct dc_hw_t
{
    dc_t                  parent;         /**< parent DC pointer  */

    struct widget         *owner;         /**< DC owner widget    */
    struct graphic_driver *hw_driver;     /**< hardware driver    */
};

/**
 * @struct   dc_buffer_t dc.h	
 * @brief    Buffer DC information struct
 * @details  This struct record buffer DC information.
 */
struct dc_buffer_t
{
    dc_t parent;                          /**< parent DC pointer  */

    /*
    struct cogui_gc gc;

    uint8_t pixel_format;
    uint8_t blend_mode;		

    uint16_t width, height;
    uint16_t pitch;

    uint8_t pixel_alpha;
    uint8_t *pixel;*/
};

/* create a hardware DC */
dc_t *dc_hw_create(struct widget *owner);

void gui_dc_draw_line(dc_t *dc, int32_t x1, int32_t x2, int32_t y1, int32_t y2);
void gui_dc_draw_rect(dc_t *dc, rect_t *rect);
void gui_dc_draw_shaded_rect(dc_t *dc, rect_t *rect, color_t c1, color_t c2);
void gui_dc_fill_rect_forecolor(dc_t *dc, rect_t *rect);

void gui_dc_draw_horizontal_line(dc_t *dc, int32_t x1, int32_t x2, int32_t y);
void gui_dc_draw_vertical_line(dc_t *dc, int32_t x, int32_t y1, int32_t y2);

void gui_dc_draw_border(dc_t *dc, rect_t *rect);

void gui_dc_draw_text(dc_t *dc, rect_t *rect, char *str);

/* get current graph context */
struct gc *gui_dc_get_gc(dc_t *dc);

struct widget *gui_dc_get_owner(dc_t *dc);

/* DC usage function */
dc_t *gui_dc_begin_drawing(struct widget *owner);
void gui_dc_end_drawing(dc_t *dc);

#define gui_dc_draw_point(dc, x, y, c)                      \
{                                                           \
    (dc)->engine->draw_color_point((dc), (x), (y), (c));    \
}                                                           \


#ifdef __cplusplus
}
#endif

#endif /* __GUI_DC_H__ */

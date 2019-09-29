/**
 *******************************************************************************
 * @file       dc.h
 * @version    V0.1.0  
 * @date       2019.9.29
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#ifndef _COGUI_DC_H
#define _COGUI_DC_H

#include "color.h"

#define COGUI_DC(dc)	((cogui_dc_t *)(dc))

#define _int_swap(x, y) {x ^= y; y ^= x; x ^= y;}
#define _int_comp(x, y) { if (x>y) _int_swap(x, y); }

#define COGUI_DC_FC(dc) (cogui_dc_get_gc(COGUI_DC(dc))->foreground)
#define COGUI_DC_BC(dc) (cogui_dc_get_gc(COGUI_DC(dc))->background)

struct cogui_dc;
struct cogui_widget;
struct cogui_graphic_driver;

struct cogui_gc
{
    /* foreground and background color */
    cogui_color_t foreground, background;

    /* text style */
    U16 textstyle;
    /* text align */
    U16 textalign;

    /* font 
    struct cogui_font *font; */
};

enum cogui_dc_type
{
    COGUI_DC_HW,
    COGUI_DC_CLIENT,
    COGUI_DC_BUFFER,
};

struct cogui_dc_engine
{
    /* interface */
    void (*draw_point)(struct cogui_dc *dc, S32 x, S32 y);
    void (*draw_color_point)(struct cogui_dc *dc, S32 x, S32 y, cogui_color_t color);
    void (*draw_vline)(struct cogui_dc *dc, S32 x, S32 y1, S32 y2);
    void (*draw_hline)(struct cogui_dc *dc, S32 x1, S32 x2, S32 y);
    void (*fill_rect)(struct cogui_dc *dc, cogui_rect_t *rect);

    StatusType (*fini)(struct cogui_dc * dc);
};

struct cogui_dc
{
    /* type of device context */
    enum cogui_dc_type type;

    /* dc engine */
    struct cogui_dc_engine *engine;
};
typedef struct cogui_dc cogui_dc_t;

struct cogui_dc_hw
{
    cogui_dc_t parent;
    struct cogui_widget *owner;
    struct cogui_graphic_driver *hw_driver;
};

struct cogui_dc_buffer
{
    cogui_dc_t parent;

    /* graphic context */
    struct cogui_gc gc;

    /* pixel format */
    U8 pixel_format;
    U8 blend_mode;		

    /* width and height */
    U16 width, height;
    /* pitch */
    U16 pitch;

	/* pixel alpha */
    U8 pixel_alpha;
    /* pixel data */
    U8 *pixel;
};


/* create a hardware dc */
cogui_dc_t *cogui_dc_hw_create(struct cogui_widget * owner);

void cogui_dc_draw_line(cogui_dc_t *dc, S32 x1, S32 y1, S32 x2, S32 y2);
void cogui_dc_draw_rect(cogui_dc_t *dc, cogui_rect_t *rect);
void cogui_dc_draw_shaded_rect(cogui_dc_t *dc, cogui_rect_t *rect, cogui_color_t c1, cogui_color_t c2);
void cogui_dc_fill_rect_forecolor(cogui_dc_t *dc, cogui_rect_t *rect);
//void cogui_dc_draw_round_rect(cogui_dc_t *dc, cogui_rect_t *rect, S32 r);
//void cogui_dc_fill_round_rect(cogui_dc_t *dc, cogui_rect_t *rect, S32 r);

void cogui_dc_draw_horizontal_line(cogui_dc_t *dc, S32 x1, S32 x2, S32 y);
void rtgui_dc_draw_vertical_line(cogui_dc_t *dc, S32 x, S32 y1, S32 y2);

void cogui_dc_draw_border(cogui_dc_t *dc, cogui_rect_t *rect, int flag);

struct cogui_gc *cogui_dc_get_gc(cogui_dc_t *dc);

cogui_dc_t *cogui_dc_begin_drawing(struct cogui_widget *owner);
void cogui_dc_end_drawing(cogui_dc_t *dc);

#endif /* _COGUI_DC_H */

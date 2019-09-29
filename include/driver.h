/**
 *******************************************************************************
 * @file       driver.h
 * @version    V0.0.3
 * @date       2019.9.29
 * @brief      Some system function for GUI engine's driver.
 *******************************************************************************
 */ 

#ifndef _COGUI_DRIVER_H
#define _COGUI_DRIVER_H

#include "color.h"

enum
{
    GRAPHIC_PIXEL_FORMAT_MONO = 0,
    GRAPHIC_PIXEL_FORMAT_GRAY4,
    GRAPHIC_PIXEL_FORMAT_GRAY16,
    GRAPHIC_PIXEL_FORMAT_RGB332,
    GRAPHIC_PIXEL_FORMAT_RGB444,
    GRAPHIC_PIXEL_FORMAT_RGB565,
    GRAPHIC_PIXEL_FORMAT_RGB565P,
    GRAPHIC_PIXEL_FORMAT_BGR565 = GRAPHIC_PIXEL_FORMAT_RGB565P,
    GRAPHIC_PIXEL_FORMAT_RGB666,
    GRAPHIC_PIXEL_FORMAT_RGB888,
    GRAPHIC_PIXEL_FORMAT_ARGB888,
    GRAPHIC_PIXEL_FORMAT_ABGR888,
    GRAPHIC_PIXEL_FORMAT_ARGB565,
    GRAPHIC_PIXEL_FORMAT_ALPHA,
};

/* graphic driver operations */
struct graphic_driver_ops
{
    /* set and get pixel in (x, y) */
    void (*set_pixel)(cogui_color_t *c, S32 x, S32 y);
    void (*get_pixel)(cogui_color_t *c, S32 x, S32 y);

    void (*draw_hline)(cogui_color_t *c, S32 x1, S32 x2, S32 y);
    void (*draw_vline)(cogui_color_t *c, S32 x , S32 y1, S32 y2);

    /* draw raw hline */
    void (*draw_raw_hline)(U8 *pixels, S32 x1, S32 x2, S32 y);
};

/* graphic extension operations */
struct graphic_ext_ops
{
    /* some 2D operations */
    void (*draw_line)(cogui_color_t *c, S32 x1, S32 y1, S32 x2, S32 y2);

    void (*draw_rect)(cogui_color_t *c, S32 x1, S32 y1, S32 x2, S32 y2);
    void (*fill_rect)(cogui_color_t *c, S32 x1, S32 y1, S32 x2, S32 y2);

    void (*draw_circle)(cogui_color_t *c, S32 x, S32 y, S32 r);
    void (*fill_circle)(cogui_color_t *c, S32 x, S32 y, S32 r);

    void (*draw_ellipse)(cogui_color_t *c, S32 x, S32 y, S32 rx, S32 ry);
    void (*fill_ellipse)(cogui_color_t *c, S32 x, S32 y, S32 rx, S32 ry);
};

struct cogui_graphic_driver
{
    /* pixel format and byte per pixel */
    U8 pixel_format;
    U8 bits_per_pixel;
    U16 pitch;

    /* screen width and height */
    U16 width;
    U16 height;

    /* framebuffer address and ops */
    U8 *framebuffer;

    struct graphic_driver_ops *ops;
    struct graphic_ext_ops *ext_ops;
};
typedef struct cogui_graphic_driver cogui_graphic_driver_t;

cogui_graphic_driver_t *cogui_graphic_driver_get_default(void);
void cogui_set_graphic_driver(cogui_graphic_driver_t *driver);

#endif /* _COGUI_DRIVER_H */


/**
 *******************************************************************************
 * @file       driver.h
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      Some system function for GUI engine's driver.
 *******************************************************************************
 */ 

#ifndef __COGUI_DRIVER_H__
#define __COGUI_DRIVER_H__

#ifdef __cplusplus
extern "C" {
#endif

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
    void (*set_pixel)(cogui_color_t *c, int32_t x, int32_t y);
    void (*get_pixel)(cogui_color_t *c, int32_t x, int32_t y);

    void (*draw_hline)(cogui_color_t *c, int32_t x1, int32_t x2, int32_t y);
    void (*draw_vline)(cogui_color_t *c, int32_t x , int32_t y1, int32_t y2);
};

/* graphic extension operations */
struct graphic_ext_ops
{
    /* some 2D operations */
    void (*draw_line)(cogui_color_t *c, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

    void (*draw_rect)(cogui_color_t *c, int32_t x1, int32_t y1, int32_t x2, int32_t y2);
    void (*fill_rect)(cogui_color_t *c, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

    void (*draw_circle)(cogui_color_t *c, int32_t x, int32_t y, int32_t r);
    void (*fill_circle)(cogui_color_t *c, int32_t x, int32_t y, int32_t r);

    void (*draw_ellipse)(cogui_color_t *c, int32_t x, int32_t y, int32_t rx, int32_t ry);
    void (*fill_ellipse)(cogui_color_t *c, int32_t x, int32_t y, int32_t rx, int32_t ry);
};

struct cogui_graphic_driver
{
    /* pixel format and byte per pixel */
    U8 pixel_format;

    /* screen width and height */
    U16 width;
    U16 height;

    /* framebuffer address and ops */
    uint32_t frame_buffer;

    const struct graphic_driver_ops *ops;
    const struct graphic_ext_ops *ext_ops;
};
typedef struct cogui_graphic_driver cogui_graphic_driver_t;

cogui_graphic_driver_t *cogui_graphic_driver_get_default(void);
void cogui_set_graphic_driver(cogui_graphic_driver_t *driver);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_DRIVER_H__ */

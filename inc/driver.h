/**
 *******************************************************************************
 * @file       driver.h
 * @version    V0.7.4
 * @date       2020.04.18
 * @brief      Some system function for GUI engine's driver.
 *******************************************************************************
 */ 

#ifndef __GUI_DRIVER_H__
#define __GUI_DRIVER_H__

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
    void (*set_pixel)(color_t *c, int32_t x, int32_t y);
    void (*get_pixel)(color_t *c, int32_t x, int32_t y);

    void (*draw_hline)(color_t *c, int32_t x1, int32_t x2, int32_t y);
    void (*draw_vline)(color_t *c, int32_t x , int32_t y1, int32_t y2);
};

/* graphic extension operations */
struct graphic_ext_ops
{
    /* some 2D operations */
    void (*draw_line)(color_t *c, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

    void (*draw_rect)(color_t *c, int32_t x1, int32_t y1, int32_t x2, int32_t y2);
    void (*fill_rect)(color_t *c, int32_t x1, int32_t y1, int32_t x2, int32_t y2);

    void (*draw_circle)(color_t *c, int32_t x, int32_t y, int32_t r);
    void (*fill_circle)(color_t *c, int32_t x, int32_t y, int32_t r);

    void (*draw_ellipse)(color_t *c, int32_t x, int32_t y, int32_t rx, int32_t ry);
    void (*fill_ellipse)(color_t *c, int32_t x, int32_t y, int32_t rx, int32_t ry);
};

struct graphic_driver
{
    /* pixel format and byte per pixel */
    uint8_t pixel_format;

    /* screen width and height */
    uint16_t width;
    uint16_t height;

    /* framebuffer address and ops */
    uint32_t frame_buffer;

    const struct graphic_driver_ops *ops;
    const struct graphic_ext_ops *ext_ops;
};
typedef struct graphic_driver graphic_driver_t;

graphic_driver_t *gui_graphic_driver_get_default(void);
void gui_set_graphic_driver(graphic_driver_t *driver);

#ifdef __cplusplus
}
#endif

#endif /* __GUI_DRIVER_H__ */

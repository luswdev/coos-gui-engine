/**
 *******************************************************************************
 * @file       GuiDriver.h
 * @version    V0.0.1   
 * @date       2019.5.19
 * @brief      Some system function for GUI engine's driver.
 *******************************************************************************
 */ 

#ifndef _GUI_DRIVER_H
#define _GUI_DRIVER_H

/*---------------------------- structure -------------------------------------*/

/* graphic driver operations */
struct graphicDriverOops
{
    /* set and get pixel in (x, y) */
    void (*setPixel)(GUI_COLOR *c, S32 x, S32 y);
    void (*getPixel)(GUI_COLOR *c, S32 x, S32 y);

    void (*drawHline)(GUI_COLOR *c, S32 x1, S32 x2, S32 y);
    void (*drawVline)(GUI_COLOR *c, S32 x , S32 y1, S32 y2);

    /* draw raw hline */
    void (*drawRawHline)(U8 *pixels, S32 x1, S32 x2, S32 y);
};

/* graphic extension operations */
struct graphicExtOps
{
    /* some 2D operations */
    void (*drawLine)(GUI_COLOR *c, S32 x1, S32 y1, S32 x2, S32 y2);

    void (*drawRect)(GUI_COLOR *c, S32 x1, S32 y1, S32 x2, S32 y2);
    void (*fillRect)(GUI_COLOR *c, S32 x1, S32 y1, S32 x2, S32 y2);

    void (*drawCircle)(GUI_COLOR *c, S32 x, S32 y, S32 r);
    void (*fillCircle)(GUI_COLOR *c, S32 x, S32 y, S32 r);

    void (*drawEllipse)(GUI_COLOR *c, S32 x, S32 y, S32 rx, S32 ry);
    void (*fillEllipse)(GUI_COLOR *c, S32 x, S32 y, S32 rx, S32 ry);
};

struct graphicDriver
{
    /* pixel format and byte per pixel */
    U8 pixelFormat;
    U8 bitsPerPixel;
    U16 pitch;

    /* screen width and height */
    U16 width;
    U16 height;

    /* framebuffer address and ops */
    U8 *framebuffer;

    const struct graphicDriverOops *ops;
    const struct graphicExtOps *extOps;
}GuiGD,*P_GuiGD;

#endif /* _GUI_DRIVER_H */
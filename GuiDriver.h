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

cogui_graphic_driver_t *cogui_graphic_driver_get_default(void);
void cogui_set_graphic_driver(cogui_graphic_driver_t *driver);

#endif /* _GUI_DRIVER_H */


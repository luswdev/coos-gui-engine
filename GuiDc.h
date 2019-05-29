/**
 *******************************************************************************
 * @file       GuiDc.h
 * @version    V0.0.1   
 * @date       2019.5.29
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#ifndef _GUI_DC_H
#define _GUI_DC_H

#define _intSwap(x, y) {x ^= y; y ^= x; x ^= y;}

enum guiDcType
{
    GUI_DC_HW,
    GUI_DC_CLIENT,
    GUI_DC_BUFFER,
};

/*---------------------------- structure -------------------------------------*/
struct dcEngine
{
    /* interface */
    void (*drawPoint)(P_GuiDc dc, S32 x, S32 y);
    void (*drawColorPoint)(P_GuiDc dc, S32 x, S32 y, GUI_COLOR color);
    void (*drawVline)(P_GuiDc dc, S32 x, S32 y1, S32 y2);
    void (*drawHline)(P_GuiDc dc, S32 x1, S32 x2, S32 y);
    void (*fillRect)(P_GuiDc dc, rtgui_rect_t *rect);
    void (*blitLine)(P_GuiDc dc, S32 x1, S32 x2, S32 y, U8 lineData);
    void (*blit)(P_GuiDc dc, P_GuiPoint dcPoint, P_GuiDc dest, P_GuiRect rect);

    rt_bool_t (*fini)( dc);
}GuiDcEng,*P_GuiDcEng;

struct dc
{
    /* type of device context */
    enum guiDcType type;

    /* dc engine */
    const P_GuiDcEng engine;
}GuiDc,*P_GuiDc;

struct dcHw
{
    GuiDc parent;
    P_GuiWidget owner;
    const P_GuiGD hwDriver;
};

struct dcBuffer
{
    GuiDc parent;

    /* graphic context */
    struct gc gc;

    /* pixel format */
    U8 pixelFormat;
    U8 blendMode;		/* RTGUI_BLENDMODE: None/Blend/Add/Mod */

    /* width and height */
    U16 width, height;
    /* pitch */
    U16 pitch;

	/* pixel alpha */
    U8 pixelAlpha;
    /* pixel data */
    U8 *pixel;
}


#endif /* _GUI_DC_H */
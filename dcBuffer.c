/**
 *******************************************************************************
 * @file       dcBuffer.c
 * @version    V0.0.1   
 * @date       2019.5.29
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#include "cogui.h"

/*---------------------------- Function declare ------------------------------*/
static void DcBufferDrawPoint(P_GuiDc dc, S32 x, S32 y);
static void DcBufferDrawColorPoint(P_GuiDc dc, S32 x, S32 y, rtgui_color_t color);
static void DcBufferDrawVline(P_GuiDc dc, S32 x, S32 y1, S32 y2);
static void DcBufferDrawHline(P_GuiDc dc, S32 x1, S32 x2, S32 y);
static void DcBufferFillRect(P_GuiDc dc, P_GuiRect rect);

static StatusType DcBufferFini(P_GuiDc dc);

const GuiDcEng dcBufferEngine =
{
    DcBufferDrawPoint,
    DcBufferDrawColorPoint,
    DcBufferDrawVline,
    DcBufferDrawHline,
    DcBufferFillRect,

    DcBufferFini,
};


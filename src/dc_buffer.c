/**
 *******************************************************************************
 * @file       dc_buffer.c
 * @version    V0.0.1   
 * @date       2019.5.29
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"

static void DcBufferDrawPoint(cogui_dc_t *dc, S32 x, S32 y);
static void DcBufferDrawColorPoint(cogui_dc_t *dc, S32 x, S32 y, cogui_color_t color);
static void DcBufferDrawVline(cogui_dc_t *dc, S32 x, S32 y1, S32 y2);
static void DcBufferDrawHline(cogui_dc_t *dc, S32 x1, S32 x2, S32 y);
static void DcBufferFillRect(cogui_dc_t *dc, P_GuiRect rect);

static StatusType DcBufferFini(cogui_dc_t *dc);

const GuiDcEng dcBufferEngine =
{
    DcBufferDrawPoint,
    DcBufferDrawColorPoint,
    DcBufferDrawVline,
    DcBufferDrawHline,
    DcBufferFillRect,

    DcBufferFini,
};


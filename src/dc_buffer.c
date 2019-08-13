/**
 *******************************************************************************
 * @file       dc_buffer.c
 * @version    V0.0.1   
 * @date       2019.5.29
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"

static void cogui_dc_buffer_draw_point(cogui_dc_t *dc, S32 x, S32 y);
static void coggui_dc_buffer_draw_color_point(cogui_dc_t *dc, S32 x, S32 y, cogui_color_t color);
static void cogui_dc_buffer_draw_vline(cogui_dc_t *dc, S32 x, S32 y1, S32 y2);
static void cogui_dc_buffer_draw_hline(cogui_dc_t *dc, S32 x1, S32 x2, S32 y);
static void cogui_dc_buffer_fill_rect(cogui_dc_t *dc, P_GuiRect rect);

static StatusType cogui_dc_buffer_fini(cogui_dc_t *dc);

const cogui_dc_engine cogui_dc_buffer_engine =
{
    cogui_dc_buffer_draw_point,
    coggui_dc_buffer_draw_color_point,
    cogui_dc_buffer_draw_vline,
    cogui_dc_buffer_draw_hline,
    cogui_dc_buffer_fill_rect,

    cogui_dc_buffer_fini,
};


/**
 *******************************************************************************
 * @file       dc_buffer.c
 * @version    V0.7.4
 * @date       2020.04.18
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#include <cogui.h>

static void dc_buffer_draw_point(dc_t *dc, S32 x, S32 y);
static void dc_buffer_draw_color_point(dc_t *dc, S32 x, S32 y, color_t color);
static void dc_buffer_draw_vline(dc_t *dc, S32 x, S32 y1, S32 y2);
static void dc_buffer_draw_hline(dc_t *dc, S32 x1, S32 x2, S32 y);
static void dc_buffer_fill_rect(dc_t *dc, rect_t rect);
static StatusType dc_buffer_fini(dc_t *dc);

const struct dc_engine dc_buffer_engine =
{
    dc_buffer_draw_point,
    dc_buffer_draw_color_point,
    dc_buffer_draw_vline,
    dc_buffer_draw_hline,
    dc_buffer_fill_rect,

    dc_buffer_fini,
};

static void dc_buffer_draw_point(dc_t *dc, S32 x, S32 y)
{
    /* TODO: need implement
     *  empty
     */
}

static void dc_buffer_draw_color_point(dc_t *dc, S32 x, S32 y, color_t color)
{
    /* TODO: need implement
     *  empty
     */
}

static void dc_buffer_draw_vline(dc_t *dc, S32 x, S32 y1, S32 y2)
{
    /* TODO: need implement
     *  empty
     */
}

static void dc_buffer_draw_hline(dc_t *dc, S32 x1, S32 x2, S32 y)
{
    /* TODO: need implement
     *  empty
     */
}

static void dc_buffer_fill_rect(dc_t *dc, rect_t rect)
{
    /* TODO: need implement
     *  empty
     */
}

static StatusType dc_buffer_fini(dc_t *dc)
{
    /* TODO: need implement
     *  empty
     */
    return E_OK;
}

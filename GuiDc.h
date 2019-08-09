/**
 *******************************************************************************
 * @file       GuiDc.h
 * @version    V0.0.1   
 * @date       2019.5.29
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#ifndef _COGUI_DC_H
#define _COGUI_DC_H

#define COGUI_DC(dc)	((cogui_dc_t *)(dc))

#define _int_swap(x, y) {x ^= y; y ^= x; x ^= y;}
#define _int_comp(x, y) { if (x>y) _intSwap(x, y); }

#define COGUI_DC_FC(dc) (cogui_dc_get_gc(COGUI_DC(dc))->foreground)
#define COGUI_DC_BC(dc) (cogui_dc_get_gc(COGUI_DC(dc))->background)

/*---------------------------- Function declare ------------------------------*/

/* create a hardware dc */
cogui_dc_t *cogui_dc_hw_create(cogui_widget_t * owner);

void cogui_dc_draw_line(cogui_dc_t *dc, S32 x1, S32 y1, S32 x2, S32 y2);
void cogui_dc_draw_rect(cogui_dc_t *dc, P_GuiRect rect);
void cogui_dc_draw_shaded_rect(cogui_dc_t *dc, P_GuiRect rect, cogui_color_t c1, cogui_color_t c2);
void cogui_dc_fill_rect_forecolor(cogui_dc_t *dc, P_GuiRect rect);
//void cogui_dc_draw_round_rect(cogui_dc_t *dc, P_GuiRect rect, S32 r);
//void cogui_dc_fill_round_rect(cogui_dc_t *dc, P_GuiRect rect, S32 r);

void cogui_dc_draw_horizontal_line(cogui_dc_t *dc, S32 x1, S32 x2, S32 y);
void rtgui_dc_draw_vertical_line(cogui_dc_t *dc, S32 x, S32 y1, S32 y2);

void cogui_dc_draw_border(cogui_dc_t *dc, P_GuiRect rect, int flag);

struct cogui_gc *cogui_dc_get_gc(cogui_dc_t *dc);


#endif /* _COGUI_DC_H */

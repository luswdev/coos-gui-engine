/**
 *******************************************************************************
 * @file       dc.c
 * @version    V0.1.0 
 * @date       2019.8.9
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"

void cogui_dc_draw_line(cogui_dc_t *dc, S32 x1, S32 x2, S32 y1, S32 y2)
{
	COGUI_ASSERT(dc != Co_NULL);
	
	if(x1==x2)
		dc->engine->draw_vline(dc,x1,y1,y2);
	else if(y1==y2)
		dc->engine->draw_hline(dc,x1,x2,y1);
	else{
		_int_comp(x1, x2);
		_int_comp(y1, y2);
		
		for( ;y1<y2; y1++)
			dc->engine->draw_hline(dc,x1,x2,y1);
	}
}

void cogui_dc_draw_rect(cogui_dc_t *dc, cogui_rect_t *rect)
{
	COGUI_ASSERT(dc != Co_NULL);
	
	if(rect==Co_NULL)
		return;
	
	S32 x1,x2,y1,y2;
	
	x1=rect->x1;
	x2=rect->x2;
	y1=rect->y1;
	y2=rect->y2;
	
	dc->engine->draw_vline(dc, x1, y1, y2);
	dc->engine->draw_vline(dc, x2-1, y1, y2);
	dc->engine->draw_hline(dc, x1, x2, y1);
	dc->engine->draw_hline(dc, x1, x2, y2-1);
}


void cogui_dc_draw_shaded_rect(cogui_dc_t *dc, cogui_rect_t *rect, cogui_color_t c1, cogui_color_t c2)
{
	COGUI_ASSERT(dc != Co_NULL);
		
	COGUI_DC_FC(dc) = c1;
	dc->engine->draw_vline(dc, rect->x1, rect->y1, rect->y2);
	dc->engine->draw_hline(dc, rect->x1+1, rect->x2, rect->y1);
	
	COGUI_DC_FC(dc) = c2;
	dc->engine->draw_vline(dc, rect->x2-1, rect->y1, rect->y2);
	dc->engine->draw_hline(dc, rect->x1, rect->y1, rect->y2-1);
}

void cogui_dc_fill_rect_forecolor(cogui_dc_t *dc, cogui_rect_t *rect)
{
	COGUI_ASSERT(dc != Co_NULL);
	
	cogui_color_t save_color;
	
	save_color = COGUI_DC_BC(dc);
	COGUI_DC_BC(dc) = COGUI_DC_FC(dc);
	
	dc->engine->fill_rect(dc, rect);
	
	COGUI_DC_BC(dc) = save_color;
	
}

void cogui_dc_draw_border(cogui_dc_t *dc, cogui_rect_t *rect, int flag)
{
	cogui_rect_t r;
	//cogui_color_t c;
	
	COGUI_ASSERT(dc != Co_NULL);
	
	if(rect==Co_NULL)
		return;
	
	r = *rect;
	switch(flag)
	{
		case COGUI_BORDER_SIMPLE:
			COGUI_DC_FC(dc) = 0xFFFF;
			cogui_dc_draw_rect(dc, &r);
			break;
		case COGUI_BORDER_EXTRA:
			COGUI_DC_FC(dc) = 0xF7DE;
			cogui_dc_draw_rect(dc, &r);
			break;
		case COGUI_BORDER_SUNKEN:
			break;
		case COGUI_BORDER_BOX:
			break;
		case COGUI_BORDER_STATIC:
			break;
		case COGUI_BORDER_RAISE:
			break;
		default:
			break;
	}
}

struct cogui_gc *cogui_dc_get_gc(cogui_dc_t *dc)
{
	struct cogui_gc *gc = Co_NULL;
	
	COGUI_ASSERT(dc != Co_NULL);
	
	switch(dc->type)
	{
		case COGUI_DC_HW:
		{
			struct cogui_dc_hw *dchw;
			
			dchw = (struct cogui_dc_hw *)dc;
			
			gc = &dchw->owner->gc;
			break;
		}

		case COGUI_DC_CLIENT:
		case COGUI_DC_BUFFER:
		default:
			break;
	}
	
	return gc;
}

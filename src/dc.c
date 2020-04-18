/**
 *******************************************************************************
 * @file       dc.c
 * @version    V0.7.4
 * @date       2020.04.18
 * @brief      This is a file for GUI DC engine interface.	
 *******************************************************************************
 */ 

#include <cogui.h>

/**
 *******************************************************************************
 * @brief      Draw a line
 * @param[in]  *dc      Using this DC to draw
 * @param[in]  x1       Rectangle coordinate x1
 * @param[in]  x2       Rectangle coordinate x2
 * @param[in]  y1       Rectangle coordinate y1
 * @param[in]  y2       Rectangle coordinate y2
 * @param[out] None
 * @retval     None
 *******************************************************************************
 */
void gui_dc_draw_line(dc_t *dc, int32_t x1, int32_t x2, int32_t y1, int32_t y2)
{
	ASSERT(dc != Co_NULL);

    if (x1 == x2 && y1 == y2) {
		dc->engine->draw_point(dc, x1, y1);        /* this is a point         */
    } else if (x1 == x2) {
		dc->engine->draw_vline(dc, x1, y1, y2);    /* this is a line width 1  */
    } else if (y1 == y2) { 
		dc->engine->draw_hline(dc, x1, x2, y1);    /* this is a line height 1 */
    } else{        /* this is a line like rectangle                           */              
		_int_comp(x1, x2);
		_int_comp(y1, y2);
		
		for( ; y1 < y2; y1++) {
			dc->engine->draw_hline(dc, x1, x2, y1);
        }
	}
}

/**
 *******************************************************************************
 * @brief      Draw a hollow rectangle
 * @param[in]  *dc      Using this DC to draw
 * @param[in]  *rect    Draw this rectangle
 * @param[out] None
 * @retval     None
 *******************************************************************************
 */
void gui_dc_draw_rect(dc_t *dc, rect_t *rect)
{
	ASSERT(dc != Co_NULL);
	
	if (rect == Co_NULL) {
		return;     /* if no need to draw, just return                        */
    }
	
    /* draw rectangle's 4 edges                                               */
	dc->engine->draw_vline(dc, rect->x1,   rect->y1, rect->y2);
	dc->engine->draw_vline(dc, rect->x2-1, rect->y1, rect->y2);
	dc->engine->draw_hline(dc, rect->x1,   rect->x2, rect->y1);
	dc->engine->draw_hline(dc, rect->x1,   rect->x2, rect->y2-1);
}

/**
 *******************************************************************************
 * @brief      Draw a solid rectangle
 * @param[in]  *dc      Using this DC to draw
 * @param[in]  *rect    Draw this rectangle
 * @param[out] None
 * @retval     None
 *
 * @par Description
 * @details    This function is called to draw a solid rectangle and filled
 *             with foreground color.
 *******************************************************************************
 */
void gui_dc_fill_rect_forecolor(dc_t *dc, rect_t *rect)
{
	ASSERT(dc != Co_NULL);
	
	color_t save_color;
	
    /* Since the fill_rect interface will filled with background color, so we
     * should save the old background color and change background into current
     * foreground color */
	save_color    = GUI_DC_BC(dc);
	GUI_DC_BC(dc) = GUI_DC_FC(dc);
	
	dc->engine->fill_rect(dc, rect);    /* call de engine                     */
	
	GUI_DC_BC(dc) = save_color;     /* restore background color               */
}

void gui_dc_draw_shaded_rect(dc_t *dc, rect_t *rect, color_t c1, color_t c2)
{
	ASSERT(dc != Co_NULL);
		
	GUI_DC_FC(dc) = c1;
	dc->engine->draw_vline(dc, rect->x1,   rect->y1, rect->y2);
	dc->engine->draw_hline(dc, rect->x1+1, rect->x2, rect->y1);
	
	GUI_DC_FC(dc) = c2;
	dc->engine->draw_vline(dc, rect->x2-1, rect->y1, rect->y2);
	dc->engine->draw_hline(dc, rect->x1,   rect->x2, rect->y2-1);
}

void gui_dc_draw_border(dc_t *dc, rect_t *rect)
{
	ASSERT(dc != Co_NULL);

    if (rect == Co_NULL) {
		return;     /* if no need to draw, just return                        */
    }

	rect_t r = *rect;
	color_t save_color;

    save_color    = GUI_DC_FC(dc);
	GUI_DC_FC(dc) = light_grey;

	gui_dc_draw_rect(dc, &r);     /* first rect with light_grey for border  */

    GUI_RECT_EXPAND(&r, -1);
	gui_dc_draw_rect(dc, &r);     /* draw again since border width == 2     */

    GUI_DC_FC(dc) = save_color;   /* restore original foreground color      */
}

void gui_dc_draw_text(dc_t *dc, rect_t *rect, char *str)
{
	ASSERT(dc != Co_NULL);

    if (str == Co_NULL) {
        return;         /* pass if nothing to show                            */
    }

    uint16_t text_align = GUI_DC_TA(dc);
    int16_t  tx, ty;

    /* default style setting */
    if (text_align == GUI_TEXT_ALIGN_NONE) {
        tx = ty = 0;
    }

    uint32_t text_width = gui_get_text_width(str, GUI_DC_FONT(dc));
    uint32_t rect_width = GUI_RECT_WIDTH(rect);

    /* if text is too long, it will no longer align */
    if (text_width > rect_width) {
        text_width = rect_width;
    }

    /* fixed text start point x */
    if (text_align & GUI_TEXT_ALIGN_LEFT) {
        tx = 0;
    }
    else if (text_align & GUI_TEXT_ALIGN_CENTER) {
        tx = rect_width - text_width;
        tx /=2;
    }
    else if (text_align & GUI_TEXT_ALIGN_RIGHT) {
        tx = rect_width - text_width;
    }

    uint32_t text_height = gui_get_text_height(str, GUI_DC_FONT(dc), rect);
    uint32_t rect_height = GUI_RECT_HEIGHT(rect);

    /* text overflow-y: hidden */
    if (text_height > rect_height) {
        text_height = rect_height;
    } 

    /* fixed text start point y */
    if (text_align & GUI_TEXT_ALIGN_TOP) {
        ty = 0;
    }
    else if (text_align & GUI_TEXT_ALIGN_MIDDLE) {
        ty = rect_height - text_height;
        ty/=2;
    }
    else if (text_align & GUI_TEXT_ALIGN_BOTTOM) {
        ty = rect_height - text_height;
    }

    /* put text in the right place */
    gui_lcd_puts(tx+rect->x1, ty+rect->y1, str, GUI_DC_FONT(dc), dc, rect);
}

/**
 *******************************************************************************
 * @brief      Get graph context by DC
 * @param[in]  *dc      Using this DC to find
 * @param[out] None
 * @retval     *gc      Graph context
 *
 * @par Description
 * @details    This function is called to find graph context by giving DC 
 *             pointer.
 *******************************************************************************
 */
struct gc *gui_dc_get_gc(dc_t *dc)
{
	struct gc *gc = Co_NULL;
	
	ASSERT(dc != Co_NULL);
	
	switch(dc->type) {
		case GUI_DC_HW: {
			struct dc_hw_t *dchw;
			dchw = (struct dc_hw_t *)dc;
			
            /* get graph  context by its owner */
			gc = &dchw->owner->gc;
			break;
		}

		case GUI_DC_BUFFER:
		default:
			break;
	}
	
	return gc;
}

/**
 *******************************************************************************
 * @brief      Get DC's owner
 * @param[in]  *dc      Using this DC to find
 * @param[out] None
 * @retval     *owner   Which widget DC belong
 *
 * @par Description
 * @details    This function is called to find owner widget by giving DC 
 *             pointer.
 *******************************************************************************
 */
struct widget *gui_dc_get_owner(dc_t *dc)
{
	widget_t *owner = Co_NULL;
	
	ASSERT(dc != Co_NULL);
	
	switch(dc->type) {
		case GUI_DC_HW: {
			struct dc_hw_t *dchw;
			dchw = (struct dc_hw_t *)dc;
			
            /* get graph  context by its owner */
			owner = dchw->owner;
			break;
		}

		case GUI_DC_BUFFER:
		default:
			break;
	}
	
	return owner;
}

/**
 *******************************************************************************
 * @brief      Start drawing by using DC
 * @param[in]  *owner   Which widget should draw
 * @param[out] None
 * @retval     *dc      The DC pointer we create
 *
 * @par Description
 * @details    This function is called to start drawing by create a DC engine
 *             for it.
 *******************************************************************************
 */
dc_t *gui_dc_begin_drawing(widget_t *owner)
{
    dc_t *dc;

    ASSERT(owner != Co_NULL);

#if (COGUI_SCREEN_TYPE == 0)
    /* call hardware interface */
    dc = dc_hw_create(owner);
#else
#endif

    /* put dc pointer into owner structure */
    owner->dc_engine = dc;

    return dc;
}

/**
 *******************************************************************************
 * @brief      End drawing by using DC
 * @param[in]  *dc      The DC engine needs to free
 * @param[out] None
 * @retval     None
 *
 * @par Description
 * @details    This function is called to free a DC pointer.
 *******************************************************************************
 */
void gui_dc_end_drawing(dc_t *dc)
{
    ASSERT(dc != Co_NULL);

    /* call DC's fini function */
    dc->engine->fini(dc);
}

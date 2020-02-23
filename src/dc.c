/**
 *******************************************************************************
 * @file       dc.c
 * @version    V0.7.1
 * @date       2020.02.23
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
void cogui_dc_draw_line(cogui_dc_t *dc, co_int32_t x1, co_int32_t x2, co_int32_t y1, co_int32_t y2)
{
	COGUI_ASSERT(dc != Co_NULL);
	
    /* this is a line width 1 */
	if (x1 == x2)
		dc->engine->draw_vline(dc, x1, y1, y2);
    /* this is a line height 1*/
	else if (y1 == y2)
		dc->engine->draw_hline(dc, x1, x2, y1);
    /* this is a line like rectangle */
	else{
		_int_comp(x1, x2);
		_int_comp(y1, y2);
		
		for( ; y1 < y2; y1++)
			dc->engine->draw_hline(dc, x1, x2, y1);
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
void cogui_dc_draw_rect(cogui_dc_t *dc, cogui_rect_t *rect)
{
	COGUI_ASSERT(dc != Co_NULL);
	
	if (rect == Co_NULL)
		return;
	
	co_int32_t x1, x2, y1, y2;
	
	x1 = rect->x1;
	x2 = rect->x2;
	y1 = rect->y1;
	y2 = rect->y2;
	
    /* draw rectangle's 4 edges*/
	dc->engine->draw_vline(dc, x1,   y1, y2);
	dc->engine->draw_vline(dc, x2-1, y1, y2);
	dc->engine->draw_hline(dc, x1,   x2, y1);
	dc->engine->draw_hline(dc, x1,   x2, y2-1);
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
void cogui_dc_fill_rect_forecolor(cogui_dc_t *dc, cogui_rect_t *rect)
{
	COGUI_ASSERT(dc != Co_NULL);
	
	cogui_color_t save_color;
	
    /* Since the fill_rect interface will filled with background color, so we
     * should save the old background color and change background into current
     * foreground color */
	save_color      = COGUI_DC_BC(dc);
	COGUI_DC_BC(dc) = COGUI_DC_FC(dc);
	
    /* call interface */
	dc->engine->fill_rect(dc, rect);
	
    /* restore background color */
	COGUI_DC_BC(dc) = save_color;
}

void cogui_dc_draw_shaded_rect(cogui_dc_t *dc, cogui_rect_t *rect, cogui_color_t c1, cogui_color_t c2)
{
	COGUI_ASSERT(dc != Co_NULL);
		
	COGUI_DC_FC(dc) = c1;
	dc->engine->draw_vline(dc, rect->x1,   rect->y1, rect->y2);
	dc->engine->draw_hline(dc, rect->x1+1, rect->x2, rect->y1);
	
	COGUI_DC_FC(dc) = c2;
	dc->engine->draw_vline(dc, rect->x2-1, rect->y1, rect->y2);
	dc->engine->draw_hline(dc, rect->x1,   rect->x2, rect->y2-1);
}

void cogui_dc_draw_border(cogui_dc_t *dc, cogui_rect_t *rect)
{
	cogui_rect_t r = *rect;
	cogui_color_t save_color;
	
	COGUI_ASSERT(dc != Co_NULL);
	
	if (rect == Co_NULL)
		return;
	
    save_color      = COGUI_DC_FC(dc);
	COGUI_DC_FC(dc) = COGUI_LIGHT_GRAY;

	cogui_dc_draw_rect(dc, &r);

    COGUI_RECT_EXPAND(&r, -1);

	cogui_dc_draw_rect(dc, &r);

    COGUI_DC_FC(dc) = save_color;
}

void cogui_dc_draw_text(cogui_dc_t *dc, cogui_rect_t *rect, char *str)
{
	COGUI_ASSERT(dc != Co_NULL);

    /* pass if nothing to show */
    if (str == Co_NULL) {
        return;
    }

    co_uint16_t text_align = COGUI_DC_TA(dc);
    co_int16_t  tx, ty;

    /* default style setting */
    if (text_align == COGUI_TEXT_ALIGN_NONE) {
        tx = ty = 0;
    }

    co_uint32_t text_width = cogui_get_text_width(str, COGUI_DC_FONT(dc));
    co_uint32_t rect_width = COGUI_RECT_WIDTH(rect);

    /* if text is too long, it will no longer align */
    if (text_width > rect_width) {
        text_width = rect_width;
    }

    /* fixed text start point x */
    if (text_align & COGUI_TEXT_ALIGN_LEFT) {
        tx = 0;
    }
    else if (text_align & COGUI_TEXT_ALIGN_CENTER) {
        tx = rect_width - text_width;
        tx /=2;
    }
    else if (text_align & COGUI_TEXT_ALIGN_RIGHT) {
        tx = rect_width - text_width;
    }

    co_uint32_t text_height = cogui_get_text_height(str, COGUI_DC_FONT(dc), rect);
    co_uint32_t rect_height = COGUI_RECT_HEIGHT(rect);

    /* text overflow-y: hidden */
    if (text_height > rect_height) {
        text_height = rect_height;
    } 

    /* fixed text start point y */
    if (text_align & COGUI_TEXT_ALIGN_TOP) {
        ty = 0;
    }
    else if (text_align & COGUI_TEXT_ALIGN_MIDDLE) {
        ty = rect_height - text_height;
        ty/=2;
    }
    else if (text_align & COGUI_TEXT_ALIGN_BOTTOM) {
        ty = rect_height - text_height;
    }

    /* put text in the right place */
    cogui_lcd_puts(tx+rect->x1, ty+rect->y1, str, COGUI_DC_FONT(dc), dc, rect);
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
struct cogui_gc *cogui_dc_get_gc(cogui_dc_t *dc)
{
	struct cogui_gc *gc = Co_NULL;
	
	COGUI_ASSERT(dc != Co_NULL);
	
	switch(dc->type) {
		case COGUI_DC_HW: {
			struct cogui_dc_hw *dchw;
			dchw = (struct cogui_dc_hw *)dc;
			
            /* get graph  context by its owner */
			gc = &dchw->owner->gc;
			break;
		}

		case COGUI_DC_BUFFER:
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
struct cogui_widget *cogui_dc_get_owner(cogui_dc_t *dc)
{
	cogui_widget_t *owner = Co_NULL;
	
	COGUI_ASSERT(dc != Co_NULL);
	
	switch(dc->type) {
		case COGUI_DC_HW: {
			struct cogui_dc_hw *dchw;
			dchw = (struct cogui_dc_hw *)dc;
			
            /* get graph  context by its owner */
			owner = dchw->owner;
			break;
		}

		case COGUI_DC_BUFFER:
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
cogui_dc_t *cogui_dc_begin_drawing(cogui_widget_t *owner)
{
    cogui_dc_t *dc;

    COGUI_ASSERT(owner != Co_NULL);

#if (COGUI_SCREEN_TYPE == 0)
    /* call hardware interface */
    dc = cogui_dc_hw_create(owner);
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
void cogui_dc_end_drawing(cogui_dc_t *dc)
{
    COGUI_ASSERT(dc != Co_NULL);

    /* call DC's fini function */
    dc->engine->fini(dc);
}

/**
 *******************************************************************************
 * @file       dc.c
 * @version    V0.1.1
 * @date       2019.10.5
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
    /* this is a line height 2 */
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

void cogui_dc_draw_button(cogui_dc_t *dc, co_int16_t flag)
{
    COGUI_ASSERT(dc != Co_NULL);

    if (flag & COGUI_WINTITLE_BTN_BORDER) {
        cogui_rect_t rect;
        COGUI_SET_RECT(&rect, 0, 0, COGUI_WINTITLE_BTN_HEIGHT, COGUI_WINTITLE_BTN_HEIGHT);
        cogui_dc_draw_rect(dc, &rect);
    }

    if (flag & COGUI_WINTITLE_BTN_CLOSE) {
        co_int16_t i, j;

        for ( i = 0; i < COGUI_WINTITLE_BTN_INNER_HEIGHT; i++) {
            for ( j = 0; j < COGUI_WINTITLE_BTN_INNER_HEIGHT; j++) {
                if ( _UI_ABS(i - j) > 3 )   /* skip other pixels */
                    continue;

                if ((i == 0  && j <= 1)  || (i == 1  && j == 0)  || /* skip left top corner     */
                    (i == 28 && j == 0)  || (i == 29 && j <= 1)  || /* skip right top corner    */
                    (i == 0  && j >= 28) || (i == 1  && j == 29) || /* skip left bottom corner  */
                    (i == 28 && j == 29) || (i == 29 && j >= 28)) { /* skip right bottom corner */
                    continue;
                }

                dc->engine->draw_point(dc, i+2, j+2);   /* positive diagonal */
                dc->engine->draw_point(dc, 31-i, j+2);  /* negative diagonal */
            }
        }
    }

    if (flag & COGUI_WINTITLE_BTN_MINI) {      
        cogui_dc_draw_line(dc, 2, 31, 15, 19);
    }
}

void cogui_dc_draw_title(cogui_dc_t *dc) {
    COGUI_ASSERT(dc != Co_NULL);

    cogui_dc_t *cdc = cogui_dc_get_owner(dc)->next->dc_engine;
    cogui_dc_t *mdc = cogui_dc_get_owner(dc)->next->next->dc_engine;

    cogui_rect_t rect;
    COGUI_SET_RECT(&rect, 0, 0, 240, COGUI_WINTITLE_HEIGHT);
    
    /* draw background */
    dc->engine->fill_rect(dc, &rect);
    //cogui_dc_draw_line(dc, 0, 240, 0, COGUI_WINTITLE_HEIGHT);

    /* draw close button */
    cogui_dc_draw_button(cdc, COGUI_WINTITLE_BTN_CLOSE);
    /* draw mini button */
    cogui_dc_draw_button(mdc,  COGUI_WINTITLE_BTN_MINI);

    char *title = cogui_dc_get_owner(dc)->top->title_name;

    /* show title name */
    cogui_tm_16x26_puts(100, 7, title, cogui_dc_get_owner(dc));
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

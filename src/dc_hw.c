/**
 *******************************************************************************
 * @file       dc_hw.c
 * @version    V0.6.1
 * @date       2020.01.18
 * @brief      This is a file for GUI hardware DC engine.	
 *******************************************************************************
 */ 

#include <cogui.h>

static void cogui_dc_hw_draw_point(cogui_dc_t *dc, co_int32_t x, co_int32_t y);
static void cogui_dc_hw_draw_color_point(cogui_dc_t *dc, co_int32_t x, co_int32_t y, cogui_color_t color);
static void cogui_dc_hw_draw_vline(cogui_dc_t *dc, co_int32_t x, co_int32_t y1, co_int32_t y2);
static void cogui_dc_hw_draw_hline(cogui_dc_t *dc, co_int32_t x1, co_int32_t x2, co_int32_t y);
static void cogui_dc_hw_fill_rect(cogui_dc_t *dc, cogui_rect_t *rect);
static StatusType cogui_dc_hw_fini(cogui_dc_t *dc);

struct cogui_dc_engine dc_hw_engine =
{
    cogui_dc_hw_draw_point,
    cogui_dc_hw_draw_color_point,
    cogui_dc_hw_draw_vline,
    cogui_dc_hw_draw_hline,
    cogui_dc_hw_fill_rect,

    cogui_dc_hw_fini,
};

/**
 *******************************************************************************
 * @brief      Create a hardware DC 
 * @param[in]  *owner   Widget which DC belone
 * @param[out] None
 * @retval     *dc		DC pointer which we create     
 *******************************************************************************
 */
cogui_dc_t *cogui_dc_hw_create(cogui_widget_t *owner)
{
    struct cogui_dc_hw *dc;

    if (owner == Co_NULL)
        return Co_NULL;

    dc = (struct cogui_dc_hw *) cogui_malloc(sizeof(struct cogui_dc_hw));
    if (dc) {
        dc->parent.type = COGUI_DC_HW;
        dc->parent.engine = &dc_hw_engine;
        dc->owner = owner;
        dc->hw_driver = cogui_graphic_driver_get_default();
		
        return (cogui_dc_t *)dc;
    }

    return Co_NULL;
}

/**
 *******************************************************************************
 * @brief      Finish a hardware DC 
 * @param[in]  *dc      Which DC should finish
 * @param[out] None
 * @retval     GUI_E_OK	    Finish successfully
 * @retval     GUI_E_ERROR	Something wrong with this DC
 *******************************************************************************
 */
static StatusType cogui_dc_hw_fini(cogui_dc_t *dc)
{
    if (dc == Co_NULL || dc->type != COGUI_DC_HW)
        return GUI_E_ERROR;

    /* release hardware DC */
    cogui_free(dc);

    return GUI_E_OK;
}

/**
 *******************************************************************************
 * @brief      Draw a point through hardware DC 
 * @param[in]  *self        Which DC we used
 * @param[in]  x            Coordinate x
 * @param[in]  y            Coordinate y
 * @param[out] None
 * @retval     None
 *******************************************************************************
 */
static void cogui_dc_hw_draw_point(cogui_dc_t *self, co_int32_t x, co_int32_t y)
{
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(self != Co_NULL);
    dc = (struct cogui_dc_hw *) self;

    /* determine the point is vaild or not */
    if (x < 0 || y < 0)
        return;

    /* move x to logic x */
    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2) 
        return;
    
    /* move y to logic y */
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2) 
        return;

    /* draw this point */
    dc->hw_driver->ops->set_pixel(&(dc->owner->gc.foreground), x, y);
}

/**
 *******************************************************************************
 * @brief      Draw a color point through hardware DC 
 * @param[in]  *self        Which DC we used
 * @param[in]  x            Coordinate x
 * @param[in]  y            Coordinate y
 * @param[in]  color        Which color we choose
 * @param[out] None
 * @retval     None
 *******************************************************************************
 */
static void cogui_dc_hw_draw_color_point(cogui_dc_t *self, co_int32_t x, co_int32_t y, cogui_color_t color)
{
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(self != Co_NULL);
    dc = (struct cogui_dc_hw *) self;

    /* determine the point is vaild or not */
    if (x < 0 || y < 0)
        return;

    /* move x to logic x */
    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2)
        return;
    
    /* move y to logic y */
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2)
        return;
    
    /* draw this point */
    dc->hw_driver->ops->set_pixel(&color, x, y);
}

/**
 *******************************************************************************
 * @brief      Draw a vertical line through hardware DC 
 * @param[in]  *self        Which DC we used
 * @param[in]  x            Coordinate x
 * @param[in]  y1           Coordinate y1
 * @param[in]  y2           Coordinate y2
 * @param[out] None
 * @retval     None
 *
 * @par Description
 * @details    This function is called to draw a vertical line through hardware
 *             DC, this line is (y2-y1) height.
 *******************************************************************************
 */
static void cogui_dc_hw_draw_vline(cogui_dc_t *self, co_int32_t x, co_int32_t y1, co_int32_t y2)
{
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(self != Co_NULL);
    dc = (struct cogui_dc_hw *) self;

    /* determine x is vaild or not */
    if (x < 0)
        return;

    /* move x to logic x */
    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2)
        return;

    /* move y1 and y2 to logic */    
    y1 = y1 + dc->owner->extent.y1;
    y2 = y2 + dc->owner->extent.y1;

    /* y1 should less than y2 */
    if (y1 > y2)
        _int_swap(y1, y2);
    
    /* determine y1 and y2 are vaild or not */
    if (y1 > dc->owner->extent.y2 || y2 < dc->owner->extent.y1)
        return;

    /* if the line is over extent, cut it */
    if (y1 < dc->owner->extent.y1)
        y1 = dc->owner->extent.y1;
    
    if (y2 > dc->owner->extent.y2)
        y2 = dc->owner->extent.y2;

    /* draw this line */
    dc->hw_driver->ops->draw_vline(&(dc->owner->gc.foreground), x, y1, y2);
}

/**
 *******************************************************************************
 * @brief      Draw a horizontal line through hardware DC 
 * @param[in]  *self        Which DC we used
 * @param[in]  x1           Coordinate x1
 * @param[in]  x2           Coordinate x2
 * @param[in]  y            Coordinate y
 * @param[out] None
 * @retval     None
 *
 * @par Description
 * @details    This function is called to draw a horizontal line through hardware
 *             DC, this line is (x2-x1) width.
 *******************************************************************************
 */
static void cogui_dc_hw_draw_hline(cogui_dc_t *self, co_int32_t x1, co_int32_t x2, co_int32_t y)
{
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(self != Co_NULL);
    dc = (struct cogui_dc_hw *) self;

    /* determine y is vaild or not */
    if (y < 0)
        return;
    
    /* move y to logic y */
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2)
        return;

    /* move x1 and x2 to logic */    
    x1 = x1 + dc->owner->extent.x1;
    x2 = x2 + dc->owner->extent.x1;

    /* x1 should less than x2 */
    if (x1 > x2)
        _int_swap(x1, x2);
    
    /* determine x1 and x2 are vaild or not */
    if (x1 > dc->owner->extent.x2 || x2 < dc->owner->extent.x1)
        return;

    /* if the line is over extent, cut it */
    if (x1 < dc->owner->extent.x1)
        x1 = dc->owner->extent.x1;
    
    if (x2 > dc->owner->extent.x2)
        x2 = dc->owner->extent.x2;

    /* draw this line */
    dc->hw_driver->ops->draw_hline(&(dc->owner->gc.foreground), x1, x2, y);
}

/**
 *******************************************************************************
 * @brief      Filled a rectangle through hardware DC 
 * @param[in]  *self        Which DC we used
 * @param[in]  *rect        Which rect we filled
 * @param[out] None
 * @retval     None
 *
 * @par Description
 * @details    This function is called to filled a rectangle line through hardware
 *             DC, and choose graph context's background to fill.
 *******************************************************************************
 */
static void cogui_dc_hw_fill_rect(cogui_dc_t *self, cogui_rect_t *rect)
{
    cogui_color_t color;
    co_int32_t y1, y2, x1, x2;
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(rect);
    COGUI_ASSERT(self != Co_NULL);
    dc = (struct cogui_dc_hw *) self;

    /* get background color */
    color = dc->owner->gc.background;

    /* move to logic position */
    x1 = rect->x1 + dc->owner->extent.x1;
    if (x1 > dc->owner->extent.x2)
        return;
    
    if (x1 < dc->owner->extent.x1)
        x1 = dc->owner->extent.x1;
    
    x2 = rect->x2 + dc->owner->extent.x1;
    if (x2 < dc->owner->extent.x1)
        return;
    
    if (x2 > dc->owner->extent.x2)
        x2 = dc->owner->extent.x2;        
    

    y1 = rect->y1 + dc->owner->extent.y1;
    if (y1 > dc->owner->extent.y2)
        return;
    
    if (y1 < dc->owner->extent.y1)
        y1 = dc->owner->extent.y1;
    
    y2 = rect->y2 + dc->owner->extent.y1;
    if (y2 < dc->owner->extent.y1)
        return;
    
    if (y2 > dc->owner->extent.y2)
        y2 = dc->owner->extent.y2;
    
    /* fille rectangle */
    for (; y1 < y2; y1++) {
        dc->hw_driver->ops->draw_hline(&color, x1, x2, y1);
    }
}

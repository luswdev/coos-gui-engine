/**
 *******************************************************************************
 * @file       dc_hw.c
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      This is a file for GUI hardware DC engine.	
 *******************************************************************************
 */ 

#include <cogui.h>

static void dc_hw_draw_point(dc_t *dc, int32_t x, int32_t y);
static void dc_hw_draw_color_point(dc_t *dc, int32_t x, int32_t y, color_t color);
static void dc_hw_draw_vline(dc_t *dc, int32_t x, int32_t y1, int32_t y2);
static void dc_hw_draw_hline(dc_t *dc, int32_t x1, int32_t x2, int32_t y);
static void dc_hw_fill_rect(dc_t *dc, rect_t *rect);
static StatusType dc_hw_fini(dc_t *dc);

struct dc_engine dc_hw_engine =
{
    dc_hw_draw_point,
    dc_hw_draw_color_point,
    dc_hw_draw_vline,
    dc_hw_draw_hline,
    dc_hw_fill_rect,

    dc_hw_fini,
};

/**
 *******************************************************************************
 * @brief      Create a hardware DC 
 * @param[in]  *owner   Widget which DC belone
 * @param[out] None
 * @retval     *dc		DC pointer which we create     
 *******************************************************************************
 */
dc_t *dc_hw_create(widget_t *owner)
{
    struct dc_hw_t *dc;

    if (owner == Co_NULL)
        return Co_NULL;

    dc = (struct dc_hw_t *) gui_malloc(sizeof(struct dc_hw_t));
    if (dc) {
        dc->parent.type = GUI_DC_HW;
        dc->parent.engine = &dc_hw_engine;
        dc->owner = owner;
        dc->hw_driver = gui_graphic_driver_get_default();
		
        return (dc_t *)dc;
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
static StatusType dc_hw_fini(dc_t *dc)
{
    if (dc == Co_NULL || dc->type != GUI_DC_HW)
        return GUI_E_ERROR;

    /* release hardware DC */
    gui_free(dc);

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
static void dc_hw_draw_point(dc_t *self, int32_t x, int32_t y)
{
    struct dc_hw_t *dc;

    ASSERT(self != Co_NULL);
    dc = (struct dc_hw_t *) self;

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
static void dc_hw_draw_color_point(dc_t *self, int32_t x, int32_t y, color_t color)
{
    struct dc_hw_t *dc;

    ASSERT(self != Co_NULL);
    dc = (struct dc_hw_t *) self;

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
static void dc_hw_draw_vline(dc_t *self, int32_t x, int32_t y1, int32_t y2)
{
    struct dc_hw_t *dc;

    ASSERT(self != Co_NULL);
    dc = (struct dc_hw_t *) self;

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
static void dc_hw_draw_hline(dc_t *self, int32_t x1, int32_t x2, int32_t y)
{
    struct dc_hw_t *dc;

    ASSERT(self != Co_NULL);
    dc = (struct dc_hw_t *) self;

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
static void dc_hw_fill_rect(dc_t *self, rect_t *rect)
{
    color_t color;
    int32_t y1, y2, x1, x2;
    struct dc_hw_t *dc;

    ASSERT(rect);
    ASSERT(self != Co_NULL);
    dc = (struct dc_hw_t *) self;

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

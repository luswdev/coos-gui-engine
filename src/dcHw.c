/**
 *******************************************************************************
 * @file       dcHw.c
 * @version    V0.0.1   
 * @date       2019.5.29
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#include "cogui.h"

/*---------------------------- Function declare ------------------------------*/
static void cogui_dc_hw_draw_point(cogui_dc_t *dc, S32 x, S32 y);
static void cogui_dc_hw_draw_color_point(cogui_dc_t *dc, S32 x, S32 y, cogui_color_t color);
static void cogui_dc_hw_draw_vline(cogui_dc_t *dc, S32 x, S32 y1, S32 y2);
static void cogui_dc_hw_draw_hline(cogui_dc_t *dc, S32 x1, S32 x2, S32 y);
static void cogui_dc_hw_fill_rect(cogui_dc_t *dc, P_GuiRect rect);
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
 * @brief      create a dc engine (hw) 
 * @param[in]  owner    which widget own it		
 * @param[out] None
 * @retval     dc       engine ptr			 
 * @retval     Co_NULL  create failed		 
 *
 * @par Description
 * @details    This function is called to create a dc engine (hw).
 *******************************************************************************
 */
cogui_dc_t *cogui_dc_hw_create(cogui_widget_t *owner)
{
    struct cogui_dc_hw *dc;

    /* adjudge owner */
    if (owner==Co_NULL){
        return Co_NULL;
    }

    /* create DC */
    dc = (struct cogui_dc_hw *) cogui_malloc(sizeof(struct cogui_dc_hw));
    if (dc)
    {
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
 * @brief      free a dc engine (hw) 
 * @param[in]  dc           engine ptr	
 * @param[out] None		 
 * @retval     Co_TRUE      good		 
 * @retval     Co_FALSE     bad		 
 *
 * @par Description
 * @details    This function is called to free a dc engine (hw).
 *******************************************************************************
 */
static StatusType cogui_dc_hw_fini(cogui_dc_t *dc)
{
    if (dc == Co_NULL || dc->type != COGUI_DC_HW)
        return Co_FALSE;

    /* release hardware dc */
    GuiFree(dc);

    return Co_TRUE;
}

/**
 *******************************************************************************
 * @brief      draw a point
 * @param[in]  self           engine ptr	
 * @param[in]  x              point position x	
 * @param[in]  y              point position y
 * @param[out] None		 
 * @retval     None 
 *
 * @par Description
 * @details    This function is called to draw a point.
 *******************************************************************************
 */
static void cogui_dc_hw_draw_point(cogui_dc_t *self, S32 x, S32 y)
{
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(self != Co_NULL);

    dc = (struct cogui_dc_hw *) self;

    if (x < 0 || y < 0)
        return;

    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2) 
        return;
    
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2) 
        return;

    /* draw this point */
    dc->hwDriver->ops->set_pixel(&(dc->owner->gc.foreground), x, y);
}

/**
 *******************************************************************************
 * @brief      draw a color point
 * @param[in]  self           engine ptr	
 * @param[in]  x              point position x	
 * @param[in]  y              point position y
 * @param[in]  color          draw which color
 * @param[out] None		 
 * @retval     None 
 *
 * @par Description
 * @details    This function is called to draw a color point.
 *******************************************************************************
 */
static void cogui_dc_hw_draw_color_point(cogui_dc_t *self, S32 x, S32 y, cogui_color_t color)
{
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(self != Co_NULL);

    dc = (struct cogui_dc_hw *) self;

    if (x < 0 || y < 0)
        return;

    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2)
        return;
    
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2)
        return;
    

    /* draw this point */
    dc->hwDriver->ops->set_pixel(&color, x, y);
}

/**
 *******************************************************************************
 * @brief      draw a vertical line
 * @param[in]  self           engine ptr	
 * @param[in]  x              line position x	
 * @param[in]  y1             line position bottom y
 * @param[in]  y2             line position top y
 * @param[out] None		 
 * @retval     None 
 *
 * @par Description
 * @details    This function is called to draw a vertical line.
 *******************************************************************************
 */
static void cogui_dc_hw_draw_vline(cogui_dc_t *self, S32 x, S32 y1, S32 y2)
{
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(self != Co_NULL);

    dc = (struct cogui_dc_hw *) self;

    if (x < 0){
        return;
    }

    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2)
        return;
    
    y1 = y1 + dc->owner->extent.y1;
    y2 = y2 + dc->owner->extent.y1;

    if (y1 > y2)
        _intSwap(y1, y2);
    
    if (y1 > dc->owner->extent.y2 || y2 < dc->owner->extent.y1)
        return;

    if (y1 < dc->owner->extent.y1)
        y1 = dc->owner->extent.y1;
    
    if (y2 > dc->owner->extent.y2)
        y2 = dc->owner->extent.y2;

    /* draw vline */
    dc->hwDriver->ops->draw_vline(&(dc->owner->gc.foreground), x, y1, y2);
}

/**
 *******************************************************************************
 * @brief      draw a horizontal line
 * @param[in]  self           engine ptr	
 * @param[in]  x1             line position left x	
 * @param[in]  x2             line position right x
 * @param[in]  y              line position y
 * @param[out] None		 
 * @retval     None 
 *
 * @par Description
 * @details    This function is called to draw a horizontal line.
 *******************************************************************************
 */
static void cogui_dc_hw_draw_hline(cogui_dc_t *self, S32 x1, S32 x2, S32 y)
{
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(self != Co_NULL);
	
    dc = (struct cogui_dc_hw *) self;

    if (y < 0)
        return;
    
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2)
        return;

    /* convert logic to device */
    x1 = x1 + dc->owner->extent.x1;
    x2 = x2 + dc->owner->extent.x1;
    if (x1 > x2)
        _int_swap(x1, x2);
    
    if (x1 > dc->owner->extent.x2 || x2 < dc->owner->extent.x1)
        return;

    if (x1 < dc->owner->extent.x1)
        x1 = dc->owner->extent.x1;
    
    if (x2 > dc->owner->extent.x2)
        x2 = dc->owner->extent.x2;
    

    /* draw hline */
    dc->hwDriver->ops->draw_hline(&(dc->owner->gc.foreground), x1, x2, y);
}

/**
 *******************************************************************************
 * @brief      fill a rectangle
 * @param[in]  self           engine ptr	
 * @param[in]  rect           rectangle ptr
 * @param[out] None		 
 * @retval     None 
 *
 * @par Description
 * @details    This function is called to fill a rectangle.
 *******************************************************************************
 */
static void cogui_dc_hw_fill_rect(cogui_dc_t *self, P_GuiRect rect)
{
    cogui_color_t color;
    S32 y1, y2, x1, x2;
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(self != Co_NULL);
	COGUI_ASSERT(rect);
    
    dc = (struct cogui_dc_hw *) self;

    /* get background color */
    color = dc->owner->gc.background;

    /* convert logic to device */
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
    

    /* fill rect */
    for (; y1 < y2; y1++)
    {
        dc->hwDriver->ops->draw_hline(&color, x1, x2, y1);
    }
}

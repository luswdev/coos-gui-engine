/**
 *******************************************************************************
 * @file       dcHw.c
 * @version    V0.1.0  
 * @date       2019.8.9
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"

static void cogui_dc_hw_draw_point(cogui_dc_t *dc, S32 x, S32 y);
static void cogui_dc_hw_draw_color_point(cogui_dc_t *dc, S32 x, S32 y, cogui_color_t color);
static void cogui_dc_hw_draw_vline(cogui_dc_t *dc, S32 x, S32 y1, S32 y2);
static void cogui_dc_hw_draw_hline(cogui_dc_t *dc, S32 x1, S32 x2, S32 y);
static void cogui_dc_hw_fill_rect(cogui_dc_t *dc, cogui_rect_t rect);
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

cogui_dc_t *cogui_dc_hw_create(cogui_widget_t *owner)
{
    struct cogui_dc_hw *dc;

    if (owner==Co_NULL)
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

static StatusType cogui_dc_hw_fini(cogui_dc_t *dc)
{
    if (dc == Co_NULL || dc->type != COGUI_DC_HW)
        return Co_FALSE;

    cogui_free(dc);

    return Co_TRUE;
}

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

    dc->hwDriver->ops->set_pixel(&(dc->owner->gc.foreground), x, y);
}

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
    
    dc->hwDriver->ops->set_pixel(&color, x, y);
}

static void cogui_dc_hw_draw_vline(cogui_dc_t *self, S32 x, S32 y1, S32 y2)
{
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(self != Co_NULL);

    dc = (struct cogui_dc_hw *) self;

    if (x < 0)
        return;

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

    dc->hwDriver->ops->draw_vline(&(dc->owner->gc.foreground), x, y1, y2);
}

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

    dc->hwDriver->ops->draw_hline(&(dc->owner->gc.foreground), x1, x2, y);
}

static void cogui_dc_hw_fill_rect(cogui_dc_t *self, cogui_rect_tv rect)
{
    cogui_color_t color;
    S32 y1, y2, x1, x2;
    struct cogui_dc_hw *dc;

    COGUI_ASSERT(self != Co_NULL);
	COGUI_ASSERT(rect);
    
    dc = (struct cogui_dc_hw *) self;

    color = dc->owner->gc.background;

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
    
    for (; y1 < y2; y1++) {
        dc->hwDriver->ops->draw_hline(&color, x1, x2, y1);
    }
}

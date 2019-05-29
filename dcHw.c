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
static void DcHwDrawPoint(P_GuiDc dc, S32 x, S32 y);
static void DcHwDrawColorPoint(P_GuiDc dc, S32 x, S32 y, GUI_COLOR color);
static void DcHwDrawVline(P_GuiDc dc, S32 x, S32 y1, S32 y2);
static void DcHwDrawHline(P_GuiDc dc, S32 x1, S32 x2, S32 y);
static void DcHwFillRect(P_GuiDc dc, P_GuiRect rect);
static StatusType DcHwFini(P_GuiDc dc);

const GuiDcEng dcHwEngine =
{
    DcHwDrawPoint,
    DcHwDrawColorPoint,
    DcHwDrawVline,
    DcHwDrawHline,
    DcHwFillRect,

    DcHwFini,
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
P_GuiDc DcHwCreate(P_GuiWidget owner)
{
    struct dcHw *dc;

    /* adjudge owner */
    if (owner==Co_NULL || owner->toplevel==Co_NULL){
        return Co_NULL;
    }

    /* create DC */
    dc = (struct dcHw *) GuiMalloc(sizeof(struct dcHw));
    if (dc)
    {
        dc->parent.type = GUI_DC_HW;
        dc->parent.engine = &dc_hw_engine;
        dc->owner = owner;
        dc->hwDriver = GraphiDriverGetDefault();

        return &(dc->parent);
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
static StatusType DcHwFini(P_GuiDc dc)
{
    if (dc==Co_NULL || dc->type!=GUI_DC_HW){
        return Co_FALSE;
    }

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
static void DcHwDrawPoint(P_GuiDc self, S32 x, S32 y)
{
    struct dcHw *dc;

    if(self==Co_NULL){
        return;
    }

    dc = (struct dcHw *) self;

    if (x < 0 || y < 0){
        return;
    }

    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2){
        return;
    }
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2){
        return;
    }

    /* draw this point */
    dc->hw_driver->ops->setPixel(&(dc->owner->gc.foreground), x, y);
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
static void DcHwDrawColorPoint(P_GuiDc self, S32 x, S32 y, GUI_COLOR color)
{
    struct dcHw *dc;

    if(self==Co_NULL){
        return;
    }

    dc = (struct dcHw *) self;

    if (x < 0 || y < 0){
        return;
    }

    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2){
        return;
    }
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2){
        return;
    }

    /* draw this point */
    dc->hw_driver->ops->setPixel(&color, x, y);
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
static void DcHwDrawVline(P_GuiDc self, S32 x, S32 y1, S32 y2)
{
    struct dcHw *dc;

    if(self==Co_NULL){
        return;
    }

    dc = (struct dcHw *) self;

    if (x < 0){
        return;
    }

    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2){
        return;
    }
    y1 = y1 + dc->owner->extent.y1;
    y2 = y2 + dc->owner->extent.y1;

    if (y1 > y2){
        _intSwap(y1, y2);
    }
    if (y1 > dc->owner->extent.y2 || y2 < dc->owner->extent.y1){
        return;
    }

    if (y1 < dc->owner->extent.y1){
        y1 = dc->owner->extent.y1;
    }
    if (y2 > dc->owner->extent.y2){
        y2 = dc->owner->extent.y2;
    }

    /* draw vline */
    dc->hw_driver->ops->drawVline(&(dc->owner->gc.foreground), x, y1, y2);
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
static void DcHwDrawHline(P_GuiDc self, S32 x1, S32 x2, S32 y)
{
    struct dcHw *dc;

    if(self==Co_NULL){
        return;
    }

    dc = (struct dcHw *) self;

    if (y < 0){
        return;
    }
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2){
        return;
    }

    /* convert logic to device */
    x1 = x1 + dc->owner->extent.x1;
    x2 = x2 + dc->owner->extent.x1;
    if (x1 > x2){
        _int_swap(x1, x2);
    }
    if (x1 > dc->owner->extent.x2 || x2 < dc->owner->extent.x1){
        return;
    }

    if (x1 < dc->owner->extent.x1){
        x1 = dc->owner->extent.x1;
    }
    if (x2 > dc->owner->extent.x2){
        x2 = dc->owner->extent.x2;
    }

    /* draw hline */
    dc->hw_driver->ops->drawHline(&(dc->owner->gc.foreground), x1, x2, y);
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
static void DcHwFillRect(P_GuiDc self, P_GuiRect rect)
{
    GUI_COLOR color;
    register U64 y1, y2, x1, x2;
    struct dcHw *dc;

    if(self==Co_NULL || !rect){
        return;
    }
    
    dc = (struct dcHw *) self;

    /* get background color */
    color = dc->owner->gc.background;

    /* convert logic to device */
    x1 = rect->x1 + dc->owner->extent.x1;
    if (x1 > dc->owner->extent.x2){
        return;
    }
    if (x1 < dc->owner->extent.x1){
        x1 = dc->owner->extent.x1;\
    }
    x2 = rect->x2 + dc->owner->extent.x1;
    if (x2 < dc->owner->extent.x1){
        return;
    }
    if (x2 > dc->owner->extent.x2){
        x2 = dc->owner->extent.x2;        
    }

    y1 = rect->y1 + dc->owner->extent.y1;
    if (y1 > dc->owner->extent.y2){
        return;
    }
    if (y1 < dc->owner->extent.y1){
        y1 = dc->owner->extent.y1;
    }
    y2 = rect->y2 + dc->owner->extent.y1;
    if (y2 < dc->owner->extent.y1){
        return;
    }
    if (y2 > dc->owner->extent.y2){
        y2 = dc->owner->extent.y2;
    }

    /* fill rect */
    for (; y1 < y2; y1++)
    {
        dc->hw_driver->ops->drawHline(&color, x1, x2, y1);
    }
}
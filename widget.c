/**
 *******************************************************************************
 * @file       widget.c
 * @version    V0.0.1   
 * @date       2019.5.26
 * @brief      Some widget function for GUI engine's event.	
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "cogui.h"

/**
 *******************************************************************************
 * @brief      Initial a widget	 
 * @param[in]  widget     widget ptr		
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to initial a widget.
 *******************************************************************************
 */
void _WidgetInit(P_GuiWidget widget)
{
    /* set parent and toplevel root */
    widget->parent        = Co_NULL;
    widget->topLevel      = Co_NULL;

    widget->minWidth = widget->minHeight = 0;

    /* some common event handler */
    widget->onFocusIn   = Co_NULL;
    widget->onFocusOut  = Co_NULL;

    /* set default event handler */
    widget->handler = WidgetEventHandler;

    /* init user data private to 0 */
    widget->user_data = 0;
}

/**
 *******************************************************************************
 * @brief      create a widget	 
 * @param[in]  None		
 * @param[out] Co_NULL      create failed
 * @param[out] widget       widget
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to create a widget.
 *******************************************************************************
 */
P_GuiWidget WidgetCreate()
{
    P_GuiWidget widget;

    widget = GuiMalloc(sizeof(GuiWidget));
    if(widget==Co_NULL){
        return Co_NULL;
    }
    
    _WidgetInit(widget);

    return widget;
}

/**
 *******************************************************************************
 * @brief      delete a widget	 
 * @param[in]  widget       widget ptr		
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to delete a widget.
 *******************************************************************************
 */
void WidgetDel(P_GuiWidget widget)
{   
    GuiFree(widget);
}

/**
 *******************************************************************************
 * @brief      set widget focus handler
 * @param[in]  widget       widget ptr	
 * @param[in]  handler      handler ptr	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set widget focus handler.
 *******************************************************************************
 */
void WidgetSetFocus(P_GuiWidget widget, EventHandlerPtr handler)
{
    if(widget!=Co_NULL){
        widget->OnFocusIn = handler;
    }
}

/**
 *******************************************************************************
 * @brief      set widget unfocus handler
 * @param[in]  widget       widget ptr	
 * @param[in]  handler      handler ptr	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set widget unfocus handler.
 *******************************************************************************
 */
void WidgetSetUnFocus(P_GuiWidget widget, EventHandlerPtr handler)
{
    if(widget!=Co_NULL){
        widget->OnFocusOut = handler;
    }
}


/**
 *******************************************************************************
 * @brief      let widget focus
 * @param[in]  widget       widget ptr	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to let widget focus.
 *******************************************************************************
 */
void WidgetFocus(P_GuiWidget widget)
{
    P_GuiWidget oldFocus;

    if(widget==Co_NULL || widget->topLevel==Co_NULL){
        return;
    }

    if(!(widget->flag&GUI_WIDGET_FLAG_FOCUSABLE) || 
       (widget->flag&GUI_WIDGET_FLAG_DISABLE)){
        return;
    }

    oldFocus = widget->topLevel->focusWidget;
    if(oldFocus==widget){   /* it's the same focused widget */
        return;
    }

    /* unfocused the old widget */
    if (oldFocus != Co_NULL)
        WidgetUnfocus(oldFocus);

    /* set widget as focused */
    widget->flag |= GUI_WIDGET_FLAG_FOCUS;
    widget->topLevel->focusWidget = widget;

    /* invoke on focus in call back */
    if (widget->onFocusIn != Co_NULL)
        widget->onFocusIn(widget, Co_NULL);
}


/**
 *******************************************************************************
 * @brief      let widget unfocus handler
 * @param[in]  widget       widget ptr	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to let widget unfocus handler.
 *******************************************************************************
 */
void WidgetUnFocus(P_GuiWidget widget)
{
    if(widget==Co_NULL){
        return;
    }

    if (!widget->topLevel || !(widget->flag&GUI_WIDGET_FLAG_FOCUS)){
        return;
    }

    widget->flag &= ~GUI_WIDGET_FLAG_FOCUS;

    if (widget->on_focus_out != Co_NULL){
        widget->on_focus_out(widget, Co_NULL);
    }

    widget->topLevel->focusWidget = Co_NULL;
}


/**
 *******************************************************************************
 * @brief      get widget rectangle
 * @param[in]  widget       widget ptr	
 * @param[in]  rect         rect ptr	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to get widget rectangle.
 *******************************************************************************
 */
void WidgetGetRect(P_GuiWidget widget, P_GuiRect rect)
{
    if(widget==Co_NULL){
        return;
    }

    if (rect != Co_NULL){
        rect->x1 = rect->y1 = 0;
        rect->x2 = widget->extent.x2 - widget->extent.x1;
        rect->y2 = widget->extent.y2 - widget->extent.y1;
    }
}

/**
 *******************************************************************************
 * @brief      set widget border style
 * @param[in]  widget       widget ptr	
 * @param[in]  style        border style	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set widget border style.
 *******************************************************************************
 */
void WidgetSetBorder(P_GuiWidget widget, U32 style)
{
    if(widget == Co_NULL){
        return;
    }

    widget->borderStyle = style;
    switch (style)
    {
    case GUI_BORDER_NONE:
        widget->border = 0;
        break;

    case GUI_BORDER_SIMPLE:
    case GUI_BORDER_UP:
    case GUI_BORDER_DOWN:
        widget->border = 1;
        break;

    case GUI_BORDER_STATIC:
    case GUI_BORDER_RAISE:
    case GUI_BORDER_SUNKEN:
    case GUI_BORDER_BOX:
    case GUI_BORDER_EXTRA:
        widget->border = 2;
        break;

    default:
        widget->border = 2;
        break;
    }
}

/**
 *******************************************************************************
 * @brief      set widget rectangle by a exist rectangle
 * @param[in]  widget       widget ptr	
 * @param[in]  rect         rectangle ptr	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set widget rectangle by a exist rectangle.
 *******************************************************************************
 */
void WidgetSetRect(P_GuiWidget widget, P_GuiRect rect)
{
    if(widget==Co_NULL || rect==Co_NULL){
        return;
    }

    /* update extent rectangle */
    widget->extent = *rect;
    /* set the visiable extern as extern */
    widget->extentVisiable = *rect;

    /* reset min width and height */
    widget->minWidth  = widget->extent.x2 - widget->extent.x1;
    widget->minHeight = widget->extent.y2 - widget->extent.y1;

    // update clip
}

/**
 *******************************************************************************
 * @brief      set widget rectangle by coordinates
 * @param[in]  widget       widget ptr	
 * @param[in]  x            x coordinate	
 * @param[in]  y            y coordinate
 * @param[in]  width        rectangle width	
 * @param[in]  height       rectangle height	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set widget rectangle by coordinates.
 *******************************************************************************
 */
void WidgetSetRectangle(P_GuiWidget widget, S32 x, S32 y, S32 width, S32 height)
{
    GuiRect rect;

    rect.x1 = x;
    rect.x2 = x + width;
    rect.y1 = y;
    rect.y2 = y + height;

    WidgetSetRect(widget, &rect);
}

/**
 *******************************************************************************
 * @brief      get widget extent
 * @param[in]  widget       widget ptr	
 * @param[in]  rect         where to put extent result	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to get widget extent.
 *******************************************************************************
 */
void WidgetGetExtent(P_GuiWidget widget, P_GuiRect rect)
{
    if(widget==Co_NULL || rect==Co_NULL){
        return;
    }

    *rect = widget->extent;
}

/**
 *******************************************************************************
 * @brief      set widget min-size
 * @param[in]  widget       widget ptr	
 * @param[in]  width        widget min-width	
 * @param[in]  height       widget min-height	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set widget min-size.
 *******************************************************************************
 */
void WidgetSetMinsize(P_GuiWidget widget, S32 width, S32 height)
{
    if(widget!=Co_NULL){
        widget->minWidth = width;
        widget->minHeight = height;
    }
}

/**
 *******************************************************************************
 * @brief      set widget min-width
 * @param[in]  widget       widget ptr	
 * @param[in]  width        widget min-width	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set widget min-width.
 *******************************************************************************
 */
void WidgetSetMinwidth(P_GuiWidget widget, S32 width)
{
    if(widget!=Co_NULL){
        widget->minWidth = width;
    }
}

/**
 *******************************************************************************
 * @brief      set widget min-height
 * @param[in]  widget       widget ptr	
 * @param[in]  height       widget min-height	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set widget min-height.
 *******************************************************************************
 */
void WidgetSetMinheight(P_GuiWidget widget, S32 height)
{
    if(widget!=Co_NULL){
        widget->minHeight = height;
    }
}

/**
 *******************************************************************************
 * @brief      let widget show
 * @param[in]  widget       widget ptr	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to let widget show.
 *******************************************************************************
 */
void WidgetShow(P_GuiWidget widget)
{
    struct GuiEvent event;

    if(widget==Co_NULL){
        return;
    }

    if(widget->flag&GUI_WIDGET_FLAG_SHOWN){
        return;
    }

    widget->flag |= GUI_WIDGET_FLAG_SHOWN;

    if(widget->topLevel != Co_NULL){
        // update clip

        GUI_EVENT_INIT(&event, GUI_EVENT_WIN_SHOW);
        if (widget->handler != Co_NULL){
            widget->handler(widget, &event);
        }
    }
}

/**
 *******************************************************************************
 * @brief      let widget hide
 * @param[in]  widget       widget ptr	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to let widget hide.
 *******************************************************************************
 */
void WidgetHide(P_GuiWidget widget)
{
    struct GuiEvent event;

    if(widget==Co_NULL){
        return;
    }

    if(!(widget->flag&GUI_WIDGET_FLAG_SHOWN)){
        return;
    }

    if(widget->topLevel != Co_NULL){
        GUI_EVENT_INIT(&event, GUI_EVENT_WIN_HIDE);
        if (widget->handler != Co_NULL){
            widget->handler(widget, &event);
        }
    }

    widget->flag &= ~GUI_WIDGET_FLAG_SHOWN;
}

/**
 *******************************************************************************
 * @brief      do something when widget show
 * @param[in]  widget       widget ptr	
 * @param[in]  event        event ptr
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to do something when widget show.
 *******************************************************************************
 */
StatusType WidgetOnshow(P_GuiWidget widget, struct GuiEvent *event)
{
    if(!(widget->flag&GUI_WIDGET_FLAG_SHOWN)){
        return Co_FALSE;
    }

    // clip

    return Co_FALSE;
}

/**
 *******************************************************************************
 * @brief      do something when widget hide
 * @param[in]  widget       widget ptr	
 * @param[in]  event        event ptr
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to do something when widget hide.
 *******************************************************************************
 */
StatusType WidgetOnhide(P_GuiWidget widget, struct GuiEvent *event)
{
     if(widget->flag&GUI_WIDGET_FLAG_SHOWN){
        return Co_FALSE;
    }

    // clip

    return Co_FALSE;
}

void WidgetUpdate(P_GuiWidget widget);

/**
 *******************************************************************************
 * @brief      widget's event handler
 * @param[in]  widget       widget ptr	
 * @param[in]  event        event ptr
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is widget's event handler.
 *******************************************************************************
 */
StatusType WidgetEventHandler(P_GuiWidget widget, struct GuiEvent *event)
{
    if(widget!=Co_NULL){
        return Co_FALSE;
    }    
}

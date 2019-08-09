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

const cogui_color_t guiDefaultForeground = 0xFFFF;
const cogui_color_t guiDefaultBackground = 0x0000;

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
void _WidgetInit(cogui_widget_t * widget)
{
	/* init gc */
	widget->gc.foreground = guiDefaultForeground;
	widget->gc.background = guiDefaultBackground;
	
    /* set parent and toplevel root */
    widget->parent   = Co_NULL;
    widget->topLevel = Co_NULL;

    widget->minWidth = widget->minHeight = 0;

    /* some common event handler */
    widget->onFocusIn  = Co_NULL;
    widget->onFocusOut = Co_NULL;

    /* set default event handler */
    widget->handler = WidgetEventHandler;

    /* init user data private to 0 */
    widget->userData = 0;
}

/**
 *******************************************************************************
 * @brief      create a widget	 
 * @param[in]  None		
 * @param[out] None
 * @retval     widget       widget		
 * @retval     Co_NULL      create failed 
 *
 * @par Description
 * @details    This function is called to create a widget.
 *******************************************************************************
 */
cogui_widget_t * WidgetCreate()
{
    cogui_widget_t * widget;

    widget = GuiMalloc(sizeof(cogui_widget_t));
    if(widget == Co_NULL)
	{
        return Co_NULL;
    }
    
    _WidgetInit(widget);

    return widget;
}

/**
 *******************************************************************************
 * @brief      delete a widget	 
 * @param[in]  widget       widget ptr		
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to delete a widget.
 *******************************************************************************
 */
void WidgetDel(cogui_widget_t * widget)
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
void WidgetSetFocus(cogui_widget_t * widget, EventHandlerPtr handler)
{
    if(widget != Co_NULL && handler != Co_NULL)
	{
        widget->onFocusIn = handler;
    }
}

/**
 *******************************************************************************
 * @brief      set widget unfocus handler
 * @param[in]  widget       widget ptr	
 * @param[in]  handler      handler ptr	
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set widget unfocus handler.
 *******************************************************************************
 */
void WidgetSetUnFocus(cogui_widget_t * widget, EventHandlerPtr handler)
{
    if(widget != Co_NULL && handler != Co_NULL)
	{
        widget->onFocusOut = handler;
    }
}


/**
 *******************************************************************************
 * @brief      let widget focus
 * @param[in]  widget       widget ptr	
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to let widget focus.
 *******************************************************************************
 */
void WidgetFocus(cogui_widget_t * widget)
{
    cogui_widget_t * oldFocus;

    if(widget == Co_NULL || widget->topLevel == Co_NULL)
	{
        return;
    }

    if(!(widget->flag&COGUI_WIDGET_FLAG_FOCUSABLE) || 
       (widget->flag&COGUI_WIDGET_FLAG_DISABLE))
	{
        return;
    }

    oldFocus = widget->topLevel->focusWidget;
    if(oldFocus==widget)
	{   /* it's the same focused widget */
        return;
    }

    /* unfocused the old widget */
    if(oldFocus != Co_NULL)
	{
        WidgetUnFocus(oldFocus);
	}

    /* set widget as focused */
    widget->flag |= COGUI_WIDGET_FLAG_FOCUS;
    widget->topLevel->focusWidget = widget;

    /* invoke on focus in call back */
    if(widget->onFocusIn != Co_NULL)
	{
        widget->onFocusIn(widget, Co_NULL);
	}
}


/**
 *******************************************************************************
 * @brief      let widget unfocus handler
 * @param[in]  widget       widget ptr	
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to let widget unfocus handler.
 *******************************************************************************
 */
void WidgetUnFocus(cogui_widget_t * widget)
{
    if(widget==Co_NULL)
	{
        return;
    }

    if(!widget->topLevel || !(widget->flag&COGUI_WIDGET_FLAG_FOCUS))
	{
        return;
    }

    widget->flag &= ~COGUI_WIDGET_FLAG_FOCUS;

    if(widget->onFocusOut != Co_NULL)
	{
        widget->onFocusOut(widget, Co_NULL);
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
void WidgetGetRect(cogui_widget_t * widget, P_GuiRect rect)
{
    if(widget == Co_NULL)
	{
        return;
    }

    if(rect != Co_NULL)
	{
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
void WidgetSetBorder(cogui_widget_t * widget, U32 style)
{
    if(widget == Co_NULL)
	{
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
void WidgetSetRect(cogui_widget_t * widget, P_GuiRect rect)
{
    if(widget == Co_NULL || rect == Co_NULL)
	{
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
void WidgetSetRectangle(cogui_widget_t * widget, S32 x, S32 y, S32 width, S32 height)
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
void WidgetGetExtent(cogui_widget_t * widget, P_GuiRect rect)
{
    if(widget == Co_NULL || rect == Co_NULL)
	{
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
void WidgetSetMinsize(cogui_widget_t * widget, S32 width, S32 height)
{
    if(widget != Co_NULL)
	{
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
void WidgetSetMinwidth(cogui_widget_t * widget, S32 width)
{
    if(widget != Co_NULL)
	{
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
void WidgetSetMinheight(cogui_widget_t * widget, S32 height)
{
    if(widget != Co_NULL)
	{
        widget->minHeight = height;
    }
}

/**
 *******************************************************************************
 * @brief      update a widget clip region
 * @param[in]  widget       widget ptr
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to update a widget clip region.
 *******************************************************************************
 */
void WidgetUpdateClip(cogui_widget_t * widget)
{
    //GuiRect rect;
    //P_CoList node;
    //cogui_widget_t * parent, child;

    /* no widget or widget is hide, no update clip */
    //if(widget == Co_NULL || !(widget->flag&COGUI_WIDGET_FLAG_SHOWN) || widget->parent == Co_NULL)
	//{
    //    return;
    //}

    //parent = widget->parent;
    /* reset visiable extent */
    //widget->extentVisiable = widget->extent;
    //RectIntersect(&(parent->extentVisiable), &(widget->extentVisiable));

    //rect = parent->extentVisiable;
    /* reset clip to extent */
    //RegionReset(&(widget->clip), &(widget->extent));
    /* limit widget extent in parent extent */
    //RegionIntersectRect(&(widget->clip), &(widget->clip), &rect);

    /* get the no transparent parent */
    //while(parent != Co_NULL && parent->flag & COGUI_WIDGET_FLAG_TRANSPARENT)
	//{
    //    parent = parent->parent;
    //}
    //if(parent != Co_NULL)
	//{
    //    /* give my clip back to parent */
    //    RegionUnion(&(parent->clip), &(parent->clip), &(widget->clip));

    //    /* subtract widget clip in parent clip */
    //    if(!(widget->flag & COGUI_WIDGET_FLAG_TRANSPARENT) && parent->flag & COGUI_WIDGET_FLAG_IS_CONTAINER)
	//	{
    //        RegionSubtractRect(&(parent->clip), &(parent->clip), &(widget->extentVisiable));
    //    }
    //}

    /* if it's a container object, update the clip info of children */
    //if(widget->flag & COGUI_WIDGET_FLAG_IS_CONTAINER)
	//{
    //    for(node=&((P_GuiContainer)widget)->children; node!=Co_NULL; node=node->next)
	//	{
    //        child = (cogui_widget_t *)(&((cogui_widget_t *)node)->sibling);

    //        WidgetUpdateClip(child);
    //    }   
    //}
}

/**
 *******************************************************************************
 * @brief      actually move a widget
 * @param[in]  widget       widget ptr	
 * @param[in]  dx           delta x	
 * @param[in]  dy           delta y	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to actually move a widget.
 *******************************************************************************
 */
void _WidgetMove(cogui_widget_t * widget, S32 dx, S32 dy)
{
//    P_CoList node; 
//    cogui_widget_t * child, parent;

    widget->extent.x1 += dx;
    widget->extent.x2 += dx;

    widget->extent.y1 += dy;
    widget->extent.y2 += dy;

    /* handle visiable extent */
    widget->extentVisiable = widget->extent;
//    parent = widget->parent;

    /* we should find out the none-transparent parent *
    while(parent != Co_NULL && parent->flag & COGUI_WIDGET_FLAG_TRANSPARENT)
	{
        parent = parent->parent;
    }

    if(widget->parent)
	{
        RectIntersect(&(widget->parent->extentVisiable), &(widget->extentVisiable));
    }*/

    /* reset clip info *
    RegionInitWithExtents(&(widget->clip), &(widget->extent));

    if(widget->flag & COGUI_WIDGET_FLAG_IS_CONTAINER)
	{
        for(node=&((P_GuiContainer)widget)->children; node!=Co_NULL; node=node->next)
		{
            child = (cogui_widget_t *)(&((cogui_widget_t *)node)->sibling);

            _WidgetMove(child, dx, dy);
        }   
    }*/
}

/**
 *******************************************************************************
 * @brief      move widget and its children to a logic point
 * @param[in]  widget       widget ptr	
 * @param[in]  dx           delta x	
 * @param[in]  dy           delta y	
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to move widget to a logic point.
 *******************************************************************************
 */
void WidgetMoveToLogic(cogui_widget_t * widget, S32 dx, S32 dy)
{
//    GuiRect rect;
    cogui_widget_t * parent;

    if(widget==Co_NULL)
	{
        return;
    }

    /* give clip of this widget back to parent */
    parent = widget->parent;
    if(parent!=Co_NULL)
    {
        /* get the parent rect, even if it's a transparent parent. */
        //rect = parent->extentVisiable;
    }

    /* we should find out the none-transparent parent *
    while(parent!=Co_NULL && parent->flag & COGUI_WIDGET_FLAG_TRANSPARENT)
	{
        parent = parent->parent;
    }*/

    /*if(parent != Co_NULL)
    {
        * reset clip info *
        RegionInitWithExtents(&(widget->clip), &(widget->extent));
        RegionIntersectRect(&(widget->clip), &(widget->clip), &rect);

        * give back the extent *
        RegionUnion(&(parent->clip), &(parent->clip), &(widget->clip));
    }

    _WidgetMove(widget, dx, dy);*/

    // update clip
}

/**
 *******************************************************************************
 * @brief      get the physical position of a logic point on widget
 * @param[in]  widget       widget ptr	
 * @param[in]  point        point ptr
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to get the physical position.
 *******************************************************************************
 */
void WidgetPointToDevice(cogui_widget_t * widget, P_GuiPoint point)
{
    if(widget == Co_NULL || point == Co_NULL)
	{
        return;
    }

    point->x += widget->extent.x1;
    point->y += widget->extent.y1;
}

/**
 *******************************************************************************
 * @brief      get the physical position of a logic rect on widget
 * @param[in]  widget       widget ptr	
 * @param[in]  rect         rect ptr
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to get the physical position.
 *******************************************************************************
 */
void WidgetRectToDevice(cogui_widget_t * widget, P_GuiRect rect)
{
    if(widget == Co_NULL || rect == Co_NULL)
	{
        return;
    }

    rect->x1 += widget->extent.x1;
    rect->x2 += widget->extent.x1;

    rect->y1 += widget->extent.y1;
    rect->y2 += widget->extent.y1;
}

/**
 *******************************************************************************
 * @brief      get the logic position of a physical point on widget
 * @param[in]  widget       widget ptr	
 * @param[in]  point        point ptr
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to get the logic position.
 *******************************************************************************
 */
void WidgetPointToLogic(cogui_widget_t * widget, P_GuiPoint point)
{
    if(widget == Co_NULL || point == Co_NULL)
	{
        return;
    }

    point->x -= widget->extent.x1;
    point->y -= widget->extent.y1;
}

/**
 *******************************************************************************
 * @brief      get the logic position of a physical rect on widget
 * @param[in]  widget       widget ptr	
 * @param[in]  rect         rect ptr
 * @param[out] none
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to get the logic position.
 *******************************************************************************
 */
void widgetRectToLogic(cogui_widget_t * widget, P_GuiRect rect)
{
    if(widget == Co_NULL || rect == Co_NULL)
	{
        return;
    }

    rect->x1 -= widget->extent.x1;
    rect->x2 -= widget->extent.x1;

    rect->y1 -= widget->extent.y1;
    rect->y2 -= widget->extent.y1;
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
void WidgetShow(cogui_widget_t * widget)
{
    struct GuiEvent event;

    if(widget == Co_NULL)
	{
        return;
    }

    if(widget->flag & COGUI_WIDGET_FLAG_SHOWN)
	{
        return;
    }

    widget->flag |= COGUI_WIDGET_FLAG_SHOWN;

    if(widget->topLevel != Co_NULL)
	{
        // update clip

        GUI_EVENT_INIT(&event, GUI_EVENT_WIN_SHOW, AppSelf());
        if(widget->handler != Co_NULL)
		{
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
void WidgetHide(cogui_widget_t * widget)
{
    struct GuiEvent event;

    if(widget == Co_NULL)
	{
        return;
    }

    if(!(widget->flag & COGUI_WIDGET_FLAG_SHOWN))
	{
        return;
    }

    if(widget->topLevel != Co_NULL)
	{
        GUI_EVENT_INIT(&event, GUI_EVENT_WIN_HIDE, AppSelf());
        if (widget->handler != Co_NULL)
		{
            widget->handler(widget, &event);
        }
    }

    widget->flag &= ~COGUI_WIDGET_FLAG_SHOWN;
}

/**
 *******************************************************************************
 * @brief      do something when widget show
 * @param[in]  widget       widget ptr	
 * @param[in]  event        event ptr
 * @param[out] none
 * @retval     Co_FALSE     failed		 
 *
 * @par Description
 * @details    This function is called to do something when widget show.
 *******************************************************************************
 */
StatusType WidgetOnshow(cogui_widget_t * widget, struct GuiEvent *event)
{
    if(!(widget->flag & COGUI_WIDGET_FLAG_SHOWN))
	{
        return Co_FALSE;
    }

    if(widget->parent!=Co_NULL && !(widget->flag & COGUI_WIDGET_FLAG_TRANSPARENT))
	{
        WidgetClipParent(widget);
    }

    return Co_FALSE;
}

/**
 *******************************************************************************
 * @brief      do something when widget hide
 * @param[in]  widget       widget ptr	
 * @param[in]  event        event ptr
 * @param[out] none
 * @retval     Co_FALSE     failed		 
 *
 * @par Description
 * @details    This function is called to do something when widget hide.
 *******************************************************************************
 */
StatusType WidgetOnhide(cogui_widget_t * widget, struct GuiEvent *event)
{
    if(widget->flag & COGUI_WIDGET_FLAG_SHOWN)
	{
        return Co_FALSE;
    }

    if (widget->parent != Co_NULL)
    {
        WidgetClipReturn(widget);
    }

    return Co_FALSE;
}

/**
 *******************************************************************************
 * @brief      get the clip with parent
 * @param[in]  widget       widget ptr
 * @param[out] None
 * @retval     None 
 *
 * @par Description
 * @details    This function is call to get the clip with parent.
 *******************************************************************************
 */
void WidgetClipParent(cogui_widget_t * widget)
{
//    cogui_widget_t * parent;

//    parent = widget->parent;
    /* get the no transparent parent *
    while(parent!=Co_NULL && parent->flag & COGUI_WIDGET_FLAG_TRANSPARENT)
	{
        parent = parent->parent;
    }

    * clip the widget extern from parent *
    if(parent != Co_NULL)
	{
        RegionSubtract(&(parent->clip), &(parent->clip), &(widget->clip));
    }*/
}

/**
 *******************************************************************************
 * @brief      get the clip with parent
 * @param[in]  widget       widget ptr
 * @param[out] None
 * @retval     None	 
 *
 * @par Description
 * @details    This function is call to get the clip with parent.
 *******************************************************************************
 */
void WidgetClipReturn(cogui_widget_t * widget)
{
//    cogui_widget_t * parent;

//    parent = widget->parent;
    /* get the no transparent parent *
    while(parent != Co_NULL && parent->flag & COGUI_WIDGET_FLAG_TRANSPARENT)
	{
        parent = parent->parent;
    }

    * give clip back to parent *
    if(parent != Co_NULL)
	{
        RegionUnion(&(parent->clip), &(parent->clip), &(widget->clip));
    }*/
}

void WidgetUpdate(cogui_widget_t * widget);

/**
 *******************************************************************************
 * @brief      widget's event handler
 * @param[in]  widget       widget ptr	
 * @param[in]  event        event ptr
 * @param[out] None
 * @retval     Co_FALSE     failed		 
 *
 * @par Description
 * @details    This function is widget's event handler.
 *******************************************************************************
 */
StatusType WidgetEventHandler(cogui_widget_t * widget, struct GuiEvent *event)
{
    if(widget != Co_NULL)
	{
        return Co_FALSE;
    }
	
	return Co_FALSE;
}

/**
 *******************************************************************************
 * @brief      get next sibling widget
 * @param[in]  widget       widget ptr
 * @param[out] None
 * @retval     sibling      next sibling widget		 
 *
 * @par Description
 * @details    This function is call to get next sibling widget.
 *******************************************************************************
 */
cogui_widget_t * WidgetGetNextSibling(cogui_widget_t * widget)
{
    cogui_widget_t * sibling;

    if(widget->sibling.next != Co_NULL)
	{
        sibling = (cogui_widget_t *)&widget->sibling.next;
    }

    return sibling;
}

/**
 *******************************************************************************
 * @brief      get prev sibling widget
 * @param[in]  widget       widget ptr
 * @param[out] None
 * @retval     sibling      prev sibling widget		 
 *
 * @par Description
 * @details    This function is call to get prev sibling widget.
 *******************************************************************************
 */
cogui_widget_t * WidgetGetPrevSibling(cogui_widget_t * widget)
{
    cogui_widget_t * sibling;

    if(widget->sibling.prev != Co_NULL)
	{
        sibling = (cogui_widget_t *)&widget->sibling.prev;
    }

    return sibling;
}

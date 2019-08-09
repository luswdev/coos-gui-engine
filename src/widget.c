/**
 *******************************************************************************
 * @file       widget.c
 * @version    V0.0.2  
 * @date       2019.8.9
 * @brief      Some widget function for GUI engine's event.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"

const cogui_color_t default_foreground = 0xFFFF;
const cogui_color_t default_background = 0x0000;

void _cogui_widget_init(cogui_widget_t *widget)
{
	widget->gc.foreground = default_foreground;
	widget->gc.background = default_background;
	
    widget->parent   = Co_NULL;
    widget->top_level = Co_NULL;

    widget->min_width = widget->min_height = 0;

    widget->on_focus_in  = Co_NULL;
    widget->on_focus_out = Co_NULL;

    widget->handler = cogui_widget_event_handler;

    widget->user_data = 0;
}

cogui_widget_t *cogui_widget_create(void)
{
    cogui_widget_t *widget;

    widget = cogui_malloc(sizeof(cogui_widget_t));
    if (widget == Co_NULL)
        return Co_NULL;
    
    _cogui_widget_init(widget);

    return widget;
}

void cogui_widget_delete(cogui_widget_t *widget)
{   
    GuiFree(widget);
}

void WidgetSetFocus(cogui_widget_t *widget, event_handler_ptr handler)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->on_focus_in = handler;
}

void WidgetSetUnFocus(cogui_widget_t *widget, event_handler_ptr handler)
{
    COGUI_ASSERT(widget != Co_NULL);
    
    widget->on_focus_out = handler;
}

void WidgetFocus(cogui_widget_t *widget)
{
    cogui_widget_t *old_focus;

    COGUI_ASSERT(widget != Co_NULL);
    COGUI_ASSERT(widget->topLevel != Co_NULL);

    if (!(widget->flag & COGUI_WIDGET_FLAG_FOCUSABLE) || 
       (widget->flag & COGUI_WIDGET_FLAG_DISABLE))
        return;

    old_focus = widget->top_level->focusWidget;
    if (old_focus == widget)
	    return;

    if (old_focus != Co_NULL)
        cogui_widget_unfocus(old_focus);

    widget->flag |= COGUI_WIDGET_FLAG_FOCUS;
    widget->top_level->focus_widget = widget;

    if (widget->on_focus_in != Co_NULL)
        widget->on_focus_in(widget, Co_NULL);
}

void cogui_widget_unfocus(cogui_widget_t *widget)
{
    COGUI_ASSERT(widget != Co_NULL);

    if (!widget->top_level || !(widget->flag & COGUI_WIDGET_FLAG_FOCUS))
	    return;

    widget->flag &= ~COGUI_WIDGET_FLAG_FOCUS;

    if (widget->on_focus_out != Co_NULL)
        widget->on_focus_out(widget, Co_NULL);

    widget->top_level->focus_widget = Co_NULL;
}

void cogui_widget_get_rect(cogui_widget_t *widget, cogui_rect_t *rect)
{
    COGUI_ASSERT(widget != Co_NULL);

    if (rect != Co_NULL) {
        rect->x1 = rect->y1 = 0;
        rect->x2 = widget->extent.x2 - widget->extent.x1;
        rect->y2 = widget->extent.y2 - widget->extent.y1;
    }
}

void cogui_widget_set_border(cogui_widget_t *widget, U32 style)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->border_style = style;
    switch (style) {
    case COGUI_BORDER_NONE:
        widget->border = 0;
        break;

    case COGUI_BORDER_SIMPLE:
    case COGUI_BORDER_UP:
    case COGUI_BORDER_DOWN:
        widget->border = 1;
        break;

    case COGUI_BORDER_STATIC:
    case COGUI_BORDER_RAISE:
    case COGUI_BORDER_SUNKEN:
    case COGUI_BORDER_BOX:
    case COGUI_BORDER_EXTRA:
        widget->border = 2;
        break;

    default:
        widget->border = 2;
        break;
    }
}

void cogui_widget_set_rect(cogui_widget_t *widget, cogui_rect_t *rect)
{
    if (widget == Co_NULL || rect == Co_NULL)
	    return;

    widget->extent = *rect;

    widget->extent_visiable = *rect;

    widget->min_width  = widget->extent.x2 - widget->extent.x1;
    widget->min_height = widget->extent.y2 - widget->extent.y1;

    // update clip
}

void cogui_widget_set_rectangle(cogui_widget_t *widget, S32 x, S32 y, S32 width, S32 height)
{
    cogui_rect_t rect;

    rect.x1 = x;
    rect.x2 = x + width;
    rect.y1 = y;
    rect.y2 = y + height;

    cogui_widget_set_rect(widget, &rect);
}

void cogui_widget_get_extent(cogui_widget_t *widget, cogui_rect_t *rect)
{
    COGUI_ASSERT(widget != Co_NULL);
    COGUI_ASSERT(rect != Co_NULL);

    *rect = widget->extent;
}

void cogui_widget_set_minsize(cogui_widget_t *widget, S32 width, S32 height)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->min_width = width;
    widget->min_height = height;
}

void cogui_widget_set_minwidth(cogui_widget_t *widget, S32 width)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->min_width = width;
}

void cogui_widget_set_mingheight(cogui_widget_t *widget, S32 height)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->min_height = height;
}

void cogui_widget_update_clip(cogui_widget_t *widget)
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

void _cogui_widget_move(cogui_widget_t *widget, S32 dx, S32 dy)
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

void cogui_widget_move_to_logic(cogui_widget_t *widget, S32 dx, S32 dy)
{
    //GuiRect rect;
    cogui_widget_t *parent;

    if (widget == Co_NULL)
        return;

    /* give clip of this widget back to parent */
    parent = widget->parent;
    if (parent != Co_NULL) {
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

void cogui_widget_point_to_device(cogui_widget_t *widget, cogui_point_t *point)
{
    COGUI_ASSERT(widget != Co_NULL);

    if (point != Co_NULL) {
        point->x += widget->extent.x1;
        point->y += widget->extent.y1;
    }
}

void cogui_widget_rect_to_device(cogui_widget_t *widget, cogui_rect_t *rect)
{
    COGUI_ASSERT(widget != Co_NULL);

    if (rect != Co_NULL) {
        rect->x1 += widget->extent.x1;
        rect->x2 += widget->extent.x1;

        rect->y1 += widget->extent.y1;
        rect->y2 += widget->extent.y1;
    }
}

void cogui_widget_point_to_logic(cogui_widget_t *widget, cogui_point_t *point)
{
    COGUI_ASSERT(widget != Co_NULL);

    if (point != Co_NULL) {
        point->x -= widget->extent.x1;
        point->y -= widget->extent.y1;
    }    
}

void cogui_widget_rect_to_logic(cogui_widget_t *widget, cogui_rect_t *rect)
{
    COGUI_ASSERT(widget != Co_NULL);
    
    if (rect != Co_NULL) {
        rect->x1 -= widget->extent.x1;
        rect->x2 -= widget->extent.x1;

        rect->y1 -= widget->extent.y1;
        rect->y2 -= widget->extent.y1;
    }
}

void cogui_widget_show(cogui_widget_t *widget)
{
    struct cogui_event event;
    COGUI_ASSERT(widget != Co_NULL);

    if (widget->flag & COGUI_WIDGET_FLAG_SHOWN)
        return;

    widget->flag |= COGUI_WIDGET_FLAG_SHOWN;

    if (widget->topLevel != Co_NULL) {
        // update clip

        COGUI_EVENT_INIT(&event, COGUI_EVENT_WIN_SHOW,);

        if (widget->handler != Co_NULL)
            widget->handler(widget, &event);
    }
}

void cogui_widget_hide(cogui_widget_t *widget)
{
    struct cogui_event event;
    COGUI_ASSERT(widget != Co_NULL);

    if (!(widget->flag & COGUI_WIDGET_FLAG_SHOWN))
        return;

    if (widget->top_level != Co_NULL) {
        COGUI_EVENT_INIT(&event, COGUI_EVENT_WIN_HIDE);

        if (widget->handler != Co_NULL)
            widget->handler(widget, &event);
    }

    widget->flag &= ~COGUI_WIDGET_FLAG_SHOWN;
}

StatusType cogui_widget_onshow(cogui_widget_t *widget, struct cogui_event *event)
{
    if (!(widget->flag & COGUI_WIDGET_FLAG_SHOWN))
        return Co_FALSE;
    

    if (widget->parent!=Co_NULL && !(widget->flag & COGUI_WIDGET_FLAG_TRANSPARENT)) {
        cogui_widget_clip_parent(widget);
    }

    return Co_FALSE;
}

StatusType cogui_widget_onhide(cogui_widget_t *widget, struct cogui_event *event)
{
    if (widget->flag & COGUI_WIDGET_FLAG_SHOWN)
        return Co_FALSE;

    if (widget->parent != Co_NULL) {
        cogui_widget_clip_return(widget);
    }

    return Co_FALSE;
}

void cogui_widget_clip_parent(cogui_widget_t *widget)
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

void cogui_widget_clip_return(cogui_widget_t *widget)
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

void cogui_widget_update(cogui_widget_t *widget);

StatusType cogui_widget_event_handler(cogui_widget_t *widget, struct cogui_event *event)
{
    COGUI_ASSERT(widget != Co_NULL);
    COGUI_ASSERT(event != Co_NULL);

	return Co_FALSE;
}

cogui_widget_t *cogui_widget_get_next_sibling(cogui_widget_t *widget)
{
    cogui_widget_t *sibling;

    if (widget->sibling.next != Co_NULL) {
        sibling = (cogui_widget_t *)&widget->sibling.next;
    }

    return sibling;
}

cogui_widget_t *cogui_widget_get_prev_sibling(cogui_widget_t *widget)
{
    cogui_widget_t * sibling;

    if (widget->sibling.prev != Co_NULL) {
        sibling = (cogui_widget_t *)&widget->sibling.prev;
    }

    return sibling;
}

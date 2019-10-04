/**
 *******************************************************************************
 * @file       widget.c
 * @version    V0.1.0  
 * @date       2019.9.29
 * @brief      Some widget function for GUI engine's event.	
 *******************************************************************************
 */ 

#include <cogui.h>

extern const cogui_color_t default_foreground;
extern const cogui_color_t default_background;

static void _cogui_widget_init(cogui_widget_t *widget)
{
    /* set default fore/background */
	widget->gc.foreground = default_foreground;
	widget->gc.background = default_background;
	
    /* initial parent and top level */
    widget->parent   = Co_NULL;
    widget->top_level = Co_NULL;

    /* set size equal to 0 */
    widget->min_width = widget->min_height = 0;

    widget->on_focus_in  = Co_NULL;
    widget->on_focus_out = Co_NULL;

    widget->handler = cogui_widget_event_handler;

    widget->flag = COGUI_WIDGET_FLAG_INIT;
    widget->type = COGUI_WIDGET_TYPE_INIT;

    widget->user_data = 0;
}

cogui_widget_t *cogui_widget_create(void)
{
    cogui_widget_t *widget;

    widget = cogui_malloc(sizeof(cogui_widget_t));
    if (widget == Co_NULL)
        return Co_NULL;
    
    _cogui_widget_init(widget);

    widget->type = COGUI_WIDGET_TYPE_WIDGET;

    return widget;
}

void cogui_widget_delete(cogui_widget_t *widget)
{   
    cogui_free(widget);
}

void cogui_widget_set_focus(cogui_widget_t *widget, event_handler_ptr handler)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->on_focus_in = handler;
}

void cogui_widget_set_unfocus(cogui_widget_t *widget, event_handler_ptr handler)
{
    COGUI_ASSERT(widget != Co_NULL);
    
    widget->on_focus_out = handler;
}

void cogui_widget_focus(cogui_widget_t *widget)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->flag |= COGUI_WIDGET_FLAG_FOCUS;

    cogui_screen_t *my_node = cogui_get_screen_node(widget->screen_node_id);

    COGUI_ASSERT(my_node != Co_NULL);

    /* put this node into last of the list */
    cogui_screen_list_pop(widget->screen_node_id);
    cogui_screen_list_insert(my_node);
}

void cogui_widget_unfocus(cogui_widget_t *widget)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->flag &= ~COGUI_WIDGET_FLAG_FOCUS;

    cogui_screen_t *my_node = cogui_get_screen_node(widget->screen_node_id);
    cogui_screen_t *new_focus = (cogui_screen_t *)COGUI_GET_LIST_PREV(my_node);

    COGUI_ASSERT(my_node != Co_NULL);
    COGUI_ASSERT(new_focus != Co_NULL);

    /* let new focus node insert into the list of the last */
    cogui_screen_list_pop(new_focus->node_id);
    cogui_screen_list_insert(new_focus);
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

void cogui_widget_get_extent(cogui_widget_t *widget, cogui_rect_t *rect)
{
    COGUI_ASSERT(widget != Co_NULL);
    COGUI_ASSERT(rect != Co_NULL);

    *rect = widget->extent;
}

static void cogui_widget_set_rect(cogui_widget_t *widget, cogui_rect_t *rect)
{
    if (widget == Co_NULL || rect == Co_NULL)
	    return;

    widget->extent = *rect;

    widget->min_width  = widget->extent.x2 - widget->extent.x1;
    widget->min_height = widget->extent.y2 - widget->extent.y1;
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

static void _cogui_widget_move(cogui_widget_t *widget, S32 dx, S32 dy)
{
    widget->extent.x1 += dx;
    widget->extent.x2 += dx;

    widget->extent.y1 += dy;
    widget->extent.y2 += dy;

	cogui_screen_refresh();
}

void cogui_widget_move_to_logic(cogui_widget_t *widget, S32 dx, S32 dy)
{
    if (widget == Co_NULL)
        return;
	
	_cogui_widget_move(widget, dx, dy);
}

void cogui_widget_point_l2p(cogui_widget_t *widget, cogui_point_t *point)
{
    COGUI_ASSERT(widget != Co_NULL);

    if (point != Co_NULL) {
        point->x += widget->extent.x1;
        point->y += widget->extent.y1;
    }
}

void cogui_widget_rect_l2p(cogui_widget_t *widget, cogui_rect_t *rect)
{
    COGUI_ASSERT(widget != Co_NULL);

    if (rect != Co_NULL) {
        rect->x1 += widget->extent.x1;
        rect->x2 += widget->extent.x1;

        rect->y1 += widget->extent.y1;
        rect->y2 += widget->extent.y1;
    }
}

void cogui_widget_point_p2l(cogui_widget_t *widget, cogui_point_t *point)
{
    COGUI_ASSERT(widget != Co_NULL);

    if (point != Co_NULL) {
        point->x -= widget->extent.x1;
        point->y -= widget->extent.y1;
    }    
}

void cogui_widget_rect_p2l(cogui_widget_t *widget, cogui_rect_t *rect)
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

    COGUI_EVENT_INIT(&event, COGUI_EVENT_WIDGET_SHOW);

    if (widget->handler != Co_NULL)
        widget->handler(widget, &event);
}

void cogui_widget_hide(cogui_widget_t *widget)
{
    struct cogui_event event;
    COGUI_ASSERT(widget != Co_NULL);

    if (!(widget->flag & COGUI_WIDGET_FLAG_SHOWN))
        return;

    widget->flag &= ~COGUI_WIDGET_FLAG_SHOWN;

    COGUI_EVENT_INIT(&event, COGUI_EVENT_WIDGET_HIDE);

    if (widget->handler != Co_NULL)
        widget->handler(widget, &event);
}

StatusType cogui_widget_onshow(cogui_widget_t *widget, struct cogui_event *event)
{
    if (!(widget->flag & COGUI_WIDGET_FLAG_SHOWN))
        return Co_FALSE;
        
    cogui_screen_t *my_node = cogui_get_screen_node(widget->screen_node_id);
    COGUI_ENABLE_SCREEN_NODE(my_node);
    cogui_widget_focus(widget);
    

    /*if (widget->parent!=Co_NULL && !(widget->flag & COGUI_WIDGET_FLAG_TRANSPARENT)) {
        cogui_widget_clip_parent(widget);
    }*/

    return Co_FALSE;
}

StatusType cogui_widget_onhide(cogui_widget_t *widget, struct cogui_event *event)
{
    if (widget->flag & COGUI_WIDGET_FLAG_SHOWN)
        return Co_FALSE;

    cogui_screen_t *my_node = cogui_get_screen_node(widget->screen_node_id);
    COGUI_DISABLE_SCREEN_NODE(my_node);
    cogui_screen_refresh();

    /*if (widget->parent != Co_NULL) {
        cogui_widget_clip_return(widget);
    }*/

    return Co_FALSE;
}

void cogui_widget_update(cogui_widget_t *widget);

StatusType cogui_widget_event_handler(cogui_widget_t *widget, struct cogui_event *event)
{
    COGUI_ASSERT(widget != Co_NULL);
    COGUI_ASSERT(event != Co_NULL);

    switch (event->type)
    {
    case COGUI_EVENT_WIDGET_SHOW:
        cogui_widget_onshow(widget, event);
        break;

     case COGUI_EVENT_WIDGET_HIDE:
        cogui_widget_onhide(widget, event);
        break;
    }

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

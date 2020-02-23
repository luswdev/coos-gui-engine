/**
 *******************************************************************************
 * @file       widget.c
 * @version    V0.7.0
 * @date       2020.02.22
 * @brief      Some widget function for GUI engine's event.	
 *******************************************************************************
 */ 

#include <cogui.h>

extern const cogui_color_t default_foreground;
extern const cogui_color_t default_background;

extern cogui_font_t *default_font; 

extern struct cogui_window *main_page;

StatusType cogui_widget_event_handler(cogui_widget_t *widget, struct cogui_event *event);

static void _cogui_widget_init(cogui_widget_t *widget)
{
    cogui_memset(widget, 0, sizeof(cogui_widget_t));

    /* init flag and type */
    widget->flag = COGUI_WIDGET_FLAG_INIT | COGUI_WIDGET_TYPE_INIT;

    /* set default fore/background */
	widget->gc.foreground = default_foreground;
	widget->gc.background = default_background;
    widget->gc.font       = default_font;

    /* initial extent rectangle */
    COGUI_INIT_RECR(&widget->extent);

    /* set event handler */
    widget->handler = cogui_widget_event_handler;
}

cogui_widget_t *cogui_widget_create(struct cogui_window *top)
{
    cogui_widget_t *widget;

    COGUI_ASSERT(top != Co_NULL);

    widget = cogui_malloc(sizeof(cogui_widget_t));
    if (widget == Co_NULL) {
        return Co_NULL;
    }
    
    /* first initial structure data */
    _cogui_widget_init(widget);

    /* set type to widget */
    widget->flag &= ~COGUI_WIDGET_TYPE_MASK;
    widget->flag |= COGUI_WIDGET_TYPE_WIDGET;

    /* create a dc engine */
    widget->dc_engine = cogui_dc_begin_drawing(widget);
    COGUI_ASSERT(widget->dc_engine != Co_NULL);

    widget->top = top;
    widget->id  = top->widget_cnt++;

    cogui_widget_list_insert(widget);

    top->focus_widget = widget;
    return widget;
}

void cogui_widget_delete(cogui_widget_t *widget)
{
    cogui_widget_list_pop(widget->id, widget->top);
    cogui_dc_end_drawing(widget->dc_engine);
    cogui_widget_clear_text(widget);

    if (widget->user_data) {
        cogui_free(widget->user_data);
    }

    cogui_free(widget);
}

/**
 *******************************************************************************
 * @brief      Initial screen list   
 * @param[in]  None
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is used to initial a screen list to a header node
 *             and a full screen widget, and refresh screen currently.    
 *******************************************************************************
 */
cogui_widget_t *cogui_widget_list_init(struct cogui_window *top)
{	
    /* create header node */
	cogui_widget_t *header = cogui_widget_create(top);
    COGUI_ASSERT(header != Co_NULL);
    header->flag |= COGUI_WIDGET_FLAG_HEADER;
    
    /* first object should be a fill screen */
    cogui_widget_t *widget = cogui_widget_create(top);
    COGUI_ASSERT(widget != Co_NULL);	

    /* enabled it */
    widget->flag |= COGUI_WIDGET_FLAG_SHOWN;

    /* set as a full screen rectangle */
    widget->flag |= COGUI_WIDGET_FLAG_RECT | COGUI_WIDGET_FLAG_HEADER;
    cogui_widget_set_rectangle(widget, 0, 0, COGUI_SCREEN_WIDTH, COGUI_SCREEN_HEIGHT);

    /* this node should be filled by background */
    widget->gc.foreground = default_background;
    widget->flag |= COGUI_WIDGET_FLAG_FILLED;

	return widget;
}

/**
 *******************************************************************************
 * @brief      Insert a screen node into screen list
 * @param[in]  *node    Which node we should insert
 * @param[out] None
 * @retval     None 
 *
 * @par Description
 * @details    This function is used to insert a screen node into screen list
 *             and refresh screen currently.
 *******************************************************************************
 */
void cogui_widget_list_insert(cogui_widget_t *node)
{  
    COGUI_ASSERT(node != Co_NULL);

    struct cogui_window *top = node->top;
    COGUI_ASSERT(top != Co_NULL);

    /* if it is header node */
    if (top->widget_list == Co_NULL) {
        top->widget_list = node;
        node->next = Co_NULL;
        return;
    }

    cogui_widget_t *list = top->widget_list;

    while (list->next != Co_NULL)
        list = list->next;

    list->next = node;
    node->next = Co_NULL;
    
    /* after inserted, refresh screen */
    //cogui_screen_refresh(top);
}

/**
 *******************************************************************************
 * @brief      Pop out a screen node from screen list
 * @param[in]  id       Which node we should pop
 * @param[out] None
 * @retval     None 
 *
 * @par Description
 * @details    This function is used to pop out a screen node from screen list
 *             and not delete it right now. 
 *******************************************************************************
 */
cogui_widget_t *cogui_widget_list_pop(co_uint32_t id, struct cogui_window *top)
{
    cogui_widget_t *list = top->widget_list->next;

    /* recursive from first node */
    while (list->next != Co_NULL) {
        if (list->next->id == id) {
            cogui_widget_t *tmp_widget = list->next;
            
            list->next = tmp_widget->next;

            tmp_widget->next = Co_NULL;
            
			/* after pop function, refresh screen */
			cogui_screen_refresh(top);
			
            return tmp_widget;
        }

        /* or move to next one */
        list = list->next;
    }

    return Co_NULL;
}

/**
 *******************************************************************************
 * @brief      Find a node from id
 * @param[in]  id           Which node we want to find
 * @param[out] None
 * @retval     screen_node  The result we found
 * @retval     Co_NULL      Or we did not find it
 *******************************************************************************
 */
cogui_widget_t *cogui_get_widget_node(co_uint32_t id, struct cogui_window *top)
{
    cogui_widget_t *list = top->widget_list->next;

    /* recursive from first node */
    while (list != Co_NULL) {
        /* find the corrent one, return it */
        if (list->id == id) {
            return list;
        }

        /* or move to next one */
        list = list->next;
    }

    return Co_NULL;
}

/**
 *******************************************************************************
 * @brief      Refresh screen by list
 * @param[in]  None
 * @param[out] None
 * @retval     None
 *
 * @par Description
 * @details    This function is called to refresh screen by list.
 *******************************************************************************
 */
StatusType cogui_screen_refresh(struct cogui_window *top)
{
    COGUI_ASSERT(top != Co_NULL);

    if (!COGUI_WINDOW_IS_ENABLE(top) && top != main_page) {
        top = main_page;
    }

    if (!COGUI_WINDOW_IS_ENABLE(top) && top == main_page) {
        return GUI_E_ERROR;
    }

    cogui_widget_t *list = top->widget_list->next;

    while (list != Co_NULL) {
        /* if this node is disabled, skip it */
        if (!COGUI_WIDGET_IS_ENABLE(list)){
            list = list->next;
            continue;
        }

        /* draw shape if needed */
        if (list->flag & COGUI_WIDGET_FLAG_RECT) {
            if (list->flag & COGUI_WIDGET_FLAG_FILLED) {
                list->dc_engine->engine->fill_rect(list->dc_engine, &list->inner_extent);
			}
            else {
                cogui_dc_draw_rect(list->dc_engine, &list->inner_extent);
            }
        }
        
        /* draw text if needed */
        if (list->flag & COGUI_WIDGET_FLAG_HAS_TEXT) {
            cogui_rect_t pr = list->inner_extent;
            co_uint64_t padding = list->gc.padding;
            COGUI_RECT_PADDING(&pr, padding);

            cogui_dc_draw_text(list->dc_engine, &pr, list->text);
        }

        /* draw border at last if needed */
        if (list->flag & COGUI_WIDGET_BORDER) {
            cogui_dc_draw_border(list->dc_engine, &list->inner_extent);
        }        

        /* go forward to next node */
        list = list->next;
    }

    return GUI_E_OK;
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

    if (widget->top->focus_widget == widget) {
        cogui_screen_refresh(widget->top);
        return;
    }
    else {
        widget->top->focus_widget = widget;
    }

    /* put this node into last of the list */
    cogui_widget_list_pop(widget->id, widget->top);
    cogui_widget_list_insert(widget);
    cogui_screen_refresh(widget->top);
}

void cogui_widget_unfocus(cogui_widget_t *widget)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->flag &= ~COGUI_WIDGET_FLAG_FOCUS;

    cogui_widget_t *list = widget->top->widget_list;
	
    while(list->next != widget)
        list = list->next; /* it will stop at new focus widget */

    /* let new focus node insert into the list of the last */
    cogui_widget_list_pop(list->id, widget->top);
    cogui_widget_list_insert(list);
    cogui_screen_refresh(widget->top);

    widget->top->focus_widget = list;
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
    if (!(widget->top->style & COGUI_WINDOW_STYLE_NO_TITLE) && !(widget->flag & COGUI_WIDGET_FLAG_TITLE) && !(widget->flag & COGUI_WIDGET_FLAG_HEADER) ) {
        if (y <= COGUI_WINTITLE_HEIGHT)
            y = COGUI_WINTITLE_HEIGHT+1;
    }

    cogui_rect_t rect;

    COGUI_SET_RECT(&rect, x, y, width, height);
    cogui_widget_set_rect(widget, &rect);

    COGUI_SET_RECT(&widget->inner_extent, 0, 0, width, height);
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

void cogui_widget_enable_border(cogui_widget_t *widget)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->flag |= COGUI_WIDGET_BORDER;

    cogui_screen_refresh(widget->top);
}

void cogui_widget_set_font(cogui_widget_t* widget, cogui_font_t *font)
{
    COGUI_ASSERT(widget != Co_NULL);
    COGUI_ASSERT(font != Co_NULL);

    widget->gc.font = font;
}

void cogui_widget_set_text_align(cogui_widget_t *widget, co_uint16_t style)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->gc.text_align = style;
}

void cogui_widget_set_text(cogui_widget_t *widget, const char *text)
{
    COGUI_ASSERT(widget != Co_NULL);

    widget->flag |= COGUI_WIDGET_FLAG_HAS_TEXT;
    
    widget->text = cogui_strdup(text);
}

void cogui_widget_append_text(cogui_widget_t *widget, const char *text)
{
    COGUI_ASSERT(widget != Co_NULL);
    
    /* if this is first text, just call set_text to do finish work */
    if (!(widget->flag & COGUI_WIDGET_FLAG_HAS_TEXT)) {
        cogui_widget_set_text(widget, text);
        return;
    }
    
    co_uint64_t len = cogui_strlen(text) + cogui_strlen(widget->text) + 1;
    char * new_text = (char *)cogui_malloc(len);

    /* create new string and put 'text' on original text's end */
    cogui_memcpy(new_text, widget->text, cogui_strlen(widget->text));
    cogui_memcpy(new_text+cogui_strlen(widget->text), text, cogui_strlen(text)+1);

    /* after copy original text, free it */
    cogui_free(widget->text);

    widget->text = new_text;
}

void cogui_widget_clear_text(cogui_widget_t *widget)
{
    widget->flag &= ~COGUI_WIDGET_FLAG_HAS_TEXT;

    /* free text pointer if needed */
    if (widget->text) {
        cogui_free(widget->text);
    }
}

static void _cogui_widget_move(cogui_widget_t *widget, S32 dx, S32 dy)
{
    widget->extent.x1 += dx;
    widget->extent.x2 += dx;

    widget->extent.y1 += dy;
    widget->extent.y2 += dy;

	cogui_screen_refresh(widget->top);
}

void cogui_widget_move_to_logic(cogui_widget_t *widget, S32 dx, S32 dy)
{
    if (widget == Co_NULL) {
        return;
    }
	
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

StatusType cogui_widget_show(cogui_widget_t *widget)
{
    struct cogui_event event;
    COGUI_ASSERT(widget != Co_NULL);

    StatusType result;

    if (widget->flag & COGUI_WIDGET_FLAG_SHOWN)
        return GUI_E_ERROR;

    widget->flag |= COGUI_WIDGET_FLAG_SHOWN;

    COGUI_EVENT_INIT(&event, COGUI_EVENT_WIDGET_SHOW);

    if (widget->handler != Co_NULL)
        result = widget->handler(widget, &event);

    return result;
}

StatusType cogui_widget_hide(cogui_widget_t *widget)
{
    struct cogui_event event;
    COGUI_ASSERT(widget != Co_NULL);

    StatusType result;

    if (!(widget->flag & COGUI_WIDGET_FLAG_SHOWN))
        return GUI_E_ERROR;
    
    widget->flag &= ~COGUI_WIDGET_FLAG_SHOWN;

    COGUI_EVENT_INIT(&event, COGUI_EVENT_WIDGET_HIDE);
    
    if (widget->handler != Co_NULL)
        result = widget->handler(widget, &event);

    return result;
}

StatusType cogui_widget_onshow(cogui_widget_t *widget, struct cogui_event *event)
{
    if (!(widget->flag & COGUI_WIDGET_FLAG_SHOWN))
        return GUI_E_ERROR;

    cogui_widget_focus(widget);

    return GUI_E_OK;
}

StatusType cogui_widget_onhide(cogui_widget_t *widget, struct cogui_event *event)
{
    if (widget->flag & COGUI_WIDGET_FLAG_SHOWN) {
        return GUI_E_ERROR;
    }

	cogui_screen_refresh(widget->top);

    return GUI_E_OK;
}

void cogui_widget_update(cogui_widget_t *widget);

StatusType cogui_widget_event_handler(cogui_widget_t *widget, struct cogui_event *event)
{
    COGUI_ASSERT(widget != Co_NULL);
    COGUI_ASSERT(event != Co_NULL);

    StatusType result = GUI_E_ERROR;

    switch (event->type)
    {
    case COGUI_EVENT_WIDGET_SHOW:
        result = cogui_widget_onshow(widget, event);
        return result;

     case COGUI_EVENT_WIDGET_HIDE:
        result = cogui_widget_onhide(widget, event);
        return result;
    }

	return result;
}

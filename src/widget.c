/**
 *******************************************************************************
 * @file       widget.c
 * @version    V0.7.3
 * @date       2020.03.25
 * @brief      Some widget function for GUI engine's event.	
 *******************************************************************************
 */ 

#include <cogui.h>

extern font_t *default_font; 
extern window_t *main_page;

StatusType gui_widget_event_handler(widget_t *widget, event_t *event);

static void _gui_widget_init(widget_t *widget)
{
    gui_memset(widget, 0, sizeof(widget_t));

    /* init flag and type */
    widget->flag = GUI_WIDGET_FLAG_INIT | GUI_WIDGET_TYPE_INIT;

    /* set default fore/background */
	widget->gc.foreground = white;
	widget->gc.background = black;
    widget->gc.font       = default_font;

    /* initial extent rectangle */
    GUI_INIT_RECT(&widget->extent);

    /* set event handler */
    widget->handler = gui_widget_event_handler;
}

widget_t *gui_widget_create(struct window *top)
{
    widget_t *widget;

    ASSERT(top != Co_NULL);

    widget = gui_malloc(sizeof(widget_t));
    if (widget == Co_NULL) {
        return Co_NULL;
    }
    
    /* first initial structure data */
    _gui_widget_init(widget);

    /* set type to widget */
    widget->flag &= ~GUI_WIDGET_TYPE_MASK;
    widget->flag |= GUI_WIDGET_TYPE_WIDGET;

    /* create a dc engine */
    widget->dc_engine = gui_dc_begin_drawing(widget);
    ASSERT(widget->dc_engine != Co_NULL);

    widget->top = top;
    widget->id  = top->widget_cnt++;

    gui_widget_list_insert(widget);

    top->focus_widget = widget;
    return widget;
}

void gui_widget_delete(widget_t *widget)
{
    gui_widget_list_pop(widget->id, widget->top);
    gui_dc_end_drawing(widget->dc_engine);
    gui_widget_clear_text(widget);

    if (widget->user_data) {
        gui_free(widget->user_data);
    }

    gui_free(widget);
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
widget_t *gui_widget_list_init(struct window *top)
{	
    /* create header node */
	widget_t *header = gui_widget_create(top);
    ASSERT(header != Co_NULL);
    header->flag |= GUI_WIDGET_FLAG_HEADER;
    
    /* first object should be a fill screen */
    widget_t *widget = gui_widget_create(top);
    ASSERT(widget != Co_NULL);	

    /* enabled it */
    widget->flag |= GUI_WIDGET_FLAG_SHOWN;

    /* set as a full screen rectangle */
    widget->flag |= GUI_WIDGET_FLAG_RECT | GUI_WIDGET_FLAG_HEADER;
    gui_widget_set_rectangle(widget, 0, 0, COGUI_SCREEN_WIDTH, COGUI_SCREEN_HEIGHT);

    /* this node should be filled by background */
    widget->gc.foreground = default_background;
    widget->flag |= GUI_WIDGET_FLAG_FILLED;

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
void gui_widget_list_insert(widget_t *node)
{  
    ASSERT(node != Co_NULL);

    struct window *top = node->top;
    ASSERT(top != Co_NULL);

    /* if it is header node */
    if (top->widget_list == Co_NULL) {
        top->widget_list = node;
        node->next = Co_NULL;
        return;
    }

    widget_t *list = top->widget_list;

    while (list->next != Co_NULL)
        list = list->next;

    list->next = node;
    node->next = Co_NULL;
    
    /* after inserted, refresh screen */
    //gui_window_refresh(top);
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
widget_t *gui_widget_list_pop(uint32_t id, struct window *top)
{
    ASSERT(top != Co_NULL);
    widget_t *list = top->widget_list;
    if (list == Co_NULL) {
        return Co_NULL;
    }

    /* recursive from first node */
    while (list->next != Co_NULL) {
        if (list->next->id == id) {
            widget_t *tmp_widget = list->next;
            
            list->next = tmp_widget->next;

            tmp_widget->next = Co_NULL;
            
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
widget_t *gui_get_widget_node(uint32_t id, struct window *top)
{
    widget_t *list = top->widget_list->next;

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

void gui_widget_set_focus(widget_t *widget, event_handler_ptr handler)
{
    ASSERT(widget != Co_NULL);

    widget->on_focus_in = handler;
}

void gui_widget_set_unfocus(widget_t *widget, event_handler_ptr handler)
{
    ASSERT(widget != Co_NULL);
    
    widget->on_focus_out = handler;
}

void gui_widget_focus(widget_t *widget)
{
    ASSERT(widget != Co_NULL);

    window_t *win = widget->top;

    if (win->focus_widget != Co_NULL) {
        gui_widget_unfocus(win->focus_widget);
    }

    widget->flag |= GUI_WIDGET_FLAG_FOCUS;

    if (win->focus_widget == widget) {
        gui_window_refresh(win);
        return;
    }
    else {
        win->focus_widget = widget;
    }

    if (widget->on_focus_in) {
        widget->on_focus_in(widget, Co_NULL);
    }

    /* put this node into last of the list */
    gui_widget_list_pop(widget->id, win);
    gui_widget_list_insert(widget);
    gui_window_update(win, widget);
}

void gui_widget_unfocus(widget_t *widget)
{
    ASSERT(widget != Co_NULL);

    widget->flag &= ~GUI_WIDGET_FLAG_FOCUS;

    widget->top->focus_widget = Co_NULL;

    if (widget->on_focus_out) {
        widget->on_focus_out(widget, Co_NULL);
    }

    gui_window_refresh(widget->top);
}

void gui_widget_get_rect(widget_t *widget, rect_t *rect)
{
    ASSERT(widget != Co_NULL);

    if (rect != Co_NULL) {
        rect->x1 = rect->y1 = 0;
        rect->x2 = widget->extent.x2 - widget->extent.x1;
        rect->y2 = widget->extent.y2 - widget->extent.y1;
    }
}

void gui_widget_get_extent(widget_t *widget, rect_t *rect)
{
    ASSERT(widget != Co_NULL);
    ASSERT(rect != Co_NULL);

    *rect = widget->extent;
}

static void gui_widget_set_rect(widget_t *widget, rect_t *rect)
{
    if (widget == Co_NULL || rect == Co_NULL)
	    return;

    widget->extent = *rect;

    widget->min_width  = widget->extent.x2 - widget->extent.x1;
    widget->min_height = widget->extent.y2 - widget->extent.y1;
}

void gui_widget_set_rectangle(widget_t *widget, int32_t x, int32_t y, int32_t width, int32_t height)
{
    if (!(widget->top->style & GUI_WINDOW_STYLE_NO_TITLE) && !(widget->flag & GUI_WIDGET_FLAG_TITLE) && !(widget->flag & GUI_WIDGET_FLAG_HEADER) ) {
        if (y <= GUI_WINTITLE_HEIGHT)
            y = GUI_WINTITLE_HEIGHT+1;
    }

    rect_t rect;

    GUI_SET_RECT(&rect, x, y, width, height);
    gui_widget_set_rect(widget, &rect);

    GUI_SET_RECT(&widget->inner_extent, 0, 0, width, height);
}

void gui_widget_set_minsize(widget_t *widget, int32_t width, int32_t height)
{
    ASSERT(widget != Co_NULL);

    widget->min_width = width;
    widget->min_height = height;
}

void gui_widget_set_minwidth(widget_t *widget, int32_t width)
{
    ASSERT(widget != Co_NULL);

    widget->min_width = width;
}

void gui_widget_set_minheight(widget_t *widget, int32_t height)
{
    ASSERT(widget != Co_NULL);

    widget->min_height = height;
}

void gui_widget_enable_border(widget_t *widget)
{
    ASSERT(widget != Co_NULL);

    widget->flag |= GUI_WIDGET_BORDER;

    gui_window_refresh(widget->top);
}

void gui_widget_set_font(widget_t* widget, font_t *font)
{
    ASSERT(widget != Co_NULL);
    ASSERT(font != Co_NULL);

    widget->gc.font = font;
}

void gui_widget_set_text_align(widget_t *widget, uint16_t style)
{
    ASSERT(widget != Co_NULL);

    widget->gc.text_align = style;
}

void gui_widget_set_text(widget_t *widget, const char *text)
{
    ASSERT(widget != Co_NULL);

    widget->flag |= GUI_WIDGET_FLAG_HAS_TEXT;
    
    widget->text = gui_strdup(text);
}

void gui_widget_append_text(widget_t *widget, const char *text)
{
    ASSERT(widget != Co_NULL);
    
    /* if this is first text, just call set_text to do finish work */
    if (!(widget->flag & GUI_WIDGET_FLAG_HAS_TEXT)) {
        gui_widget_set_text(widget, text);
        return;
    }
    
    uint64_t len = gui_strlen(text) + gui_strlen(widget->text) + 1;
    char * new_text = (char *)gui_malloc(len);

    /* create new string and put 'text' on original text's end */
    gui_memcpy(new_text, widget->text, gui_strlen(widget->text));
    gui_memcpy(new_text+gui_strlen(widget->text), text, gui_strlen(text)+1);

    /* after copy original text, free it */
    gui_free(widget->text);

    widget->text = new_text;
}

void gui_widget_clear_text(widget_t *widget)
{
    widget->flag &= ~GUI_WIDGET_FLAG_HAS_TEXT;

    /* free text pointer if needed */
    if (widget->text) {
        gui_free(widget->text);
    }
}

static void _gui_widget_move(widget_t *widget, int32_t dx, int32_t dy)
{
    widget->extent.x1 += dx;
    widget->extent.x2 += dx;

    widget->extent.y1 += dy;
    widget->extent.y2 += dy;

	gui_window_refresh(widget->top);
}

void gui_widget_move_to_logic(widget_t *widget, int32_t dx, int32_t dy)
{
    if (widget == Co_NULL) {
        return;
    }
	
	_gui_widget_move(widget, dx, dy);
}

void gui_widget_move_to_phy(widget_t *widget, int32_t x, int32_t y)
{
    if (widget == Co_NULL) {
        return;
    }

    int32_t dx = x - widget->extent.x1;
    int32_t dy = y - widget->extent.y1;
	
	_gui_widget_move(widget, dx, dy);
}

void gui_widget_point_l2p(widget_t *widget, point_t *point)
{
    ASSERT(widget != Co_NULL);

    if (point != Co_NULL) {
        point->x += widget->extent.x1;
        point->y += widget->extent.y1;
    }
}

void gui_widget_rect_l2p(widget_t *widget, rect_t *rect)
{
    ASSERT(widget != Co_NULL);

    if (rect != Co_NULL) {
        rect->x1 += widget->extent.x1;
        rect->x2 += widget->extent.x1;

        rect->y1 += widget->extent.y1;
        rect->y2 += widget->extent.y1;
    }
}

void gui_widget_point_p2l(widget_t *widget, point_t *point)
{
    ASSERT(widget != Co_NULL);

    if (point != Co_NULL) {
        point->x -= widget->extent.x1;
        point->y -= widget->extent.y1;
    }    
}

void gui_widget_rect_p2l(widget_t *widget, rect_t *rect)
{
    ASSERT(widget != Co_NULL);
    
    if (rect != Co_NULL) {
        rect->x1 -= widget->extent.x1;
        rect->x2 -= widget->extent.x1;

        rect->y1 -= widget->extent.y1;
        rect->y2 -= widget->extent.y1;
    }
}

StatusType gui_widget_show(widget_t *widget)
{
    event_t event;
    ASSERT(widget != Co_NULL);

    StatusType result;

    if (widget->flag & GUI_WIDGET_FLAG_SHOWN)
        return GUI_E_ERROR;

    widget->flag |= GUI_WIDGET_FLAG_SHOWN;

    EVENT_INIT(&event, EVENT_WIDGET_SHOW);

    if (widget->handler != Co_NULL)
        result = widget->handler(widget, &event);

    return result;
}

StatusType gui_widget_hide(widget_t *widget)
{
    event_t event;
    ASSERT(widget != Co_NULL);

    StatusType result;

    if (!(widget->flag & GUI_WIDGET_FLAG_SHOWN))
        return GUI_E_ERROR;
    
    widget->flag &= ~GUI_WIDGET_FLAG_SHOWN;

    EVENT_INIT(&event, EVENT_WIDGET_HIDE);
    
    if (widget->handler != Co_NULL)
        result = widget->handler(widget, &event);

    return result;
}

StatusType gui_widget_onshow(widget_t *widget, event_t *event)
{
    if (!(widget->flag & GUI_WIDGET_FLAG_SHOWN))
        return GUI_E_ERROR;

    gui_widget_focus(widget);

    return GUI_E_OK;
}

StatusType gui_widget_onhide(widget_t *widget, event_t *event)
{
    if (widget->flag & GUI_WIDGET_FLAG_SHOWN) {
        return GUI_E_ERROR;
    }

	gui_window_refresh(widget->top);

    return GUI_E_OK;
}

void cogui_widget_update(widget_t *widget);

StatusType gui_widget_event_handler(widget_t *widget, event_t *event)
{
    ASSERT(widget != Co_NULL);
    ASSERT(event != Co_NULL);

    StatusType result = GUI_E_ERROR;

    switch (event->type)
    {
    case EVENT_WIDGET_SHOW:
        result = gui_widget_onshow(widget, event);
        return result;

     case EVENT_WIDGET_HIDE:
        result = gui_widget_onhide(widget, event);
        return result;
    }

	return result;
}

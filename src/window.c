/**
 ********************************************************************************
 * @file       window.c
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      Some window management function.
 *******************************************************************************
 */ 

#include <cogui.h>

extern window_t *main_page;
extern struct cursor *_cursor;

window_t *current_window;
int16_t current_app_install_cnt = 0;

struct main_app_table main_app_table[9];

StatusType cogui_window_event_handler(window_t * win, struct event *event);

static void _cogui_window_init(window_t *win)
{
    cogui_memset(win, 0, sizeof(window_t));

    win->app        = gui_app_self();
    win->app->win   = win;
    win->id         = gui_app_self()->win_id;

    win->title_name = gui_app_self()->name;

    win->flag       = COGUI_WINDOW_FLAG_INIT;
    win->handler    = cogui_window_event_handler;
}

window_t *cogui_window_create(uint16_t style)
{
    window_t *win;
    win = gui_malloc(sizeof(window_t));
    if (win == Co_NULL)
        return Co_NULL;

    _cogui_window_init(win);

    cogui_widget_list_init(win);

    if (!(style & COGUI_WINDOW_STYLE_NO_TITLE)) {
        win->title = cogui_widget_create(win);
        cogui_title_create(win);
    }

    win->style = style;
    win->magic = COGUI_WINDOW_MAGIC;

    return win;
}

window_t *gui_main_window_create(void)
{
    window_t *win     = cogui_window_create_without_title();
    widget_t *widget;
    uint16_t     i;

    widget = cogui_widget_create(win);
    cogui_widget_set_rectangle(widget, 0, 0, 240, 40);
    widget->flag |= COGUI_WIDGET_FLAG_RECT | COGUI_WIDGET_FLAG_FILLED;
    cogui_widget_set_text(widget, "CoOS");
    cogui_widget_set_font(widget, &tm_font_16x26);
    cogui_widget_set_text_align(widget, GUI_TEXT_ALIGN_CENTER|GUI_TEXT_ALIGN_MIDDLE);
    COGUI_WIDGET_ENABLE(widget);

    for ( i=0; i<9; i++) {
        widget = cogui_widget_create(win);
        cogui_widget_set_rectangle(widget, 15 + (i%3)*75 , 55 + (i/3)*88, 60, 60);
        widget->gc.foreground = green; 
        widget->flag |= COGUI_WIDGET_FLAG_RECT;
        cogui_widget_set_font(widget, &tm_font_16x26);
        cogui_widget_set_text_align(widget, GUI_TEXT_ALIGN_CENTER|GUI_TEXT_ALIGN_MIDDLE);

        main_app_table[i].app_icon = widget;

        widget = cogui_widget_create(win);
        cogui_widget_set_rectangle(widget, 15 + (i%3)*75 , 115 + (i/3)*88, 60, 13);
        widget->flag |= COGUI_WIDGET_FLAG_RECT| COGUI_WIDGET_FLAG_FILLED;
        cogui_widget_set_text_align(widget, GUI_TEXT_ALIGN_CENTER|GUI_TEXT_ALIGN_MIDDLE);

        main_app_table[i].app_title_box = widget;
    }

    gui_window_show(win);

    return win;
}

int16_t gui_main_page_app_install(char* title)
{
    if (current_app_install_cnt > 9) {
        return GUI_E_APP_FULL;
    }

    widget_t *widget;
    char *icon_text = gui_strdup(title);
    icon_text[1] = 0;
    widget = main_app_table[current_app_install_cnt].app_icon;
    cogui_widget_set_text(widget, icon_text);

    widget->flag |= COGUI_WIDGET_FLAG_FILLED;
    widget->gc.background = green;
    widget->gc.foreground = white;
    widget->user_data = gui_app_self();
    COGUI_WIDGET_ENABLE(widget);

    widget = main_app_table[current_app_install_cnt].app_title_box;
    cogui_widget_set_text(widget, title);
    COGUI_WIDGET_ENABLE(widget);

    main_app_table[current_app_install_cnt].title   = title;

    return current_app_install_cnt++;
}

void cogui_main_page_app_uninstall(int16_t id)
{
    ASSERT((id < current_app_install_cnt) && (id >= 0));

    main_app_table[id].app_icon->flag &= ~COGUI_WIDGET_FLAG_FILLED;
    main_app_table[id].title = Co_NULL;

    cogui_widget_clear_text(main_app_table[id].app_icon);
    cogui_widget_clear_text(main_app_table[id].app_title_box);

    widget_t *widget;    
    widget = main_app_table[id].app_icon;
    widget->gc.background = black;
    widget->gc.foreground = green;

    
    uint16_t i;
    for ( i=id+1; i<=current_app_install_cnt; i++) {                                            /* shift all app icon forward           */
        main_app_table[i-1].app_icon->flag      =  main_app_table[i].app_icon->flag;            /* copy useful data for icon widget     */
        main_app_table[i-1].app_icon->user_data =  main_app_table[i].app_icon->user_data;
        main_app_table[i-1].app_icon->gc        =  main_app_table[i].app_icon->gc;
        main_app_table[i-1].app_icon->text      =  main_app_table[i].app_icon->text;

        main_app_table[i-1].app_title_box->text =  main_app_table[i].app_title_box->text;       /* copy useful data for title widget    */
        main_app_table[i-1].app_title_box->flag =  main_app_table[i].app_title_box->flag;
        
        if (main_app_table[i-1].app_icon->user_data) {                                          /* update window id if need             */
            ((app_t *)(main_app_table[i-1].app_icon->user_data))->win->id = i-1;
            ((app_t *)(main_app_table[i-1].app_icon->user_data))->win_id  = i-1;
        }
    }

    --current_app_install_cnt;
}

static widget_t *cpgui_window_inverse_widgets_list(window_t *top)
{
    widget_t *inverse_list = top->widget_list; 
    widget_t *tmp_list = top->widget_list,*tmp_node = Co_NULL;

    while (tmp_list->next != Co_NULL) {
        inverse_list = tmp_list->next;
        tmp_list->next = tmp_node;
        tmp_node = tmp_list;
        tmp_list = inverse_list;
    }
    inverse_list-> next = tmp_node;

    top->widget_list = inverse_list;

    return inverse_list;
}

widget_t *gui_window_get_mouse_event_widget(window_t *top, uint16_t cx, uint16_t cy)
{
    ASSERT(top != Co_NULL);

    if (top != cogui_get_current_window()) {
        return Co_NULL;
    }

    widget_t *event_wgt = Co_NULL;

    cpgui_window_inverse_widgets_list(top);                         /* inverse widgets list to find event widget from top */

    widget_t *tmp_list = top->widget_list;
    while (!(tmp_list->flag & COGUI_WIDGET_FLAG_HEADER)) {
        if (!(tmp_list->flag & COGUI_WIDGET_FLAG_SHOWN)) {
            tmp_list=tmp_list->next;
            continue;
        }

        if ((cx >= tmp_list->extent.x1) && (cx <=tmp_list->extent.x2) &&
            (cy >= tmp_list->extent.y1) && (cy <=tmp_list->extent.y2)) {
            event_wgt = tmp_list;
            break;
        }

        tmp_list=tmp_list->next;
    }

    cpgui_window_inverse_widgets_list(top);                         /* inverse back to turn everythings back */

    if (top->focus_widget && top->focus_widget != event_wgt) {
        cogui_widget_unfocus(top->focus_widget);
    }

    top->last_mouse_event_widget = event_wgt;

    return event_wgt;
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
StatusType cogui_window_update(window_t *top, widget_t *widget)
{
    ASSERT(top != Co_NULL);

    if (!COGUI_WINDOW_IS_ENABLE(top) && top != main_page) {
        top = main_page;
    }

    if (!COGUI_WINDOW_IS_ENABLE(top) && top == main_page) {
        return GUI_E_ERROR;
    }

    widget_t *list = top->widget_list->next;

    while (list != widget && widget!= Co_NULL) {
        list = list->next;
    }

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
                gui_dc_draw_rect(list->dc_engine, &list->inner_extent);
            }
        }
        
        /* draw text if needed */
        if (list->flag & COGUI_WIDGET_FLAG_HAS_TEXT) {
            rect_t pr = list->inner_extent;
            uint64_t padding = list->gc.padding;
            COGUI_RECT_PADDING(&pr, padding);

            gui_dc_draw_text(list->dc_engine, &pr, list->text);
        }

        /* draw border at last if needed */
        if (list->flag & COGUI_WIDGET_BORDER) {
            gui_dc_draw_border(list->dc_engine, &list->inner_extent);
        }        

        /* go forward to next node */
        list = list->next;
    }

    if (_cursor) {
        //gui_mouse_show();
    }

    return GUI_E_OK;
}

StatusType gui_window_refresh(window_t *top) {
    return cogui_window_update(top, Co_NULL);
}

void cogui_window_delete(window_t *win)
{
    /* remove magic code */
    win->magic = 0;

    /* delete title widget */
    //cogui_title_delete(win);
    //cogui_widget_delete(win->title);

    /* delete all widget */
    widget_t *tmp_widget = win->widget_list->next;
    widget_t *next_delete_widget = tmp_widget->next;
    while (next_delete_widget != Co_NULL) {
        cogui_widget_delete(tmp_widget);
        tmp_widget = next_delete_widget;
        next_delete_widget = next_delete_widget->next;
    }

    /* last delete header widget */
    //cogui_widget_delete(win->widget_list);

    /* remove window pointer in app structure */
    win->app->win = Co_NULL;

    /* free user data if need */
    if (win->user_data) {
        gui_free(win->user_data);
    }

    cogui_main_page_app_uninstall(win->id);

    /* free window */
    gui_free(win);
}

StatusType gui_window_close(window_t *win)
{
    ASSERT(win != Co_NULL);

    cogui_window_delete(win);

    struct event event;
    EVENT_INIT(&event, EVENT_WINDOW_CLOSE);
    event.win = win;

    return gui_send(gui_get_server(), &event);
}

void cogui_window_set_onactivate(window_t *win, event_handler_ptr handler)
{
    ASSERT(win != Co_NULL);
    
    win->on_activate = handler;
}

void cogui_window_set_ondeactive(window_t *win, event_handler_ptr handler)
{
    ASSERT(win != Co_NULL);
    
    win->on_deactivate = handler;
}


void cogui_window_set_onkey(window_t *win, event_handler_ptr handler)
{
    ASSERT(win != Co_NULL);
    
    win->on_key = handler;
}

StatusType gui_window_show(window_t *win)
{
    ASSERT(win != Co_NULL);
    struct event event;
    StatusType result;

    /* if this is not main page to show, first hide main page */
    if (win != main_page) {
        COGUI_WINDOW_DISABLE(main_page);
    }

    /* determine whether if window is need to show */
    if (COGUI_WINDOW_IS_ENABLE(win)) {
        return GUI_E_ERROR;
    }
    else {
        COGUI_WINDOW_ENABLE(win);
    }

    EVENT_INIT(&event, EVENT_WINDOW_SHOW);

    if (win->handler != Co_NULL)
        result = win->handler(win, &event);

    return result;
}

StatusType gui_window_hide(window_t *win)
{
    ASSERT(win != Co_NULL);
    struct event event;
    StatusType result;

    /* determine whether if window is need to hide */
    if (!COGUI_WINDOW_IS_ENABLE(win)) {
        return GUI_E_ERROR;
    }
    else {
        COGUI_WINDOW_DISABLE(win);
    }

    EVENT_INIT(&event, EVENT_WINDOW_HIDE);

    if (win->handler != Co_NULL)
        result = win->handler(win, &event);

    return result;
}

StatusType cogui_window_onshow(window_t *win)
{
    if (!COGUI_WINDOW_IS_ENABLE(win)) {
        return GUI_E_ERROR;
    }

	gui_window_refresh(win);

    current_window = win;

    return GUI_E_OK;
}

StatusType cogui_window_onhide(window_t *win)
{
    if (COGUI_WINDOW_IS_ENABLE(win)) {
        return GUI_E_ERROR;
    }

    if (win->focus_widget != Co_NULL) {
        cogui_widget_unfocus(win->focus_widget);
    }

    struct event event;
    EVENT_INIT(&event, EVENT_WINDOW_HIDE);
    event.win = win;

    return gui_send(gui_get_server(), &event);
}

window_t *cogui_get_main_window(void)
{
    return main_page;
}

window_t *cogui_get_current_window(void)
{
    return current_window;
}

StatusType cogui_window_event_handler(window_t *win, struct event *event)
{
    ASSERT(win != Co_NULL);
    ASSERT(event != Co_NULL);

    StatusType result = GUI_E_ERROR;

    switch (event->type)
    {
    case EVENT_WINDOW_SHOW:
        result = cogui_window_onshow(win);
        break; 

    case EVENT_WINDOW_HIDE:
        result = cogui_window_onhide(win);
        break; 
    
    case EVENT_WINDOW_CLOSE:
        result = gui_window_close(win);
        break; 

    default:
        break;
    }

	return result;
}

void cogui_assert_failed_page(const char* ex, uint16_t line, const char* func)
{
    /* let full screen background set to blue */
    main_page->widget_list->next->gc.foreground = blue;
    main_page->widget_list->next->next = Co_NULL;

    gui_window_show(main_page);
    /* create a widget to print error text */
    widget_t *widget;
    widget = cogui_widget_create(main_page);
    cogui_widget_set_rectangle(widget, 15 , 55, 60, 60);
    widget->gc.foreground = white; 
    cogui_widget_set_font(widget, &tm_font_16x26);

    widget->gc.padding = GUI_PADDING(17, 0, 5, 0);

    /* set to error code */
    cogui_widget_set_text(widget, ":("); 
    cogui_widget_show(widget);

    widget = cogui_widget_create(main_page);
    cogui_widget_set_rectangle(widget, 20 , 120, 200, 200);
    cogui_widget_set_font(widget, &tm_font_11x18);
    cogui_widget_set_text(widget, "Your computer ran into a problem.\n"); 
    cogui_widget_show(widget);

    widget = cogui_widget_create(main_page);
    cogui_widget_set_rectangle(widget, 20 , 170, 200, 150);
    char *ex_str = gui_strdup(ex);
    char *f_str = gui_strdup(func);
    char l_str[10];
    cogui_itoa(line, l_str);

    cogui_widget_set_text(widget, "Assert failed at\n"); 
    cogui_widget_append_text(widget, f_str);
    cogui_widget_append_text(widget, "\nLine: ");
    cogui_widget_append_text(widget, l_str);
    cogui_widget_append_text(widget, "\nExpression: ");
    cogui_widget_append_text(widget, ex_str);
    cogui_widget_show(widget);
}

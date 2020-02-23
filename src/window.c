/**
 ********************************************************************************
 * @file       window.c
 * @version    V0.6.1
 * @date       2020.01.18
 * @brief      Some window management function.
 *******************************************************************************
 */ 

#include <cogui.h>

extern cogui_window_t *main_page;
cogui_window_t *current_window;
co_int16_t current_app_install_cnt = 0;

struct main_app_table main_app_table[9];

static co_int16_t cogui_main_page_app_install(char *title);
static void cogui_main_page_app_uninstall(co_int16_t);

StatusType cogui_window_event_handler(struct cogui_window * win, struct cogui_event *event);

static void _cogui_window_init(cogui_window_t *win)
{
    cogui_memset(win, 0, sizeof(cogui_window_t));

    win->app        = cogui_app_self();
    win->app->win   = win;

    win->title_name = cogui_app_self()->name;

    win->flag       = COGUI_WINDOW_FLAG_INIT;
    win->handler    = cogui_window_event_handler;
}

cogui_window_t *cogui_window_create(co_uint16_t style)
{
    co_int16_t id = -1;
    if (main_page) {
        id = cogui_main_page_app_install(cogui_app_self()->name);
    }

    cogui_window_t *win;
    win = cogui_malloc(sizeof(cogui_window_t));
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
    win->id    = id;

    return win;
}

cogui_window_t *cogui_main_window_create(void)
{
    cogui_window_t *win     = cogui_window_create_without_title();
    cogui_widget_t *widget;
    co_uint16_t     i;

    widget = cogui_widget_create(win);
    cogui_widget_set_rectangle(widget, 0, 0, 240, 40);
    widget->gc.background = COGUI_BLACK;
    widget->flag |= COGUI_WIDGET_FLAG_RECT | COGUI_WIDGET_FLAG_FILLED;
    cogui_widget_set_text(widget, "CoOS");
    cogui_widget_set_font(widget, &tm_font_16x26);
    cogui_widget_set_text_align(widget, COGUI_TEXT_ALIGN_CENTER|COGUI_TEXT_ALIGN_MIDDLE);
    COGUI_WIDGET_ENABLE(widget);

    for ( i=0; i<9; i++) {
        widget = cogui_widget_create(win);
        cogui_widget_set_rectangle(widget, 15 + (i%3)*75 , 55 + (i/3)*88, 60, 60);
        widget->gc.foreground = COGUI_GREEN; 
        widget->flag |= COGUI_WIDGET_FLAG_RECT;
        COGUI_WIDGET_ENABLE(widget);
        cogui_widget_set_font(widget, &tm_font_16x26);
        cogui_widget_set_text_align(widget, COGUI_TEXT_ALIGN_CENTER|COGUI_TEXT_ALIGN_MIDDLE);

        main_app_table[i].app_icon = widget;

        widget = cogui_widget_create(win);
        cogui_widget_set_rectangle(widget, 15 + (i%3)*75 , 115 + (i/3)*88, 60, 13);
        widget->gc.foreground = COGUI_WHITE; 
        widget->flag |= COGUI_WIDGET_FLAG_RECT| COGUI_WIDGET_FLAG_FILLED;
        cogui_widget_set_text_align(widget, COGUI_TEXT_ALIGN_CENTER|COGUI_TEXT_ALIGN_MIDDLE);
        COGUI_WIDGET_ENABLE(widget);

        main_app_table[i].app_title_box = widget;
    }

    cogui_window_show(win);

    return win;
}

static co_int16_t cogui_main_page_app_install(char* title)
{
    if (current_app_install_cnt > 9) {
        return GUI_E_ERROR;
    }

    cogui_widget_t *widget;
    char *icon_text = cogui_strdup(title);
    icon_text[1] = 0;
    widget = main_app_table[current_app_install_cnt].app_icon;
    cogui_widget_set_text(widget, icon_text);

    widget->flag |= COGUI_WIDGET_FLAG_FILLED;
    widget->gc.background = COGUI_GREEN;
    widget->gc.foreground = COGUI_WHITE;

    widget = main_app_table[current_app_install_cnt].app_title_box;
    cogui_widget_set_text(widget, title);

    main_app_table[current_app_install_cnt].title = title;

    return current_app_install_cnt++;
}

static void cogui_main_page_app_uninstall(co_int16_t id)
{
    COGUI_ASSERT((id < current_app_install_cnt) && (id >= 0));

    main_app_table[id].app_icon->flag &= ~COGUI_WIDGET_FLAG_FILLED;
    main_app_table[id].title = Co_NULL;

    cogui_widget_clear_text(main_app_table[id].app_icon);
    cogui_widget_clear_text(main_app_table[id].app_title_box);

    cogui_widget_t *widget;    
    widget = main_app_table[current_app_install_cnt].app_icon;
    widget->gc.background = COGUI_BLACK;
    widget->gc.foreground = COGUI_GREEN;

    /* if this app is not previous install app, we need to shift all app forward */
    if (id != --current_app_install_cnt) {
        co_uint16_t i;
        for ( i=id+1; i<=current_app_install_cnt; i++) {
            cogui_memcpy(main_app_table+(i-1), main_app_table+i, sizeof(struct main_app_table));
        }
    }
}   

void cogui_window_delete(cogui_window_t *win)
{
    /* remove magic code */
    win->magic = 0;

    /* delete title widget */
    cogui_title_delete(win);
    cogui_widget_delete(win->title);

    /* delete all widget */
    cogui_widget_t *tmp_widget = win->widget_list->next;
    cogui_widget_t *next_delete_widget = tmp_widget;
    while ((next_delete_widget = next_delete_widget->next) != Co_NULL) {
        cogui_widget_delete(tmp_widget);
        tmp_widget = next_delete_widget;
    }

    /* last delete header widget */
    cogui_widget_delete(win->widget_list);

    /* remove window pointer in app structure */
    win->app->win = Co_NULL;

    /* free user data if need */
    if (win->user_data) {
        cogui_free(win->user_data);
    }

    cogui_main_page_app_uninstall(win->id);

    /* free window */
    cogui_free(win);
}

StatusType cogui_window_close(cogui_window_t *win)
{
    COGUI_ASSERT(win != Co_NULL);

    cogui_window_delete(win);

    struct cogui_event event;
    COGUI_EVENT_INIT(&event, COGUI_EVENT_WINDOW_CLOSE);
    event.win = win;

    return cogui_send(cogui_get_server(), &event);
}

void cogui_window_set_onactivate(cogui_window_t *win, event_handler_ptr handler)
{
    COGUI_ASSERT(win != Co_NULL);
    
    win->on_activate = handler;
}

void cogui_window_set_ondeactive(cogui_window_t *win, event_handler_ptr handler)
{
    COGUI_ASSERT(win != Co_NULL);
    
    win->on_deactivate = handler;
}


void cogui_window_set_onkey(cogui_window_t *win, event_handler_ptr handler)
{
    COGUI_ASSERT(win != Co_NULL);
    
    win->on_key = handler;
}

StatusType cogui_window_show(cogui_window_t *win)
{
    COGUI_ASSERT(win != Co_NULL);
    struct cogui_event event;
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

    COGUI_EVENT_INIT(&event, COGUI_EVENT_WINDOW_SHOW);

    if (win->handler != Co_NULL)
        result = win->handler(win, &event);

    return result;
}

StatusType cogui_window_hide(cogui_window_t *win)
{
    COGUI_ASSERT(win != Co_NULL);
    struct cogui_event event;
    StatusType result;

    /* determine whether if window is need to hide */
    if (!COGUI_WINDOW_IS_ENABLE(win)) {
        return GUI_E_ERROR;
    }
    else {
        COGUI_WINDOW_DISABLE(win);
    }

    COGUI_EVENT_INIT(&event, COGUI_EVENT_WINDOW_HIDE);

    if (win->handler != Co_NULL)
        result = win->handler(win, &event);

    return result;
}

StatusType cogui_window_onshow(cogui_window_t *win)
{
    if (!COGUI_WINDOW_IS_ENABLE(win)) {
        return GUI_E_ERROR;
    }

	cogui_screen_refresh(win);

    current_window = win;

    return GUI_E_OK;
}

StatusType cogui_window_onhide(cogui_window_t *win)
{
    if (COGUI_WINDOW_IS_ENABLE(win)) {
        return GUI_E_ERROR;
    }

    struct cogui_event event;
    COGUI_EVENT_INIT(&event, COGUI_EVENT_WINDOW_HIDE);
    event.win = win;

    return cogui_send(cogui_get_server(), &event);
}

cogui_window_t *cogui_get_current_window()
{
    cogui_app_t *app = cogui_app_self();

    return app->win;
}

StatusType cogui_window_event_handler(struct cogui_window *win, struct cogui_event *event)
{
    COGUI_ASSERT(win != Co_NULL);
    COGUI_ASSERT(event != Co_NULL);

    StatusType result = GUI_E_ERROR;

    switch (event->type)
    {
    case COGUI_EVENT_WINDOW_SHOW:
        result = cogui_window_onshow(win);
        break; 

    case COGUI_EVENT_WINDOW_HIDE:
        result = cogui_window_onhide(win);
        break; 
    
    case COGUI_EVENT_WINDOW_CLOSE:
        result = cogui_window_close(win);
        break; 

    default:
        break;
    }

	return result;
}

void cogui_assert_failed_page(const char* ex, co_uint16_t line, const char* func)
{
    /* let full screen background set to blue */
    main_page->widget_list->next->gc.background = COGUI_BLUE;
    main_page->widget_list->next->next = Co_NULL;

    cogui_window_show(main_page);
    /* create a widget to print error text */
    cogui_widget_t *widget;
    widget = cogui_widget_create(main_page);
    cogui_widget_set_rectangle(widget, 15 , 55, 60, 60);
    widget->gc.foreground = COGUI_WHITE; 
    cogui_widget_set_font(widget, &tm_font_16x26);

    widget->gc.padding = COGUI_PADDING(17, 0, 5, 0);

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
    char *ex_str = cogui_strdup(ex);
    char *f_str = cogui_strdup(func);
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

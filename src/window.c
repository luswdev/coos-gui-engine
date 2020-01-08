/**
 ********************************************************************************
 * @file       window.c
 * @version    V0.1.1
 * @date       2020.01.04
 * @brief      Some window management function.
 *******************************************************************************
 */ 

#include <cogui.h>

extern cogui_window_t *main_page;
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
    widget->gc.foreground = COGUI_DARK_GRAY; 
    widget->flag |= COGUI_WIDGET_FLAG_RECT | COGUI_WIDGET_FLAG_FILLED;
    COGUI_WIDGET_ENABLE(widget);

    for ( i=0; i<9; i++) {
        widget = cogui_widget_create(win);
        cogui_widget_set_rectangle(widget, 15 + (i%3)*75 , 55 + (i/3)*88, 60, 60);
        widget->gc.foreground = COGUI_GREEN; 
        widget->flag |= COGUI_WIDGET_FLAG_RECT;
        COGUI_WIDGET_ENABLE(widget);

        main_app_table[i].app_icon = widget;

        widget = cogui_widget_create(win);
        cogui_widget_set_rectangle(widget, 15 + (i%3)*75 , 115 + (i/3)*88, 60, 13);
        widget->gc.foreground = COGUI_WHITE; 
        widget->flag |= COGUI_WIDGET_FLAG_RECT;

        main_app_table[i].app_title_box = widget;
    }

    cogui_window_show(win);

    return win;
}

static co_int16_t cogui_main_page_app_install(char* title)
{
    if (current_app_install_cnt > 9) {
        return Co_FALSE;
    }

    cogui_widget_t *widget;    
    widget = main_app_table[current_app_install_cnt].app_icon;

    widget->flag |= COGUI_WIDGET_FLAG_FILLED;

    main_app_table[current_app_install_cnt].title = title;

    return current_app_install_cnt++;
}

static void cogui_main_page_app_uninstall(co_int16_t id)
{
    COGUI_ASSERT((id < current_app_install_cnt) && (id >= 0));

    main_app_table[id].app_icon->flag &= ~COGUI_WIDGET_FLAG_FILLED;
    main_app_table[id].title = Co_NULL;

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
        return Co_FALSE;
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
        return Co_FALSE;
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
        return Co_FALSE;
    }

	cogui_screen_refresh(win);

    return Co_TRUE;
}

StatusType cogui_window_onhide(cogui_window_t *win)
{
    if (COGUI_WINDOW_IS_ENABLE(win)) {
        return Co_FALSE;
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

    StatusType result = Co_FALSE;

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
    COGUI_DC_FC(main_page->widget_list->next->dc_engine) = COGUI_BLUE;
    cogui_dc_fill_rect_forecolor(main_page->widget_list->next->dc_engine, &main_page->widget_list->next->inner_extent);
    cogui_widget_t *widget;
    widget = cogui_widget_create(main_page);
    cogui_widget_set_rectangle(widget, 15 , 55, 60, 60);
    widget->gc.foreground = COGUI_WHITE; 
    cogui_tm_16x26_puts(5, 17, ":(", widget);
    cogui_widget_set_rectangle(widget, 20 , 120, 200, 200);
    cogui_tm_11x18_puts(0, 0, "Your computer ran into a problem.\n", widget);

    char *ex_str = cogui_strdup(ex);
    char *f_str = cogui_strdup(func);
    char l_str[10];
    cogui_itoa(line, l_str);

    cogui_tm_7x10_puts(0, 50, "Assert failed at\n", widget);
    cogui_tm_7x10_puts(0, 60, "Function: ", widget);
    cogui_tm_7x10_puts(70, 60, f_str, widget);
    cogui_tm_7x10_puts(0, 70, "Line: ", widget);
    cogui_tm_7x10_puts(42, 70, l_str, widget);
    cogui_tm_7x10_puts(0, 80, "Expression: ", widget);
    cogui_tm_7x10_puts(84, 80, ex_str, widget);
    //cogui_tm_11x18_puts(0, 80, str, widget);
}

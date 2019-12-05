/**
 ********************************************************************************
 * @file       window.c
 * @version    V0.0.2
 * @date       2019.10.7
 * @brief      Some window management function.
 *******************************************************************************
 */ 

#include <cogui.h>

extern cogui_window_t *main_page;

static void _cogui_window_init(cogui_window_t *win)
{
    /* filled window pointer to current app structure */
    win->app = cogui_app_self();
    win->app->win = win;

    /* initial widget count */
    win->widget_cnt = 0;

    /* initial oncall function */
    win->on_activate     = Co_NULL;
    win->on_deactivate   = Co_NULL;
    win->on_key          = Co_NULL;

    /* initial title pointer */
    win->title           = Co_NULL;
    win->title_name      = cogui_app_self()->name;

    win->widget_list     = Co_NULL;

    win->last_mouse_event_widget = Co_NULL;
    win->focus_widget = Co_NULL;

    //cogui_window_hide(window);

    win->flag = COGUI_WINDOW_FLAG_INIT;
    win->handler = cogui_window_event_handler;

    win->user_data = 0;

    //window->_do_show = cogui_window_do_show;
}

cogui_window_t *cogui_window_create(co_uint16_t style)
{
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
    return win;
}

cogui_window_t *cogui_main_window_create(void)
{
    cogui_window_t *win     = COGUI_WINDOW_CREATE_WITHOUT_TITLE();
    cogui_widget_t *widget  = cogui_widget_create(win);

    cogui_widget_set_rectangle(widget, 50, 50, 50, 50);
    widget->gc.foreground = COGUI_GREEN;
    widget->flag |= COGUI_WIDGET_FLAG_RECT | COGUI_WIDGET_FLAG_FILLED;

    COGUI_WIDGET_ENABLE(widget);
    cogui_window_show(win);

    return win;
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

    /* free window */
    cogui_free(win);
}

StatusType cogui_window_close(cogui_window_t *win)
{
    COGUI_ASSERT(win != Co_NULL);

    cogui_window_delete(win);

    return Co_TRUE;
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

    struct cogui_event_win event;
    COGUI_EVENT_INIT(&event.parent, COGUI_EVENT_WINDOW_HIDE);
    event.win = win;

    return cogui_send(cogui_get_server(), &event.parent);
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


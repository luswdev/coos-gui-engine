/**
 ********************************************************************************
 * @file       window.c
 * @version    V0.0.1   
 * @date       2019.9.29
 * @brief      Some system function for GUI engine's event.	
 *******************************************************************************
 */ 

#include <cogui.h>

static void _cogui_window_init(cogui_window_t *window)
{
    window->parent_window = Co_NULL;
    window->app = cogui_app_self();

    /* initial oncall function */
    window->on_activate     = Co_NULL;
    window->on_deactivate   = Co_NULL;
    window->on_focus_in     = Co_NULL;
    window->on_focus_out    = Co_NULL;
    window->on_key          = Co_NULL;

    /* set title to app's name */
    window->title       = app->name;
    window->_title_wgt  = Co_NULL;

    window->last_mouse_event_widget = Co_NULL;
    window->focus_widget = Co_NULL;

    cogui_window_hide(window);

    window->flag = COGUI_WINDOW_FLAG_INIT;
    window->handler = cogui_window_event_handler;

    window->user_data = 0;

    window->_do_show = cogui_window_do_show;
}

cogui_window_t *cogui_window_create(cogui_window_t *parentWindow, cogui_rect_t *rect, U16 style)
{
    cogui_window_t *window;

    window = cogui_malloc(sizeof(cogui_window_t));
    if (window == Co_NULL)
        return Co_NULL;
    
    COGUI_WIDGET(window) = cogui_widget_create;
    COGUI_WIDGET(window)->type = COGUI_WIDGET_TYPE_WINDOW;

    _cogui_window_init(window);

}
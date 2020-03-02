/**
 *******************************************************************************
 * @file       server.c
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      The server for gui engine.	
 *******************************************************************************
 */ 

#include <cogui.h>

cogui_app_t *server_app = Co_NULL;
OS_STK   server_Stk[512]={0};
extern cogui_window_t *main_page;
extern struct main_app_table main_app_table[9];

void cogui_server_handler_mouse_button(struct cogui_event *event)
{
    cogui_mouse_return_picture();
    if (cogui_get_current_window() == cogui_get_main_window()) {
        cogui_point_t cursor_pt;
        cogui_widget_t *event_wgt, *last_ewgt = main_page->last_mouse_event_widget;
        cogui_mouse_get_position(&cursor_pt);
        event_wgt = cogui_window_get_mouse_event_widget(cogui_app_self()->win, cursor_pt.x, cursor_pt.y);

        if (event_wgt && event_wgt->user_data) {
            if ((event->button & COGUI_MOUSE_BUTTON_UP) && last_ewgt == event_wgt) {
                cogui_app_t *eapp = (cogui_app_t *)event_wgt->user_data;
                COGUI_EVENT_INIT(event, COGUI_EVENT_PAINT);
                event->app = eapp;
            }
        } else {
            cogui_mouse_show();
            return;
        }
    } else {
        COGUI_EVENT_INIT(event, COGUI_EVENT_MOUSE_BUTTON);
        event->app = cogui_get_current_window()->app;
    }

    if (event->app != Co_NULL) {
        while(cogui_send(event->app, event) != GUI_E_OK){
            CoTickDelay(50);
        }
    }
}

void cogui_server_handler_mouse_motion(struct cogui_event *event)
{
    cogui_mouse_move_delta(event->dx, event->dy);
}

void cogui_server_event_kbd(struct cogui_event *event)
{
    /* the topwin contains current mouse */
    //P_TopWin win = Co_NULL;

    COGUI_EVENT_INIT(event, COGUI_EVENT_KBD);

    /*win = GetTopWinFocus();
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;*/

    cogui_send(event->app, event);
}

StatusType cogui_server_event_handler(struct cogui_event *event)
{
    COGUI_ASSERT(event != Co_NULL);

    StatusType result = GUI_E_ERROR;

    //cogui_printf("[Server] Got a event no.%d\r\n", event->type);

    switch (event->type)
    {
	case COGUI_EVENT_APP_CREATE:
    case COGUI_EVENT_APP_DELE:
		result = cogui_ack(event, E_OK);
		break;

    case COGUI_EVENT_PAINT:
        //result = cogui_send(event->sender, event);
        break;
		
    /* mouse and keyboard event */
    case COGUI_EVENT_MOUSE_BUTTON:
        cogui_server_handler_mouse_button(event);
        break;

    case COGUI_EVENT_MOUSE_MOTION:
        cogui_server_handler_mouse_motion(event);
        break;

    case COGUI_EVENT_WINDOW_CLOSE:
    {
        if (event->win) {
            result = GUI_E_ERROR;
        }

        result = cogui_window_show(server_app->win);    
        cogui_mouse_show();
        break;
    }

    case COGUI_EVENT_WINDOW_HIDE:
    {
        if (COGUI_WINDOW_IS_ENABLE(event->win)) {
            result = GUI_E_ERROR;
        }

        result = cogui_window_show(server_app->win);    
        cogui_mouse_show();
        break;
    }
        
    case COGUI_EVENT_KBD:
        /* handle keyboard event */
		
        //cogui_server_event_handler_kbd((struct cogui_event_kbd *)event);
        break;

    default:
        break;
    }

    return result;
}

void cogui_server_entry(void *parameter)
{
    server_app = cogui_app_create("Server");
    if(server_app == Co_NULL){
        return;
    }

    server_app->handler = cogui_server_event_handler;

    cogui_app_run(server_app);
    cogui_app_delete(server_app);
    server_app = Co_NULL;

    CoExitTask();
}

StatusType cogui_server_post_event(struct cogui_event *event)
{
    StatusType result;

    if (server_app != Co_NULL){
        result = cogui_send(server_app, event);
    }
    else{
        result = GUI_E_ERROR;
    }

    return result;
}

StatusType cogui_server_post_event_sync(struct cogui_event *event)
{
    StatusType result;

    if (server_app != Co_NULL){
        result = cogui_send_sync(server_app, event);
    }
    else{
        result = GUI_E_ERROR;
    }

    return result;
}


cogui_app_t *cogui_get_server(void)
{
    return server_app;
}

void cogui_server_init(void)
{
    CoCreateTask(cogui_server_entry, (void *)0, 15,&server_Stk[511], 512);
}

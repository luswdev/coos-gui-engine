/**
 *******************************************************************************
 * @file       server.c
 * @version    V0.0.5
 * @date       2020.01.19
 * @brief      The server for gui engine.	
 *******************************************************************************
 */ 

#include <cogui.h>

#define TASK_STK_SIZE		512

cogui_app_t *server_app = Co_NULL;
OS_STK   server_Stk[TASK_STK_SIZE]={0};

void cogui_server_handler_mouse_btn(struct cogui_event *event)
{
    /* the topwin contains current mouse */
    //P_TopWin win    = Co_NULL;

    COGUI_EVENT_INIT(event, COGUI_EVENT_MOUSE_BUTTON);

    /* set cursor position */
    //MouseSetPos(event->x, event->y);

    /*win = GetTopWin(event->x, event->y);
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;*/

    while(cogui_send(event->app, event) != E_OK){
        CoTickDelay(50);
    }
}

void cogui_server_handler_mouse_motion(struct cogui_event *event)
{
    /* the topwin contains current mouse */
    //P_TopWin win    = Co_NULL;

    COGUI_EVENT_INIT(event, COGUI_EVENT_MOUSE_MOTION);

    /*win = GetTopWin(event->x, event->y);
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;*/
    cogui_send(event->app, event);

    //MouseMoveTo(event->x, event->y);
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

    switch (event->type)
    {
	case COGUI_EVENT_APP_CREATE:
    case COGUI_EVENT_APP_DELE:
		result = cogui_ack(event, E_OK);
		break;

    case COGUI_EVENT_PAINT:
        result = cogui_send(event->sender, event);
        break;
		
    /* mouse and keyboard event */
    case COGUI_EVENT_MOUSE_BUTTON:
        /* handle mouse button */
		
        //cogui_server_event_handler_mouse_btn((struct cogui_event_mouse *)event);
        break;

    case COGUI_EVENT_MOUSE_MOTION:
        /* handle mouse motion event */
		
        //cogui_server_event_handler_mouse_motion((struct cogui_event_mouse *)event);
        break;

    case COGUI_EVENT_WINDOW_CLOSE:
    case COGUI_EVENT_WINDOW_HIDE:
    {
        if (COGUI_WINDOW_IS_ENABLE(event->win)) {
            result = GUI_E_ERROR;
        }

        result = cogui_window_show(server_app->win);    
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

cogui_app_t *cogui_get_server(void)
{
    return server_app;
}

void cogui_server_init(void)
{
    CoCreateTask(cogui_server_entry, (void *)0, 15,&server_Stk[TASK_STK_SIZE-1], TASK_STK_SIZE);
}

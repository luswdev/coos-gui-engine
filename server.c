/**
 *******************************************************************************
 * @file       server.c
 * @version    V0.0.1   
 * @date       2019.5.19
 * @brief      The server for gui engine.	
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "cogui.h"

/*---------------------------- Define  ---------------------------------------*/
#define TASK_STK_SIZE		128	/*!< Define stack size.	              */

/*---------------------------- Variable declare ------------------------------*/
cogui_app_t *server_app = Co_NULL;

OS_STK   server_Stk[TASK_STK_SIZE];	     /*!< Stack of 'task_init' task.      */

//void SHandlerMonitorAdd();
//void SHandlerMonitorRemove();

/**
 *******************************************************************************
 * @brief      Handle mouse button event
 * @param[in]  event        mouse event
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to handle a mouse button event
 *******************************************************************************
 */
void cogui_server_handler_mouse_btn(struct cogui_event_mouse *event)
{
    /* the topwin contains current mouse */
    //P_TopWin win    = Co_NULL;

    COGUI_EVENT_INIT(&event.parent, COGUI_EVENT_MOUSE_BUTTON);

    /* set cursor position */
    //MouseSetPos(event->x, event->y);

    /*win = GetTopWin(event->x, event->y);
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;*/

    while(cogui_send(event->app, &event.parent) != E_OK){
        CoTickDelay(50);
    }
}

/**
 *******************************************************************************
 * @brief      Handle mouse motion event
 * @param[in]  event        mouse event
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to handle a mouse motion event
 *******************************************************************************
 */
void cogui_server_handler_mouse_motion(struct cogui_event_mouse *event)
{
    /* the topwin contains current mouse */
    //P_TopWin win    = Co_NULL;

    COGUI_EVENT_INIT(&event.parent, COGUI_EVENT_MOUSE_MOTION);

    /*win = GetTopWin(event->x, event->y);
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;*/
    cogui_send(event->app, &event.parent);

    //MouseMoveTo(event->x, event->y);
}

/**
 *******************************************************************************
 * @brief      Handle keyboard event
 * @param[in]  event        keyboard event
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to handle a keyboard event
 *******************************************************************************
 */
void cogui_server_event_kbd(struct cogui_event_kbd *event)
{
    /* the topwin contains current mouse */
    //P_TopWin win = Co_NULL;

    COGUI_EVENT_INIT(&event.parent, COGUI_EVENT_KBD);

    /*win = GetTopWinFocus();
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;*/

    cogui_send(event->app, &event.parent);
}

/**
 *******************************************************************************
 * @brief      Server app handler
 * @param[in]  event        event to handle
 * @param[out] None
 * @retval     Co_FALSE     failed
 * @retval     Co_TRUE      success
 *
 * @par Description
 * @details    This function is server app handler function
 *******************************************************************************
 */
StatusType cogui_server_event_handler(struct GuiEvent *event)
{
    COGUI_ASSERT(event != Co_NULL);

    switch (event->type)
    {
	case COGUI_EVENT_APP_CREATE:
    case COGUI_EVENT_APP_DELE:
		cogui_ack(event, E_OK);
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

    case COGUI_EVENT_KBD:
        /* handle keyboard event */
		
        //cogui_server_event_handler_kbd((struct cogui_event_kbd *)event);
        break;

    default:
        return Co_FALSE;
    }

    return Co_TRUE;
}

/**
 *******************************************************************************
 * @brief      Start the server	 
 * @param[in]  parameter    some add on parameter
 * @param[out] None
 * @retval     None			 
 *
 * @par Description
 * @details    This function is called to start the server
 *******************************************************************************
 */
void cogui_server_entry(void *parameter)
{
    server_app = cogui_app_create("gui_server");
    if(server_app == Co_NULL){
        return;
    }

    server_app->handler = cogui_server_event_handler;

    cogui_app_run(server_app);

    cogui_app_delete(server_app);
    server_app = Co_NULL;
}

/**
 *******************************************************************************
 * @brief      post a event via server 
 * @param[in]  event        event ptr
 * @param[out] None
 * @retval     E_NOSYS      if cannot find server app
 * @retval     E_ERROR      if post failed
 * @retval     E_OK         if post success		 
 *
 * @par Description
 * @details    This function is called to post a event via server
 *******************************************************************************
 */
StatusType cogui_server_post_event(struct cogui_event *event)
{
    StatusType result;

    if (server_app != Co_NULL){
        result = cougui_send(server_pp, event);
    }
    else{
        result = E_NOSYS;
    }

    return result;
}

/**
 *******************************************************************************
 * @brief      Get server ptr 
 * @param[in]  None
 * @param[out] None
 * @retval     serverApp    Current server ptr			 
 *
 * @par Description
 * @details    This function is called to get server ptr
 *******************************************************************************
 */
cogui_app_t *GetServer(void)
{
    return server_app;
}


void ServerInit(void)
{
	printf("Create a task \"server_entry\"...\r\n");
    CoCreateTask(cogui_server_entry, (void *)0, 15,&server_Stk[TASK_STK_SIZE-1], TASK_STK_SIZE);
	printf("[OK]\r\n");
	CoExitTask();
}

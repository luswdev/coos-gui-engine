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
P_GuiApp serverApp = Co_NULL;

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
void SHandlerMouseBtn(struct eventMouse *event)
{
    /* the topwin contains current mouse */
    //P_TopWin win    = Co_NULL;

    GUI_EVENT_INIT((struct GuiEvent *)event, GUI_EVENT_MOUSE_BUTTON, serverApp);

    /* set cursor position */
    //MouseSetPos(event->x, event->y);

    /*win = GetTopWin(event->x, event->y);
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;*/

    while(GuiSend(event->app, (struct GuiEvent *)event) != E_OK){
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
void SHandlerMouseMotion(struct eventMouse *event)
{
    /* the topwin contains current mouse */
    //P_TopWin win    = Co_NULL;

    GUI_EVENT_INIT((struct GuiEvent *)event, GUI_EVENT_MOUSE_MOTION, serverApp);

    /*win = GetTopWin(event->x, event->y);
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;*/
    GuiSend(event->app, (struct GuiEvent *)event);

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
void SHandlerKbd(struct eventKbd *event)
{
    /* the topwin contains current mouse */
    //P_TopWin win = Co_NULL;

    GUI_EVENT_INIT((struct GuiEvent *)event, GUI_EVENT_KBD, serverApp);

    /*win = GetTopWinFocus();
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;*/

    GuiSend(event->app, (struct GuiEvent *)event);
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
StatusType SEventHandler(struct GuiEvent *event)
{
    if(event==Co_NULL){
        return Co_FALSE;
    }
		
		printf("[guiServer]Handle a event, type no.%d\n", (int)event->type);

    switch (event->type)
    {
		case GUI_EVENT_APP_CREATE:
    case GUI_EVENT_APP_DELE:
				printf("[guiServer]Handle app function\n");
				GuiAck(event, E_OK);
				break;
		
    /* mouse and keyboard event */
    case GUI_EVENT_MOUSE_BUTTON:
        /* handle mouse button */
				printf("[guiServer]Handle mouse button\n");
		
        //SHandlerMouseBtn((struct eventMouse *)event);
        break;

    case GUI_EVENT_MOUSE_MOTION:
        /* handle mouse motion event */
				printf("[guiServer]Handle mouse motion\n");
		
        //SHandlerMouseMotion((struct eventMouse *)event);
        break;

    case GUI_EVENT_KBD:
        /* handle keyboard event */
				printf("[guiServer]Handle keyboard event\n");
		
        //SHandlerKbd((struct eventKbd *)event);
        break;

    default:
				printf("[guiServer]bad event\n");
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
void ServerEntry(void *parameter)
{
    serverApp = CreateApp("guiServer");
    if(serverApp == Co_NULL){
        printf("[server]Create app failed.\n");
        return;
    }

    serverApp->handler = SEventHandler;

    RunApp(serverApp);

    DeleteApp(serverApp);
    serverApp = Co_NULL;
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
StatusType ServerPostEvent(struct GuiEvent *event)
{
    StatusType result;

    if (serverApp != Co_NULL){
        result = GuiSend(serverApp, event);
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
P_GuiApp GetServer(void)
{
    return serverApp;
}


void ServerInit(void)
{
		printf("Create a task \"ServerEntry\"...\n");
    CoCreateTask(ServerEntry, 0, 10,&server_Stk[TASK_STK_SIZE-1], TASK_STK_SIZE);
	
		CoExitTask();
}

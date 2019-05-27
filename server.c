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

/*---------------------------- Variable declare ------------------------------*/
P_GuiApp serverApp = Co_NULL;


void SHandlerMonitorAdd();
void SHandlerMonitorRemove();

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
    P_TopWin win    = RT_NULL;

    GUI_EVENT_INIT(event, GUI_EVENT_MOUSE_BUTTON);

    /* set cursor position */
    MouseSetPos(event->x, event->y);

    win = GetTopWin(event->x, event->y);
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;

    while(GuiSend(event->app, event) != E_OK){
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
    P_TopWin win    = RT_NULL;

    GUI_EVENT_INIT(event, GUI_EVENT_MOUSE_MOTION);

    win = GetTopWin(event->x, event->y);
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;
    GuiSend(event->app, event);

    MouseMoveTo(event->x, event->y);
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
    P_TopWin win    = RT_NULL;

    GUI_EVENT_INIT(event, GUI_EVENT_KBD);

    win = GetTopWinFocus();
    if(win == Co_NULL){
        return;
    }

    event->win = win->wid;

    GuiSend(event->app, event);
}

/**
 *******************************************************************************
 * @brief      Server app handler
 * @param[in]  event    event to handle
 * @param[out] None
 * @retval     None			 
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

    switch (event->type)
    {
    /* mouse and keyboard event */
    case GUI_EVENT_MOUSE_BUTTON:
        /* handle mouse button */
        SHandlerMouseBtn((struct eventMouse *)event);
        break;

    case GUI_EVENT_MOUSE_MOTION:
        /* handle mouse motion event */
        SHandlerMouseMotion((struct eventMouse *)event);
        break;

    case GUI_EVENT_KBD:
        /* handle mouse motion event */
        SHandlerKbd((struct eventKbd *)event);
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
void ServerEntry(void *parameter)
{
    serverApp = AppCreate("cogui");
    if(serverApp == RT_NULL)
    {
        return;
    }

    serverApp->handler = SEventHandler;

    RunApp(serverApp);

    DeleteApp(serverApp);
    serverApp = Co_NULL;
}

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
P_GuiApp GetServer()
{
    return serverApp;
}
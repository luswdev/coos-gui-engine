/**
 *******************************************************************************
 * @file       server.c
 * @version    V0.0.1   
 * @date       2019.5.19
 * @brief      The server for gui engine.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "GuiServer.h"
#include "GuiApp.h"
#include "GuiEvent.h"
#include "GuiMouse.h"

/*---------------------------- Variable declare ------------------------------*/
P_GuiApp serverApp = Co_NULL;


void SHandlerMonitorAdd();
void SHandlerMonitorRemove();

void SHandlerMouseBtn(struct eventMouse event)
{
    /* the topwin contains current mouse */
    P_TopWin win    = RT_NULL;

    GUI_EVENT_INIT(event);

    /* set cursor position */
    MouseSetPos(event->x, event->y);
}

void SHandlerMouseMotion();
void SHandlerKbd();

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

    RunApp(serverApp);

    DeleteApp(serverApp);
    serverApp = Co_NULL;
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
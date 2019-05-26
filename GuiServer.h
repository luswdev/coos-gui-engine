/**
 *******************************************************************************
 * @file       GuiServer.h
 * @version    V0.0.1   
 * @date       2019.5.23
 * @brief      The server for gui engine.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "GuiApp.h"
#include "GuiSystem.h"
#include "GuiWindow.h"

typedef struct topwin
{
    /* the window id */
    P_GuiWin *wid;

    /* which app belong */
    P_GuiApp *app;

}TopWin,*P_TopWin;


/*---------------------------- Function Define -------------------------------*/
void SHandlerMonitorAdd();
void SHandlerMonitorRemove();
void SHandlerMouseBtn(struct eventMouse *event);
void SHandlerMouseMotion(struct eventMouse *event);
void SHandlerKbd(struct eventKbd *event);

StatusType SEventHandler(struct GuiEvent *event);

void ServerEntry(void *parameter);
P_GuiApp GetServer();
/**
 *******************************************************************************
 * @file       GuiServer.h
 * @version    V0.0.1   
 * @date       2019.5.23
 * @brief      The server for gui engine.	
 *******************************************************************************
 */ 

#ifndef _GUI_SERVER_H
#define _GUI_SERVER_H

/*---------------------------- structure -------------------------------------*/
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

StatusType ServerPostEvent(struct GuiEvent *event);

void ServerEntry(void *parameter);
P_GuiApp GetServer();


#endif /* _GUI_SERVER_H */
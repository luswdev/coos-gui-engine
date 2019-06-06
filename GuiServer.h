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

/*---------------------------- Function Define -------------------------------*/
StatusType SEventHandler(struct GuiEvent *event);

StatusType ServerPostEvent(struct GuiEvent *event);

void ServerEntry(void *parameter);
P_GuiApp GetServer(void);

void ServerInit(void);

#endif /* _GUI_SERVER_H */

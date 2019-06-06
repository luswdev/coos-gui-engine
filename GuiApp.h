/**
 *******************************************************************************
 * @file       GuiApp.h
 * @version    V0.0.1   
 * @date       2019.5.18
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 */ 

#ifndef _GUI_APP_H
#define _GUI_APP_H

/*---------------------------- Include ---------------------------------------*/
#include <CoOS.h>
#include <OsTime.h>
#include <OsTask.h>

/*---------------------------- Variable Define -------------------------------*/
extern OSTCB    TCBTbl[CFG_MAX_USER_TASKS+SYS_TASK_NUM];
extern ECB  EventTbl[CFG_MAX_EVENT]; 

/*---------------------------- Function declare ------------------------------*/
P_GuiApp CreateApp(char *name);
void _InitApp(P_GuiApp app);
void DeleteApp(P_GuiApp app);

StatusType AppEventHandler(struct GuiEvent *event);

void RunApp(P_GuiApp app);
void ExitApp(P_GuiApp app, U16 code);
void CloseApp(P_GuiApp app);
void SleepApp(P_GuiApp app, U32 sleepTick);

P_GuiApp AppSelf(void);

#endif /* _GUI_APP_H */

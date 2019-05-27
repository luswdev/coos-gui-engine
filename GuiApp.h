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

enum appFlag
{
    GUI_APP_FLAG_EXITED  = 0x04,
    GUI_APP_FLAG_SHOWN   = 0x08,
    GUI_APP_FLAG_KEEP    = 0x80,
};


/*---------------------------- structure -------------------------------------*/
typedef struct App
{
    U8      id;
    U8      *name;

    enum appFlag flag;

    U16     refCnt;
    U16     exitCode;

    /* Task id */
    OS_TID tid;
    /* Message queue */
    OS_EventID   mq;

    U32     winCnt;
    /* window activate count */
    U32     winActiCnt;

    /* the event handler */
    StatusType (*handler)(struct GuiEvent *event);

    void    *userDate;
}GuiApp,*P_GuiApp;

extern OSTCB    TCBTbl[CFG_MAX_USER_TASKS+SYS_TASK_NUM];

/*---------------------------- Function declare ------------------------------*/
P_GuiApp CreateApp(U8 *name);
void _InitApp(P_GuiApp *app);
void DeleteApp(P_GuiApp *app);

void RunApp(P_GuiApp *app);
void ExitApp(P_GuiApp *app, U16 code);
void CloseApp(P_GuiApp *app);
void SleepApp(P_GuiApp *app, S32 sec);

P_GuiApp AppSelf();

#endif /* _GUI_APP_H */
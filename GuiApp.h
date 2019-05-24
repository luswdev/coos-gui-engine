/**
 *******************************************************************************
 * @file       GuiApp.h
 * @version    V0.0.1   
 * @date       2019.5.18
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include <CoOS.h>
#include <OsTime.h>
#include <OsTask.h>

typedef struct App
{
    U8      id;
    U8      *name;

    U16     refCnt;

    /* Task id */
    OS_TID tid;
    /* Message queue */
    P_QCB   mq;

    U32     winCnt;
    /* window activate count */
    U32     winActiCnt;

    void    *userDate;
}GuiApp,*P_GuiApp;

extern OSTCB    TCBTbl[CFG_MAX_USER_TASKS+SYS_TASK_NUM];

/*---------------------------- Function declare ------------------------------*/
P_GuiApp CreateApp(U8 *name);
void _InitApp(P_GuiApp *app);
void DeleteApp(P_GuiApp *app);

void RunApp(P_GuiApp *app);
void ExitApp(P_GuiApp *app);
void CloseApp(P_GuiApp *app);
void SleepApp(P_GuiApp *app, S32 sec);

P_GuiApp AppSelf();
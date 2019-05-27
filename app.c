/**
 *******************************************************************************
 * @file       app.c
 * @version    V0.0.1   
 * @date       2019.5.18
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "cogui.h"

/**
 *******************************************************************************
 * @brief      Initial a app	 
 * @param[in]  app     App ptr		
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to initial a app.
 *******************************************************************************
 */
void _InitApp(P_GuiApp app)
{
    app->name       = Co_NULL;
    app->refCnt     = 0;
    app->tid        = 0;
    app->mq         = Co_NULL;
    app->winCnt     = 0;
    app->winActiCnt = 0;
}

/**
 *******************************************************************************
 * @brief      Create a app	 
 * @param[in]  name     App title name		
 * @param[out] None
 * @retval     Co_NULL  Create app fail.
 * @retval     P_GuiApp Create app successful.			 
 *
 * @par Description
 * @details    This function is called to create a app.
 *******************************************************************************
 */
P_GuiApp CreateApp(U8 *name)
{
    P_GuiApp app;
    P_GuiApp srvApp;
    OS_TID tid = CoGetCurTaskID();
    struct eventApp *event;

    if(taskID == 0){                     /* Is idle task?                      */   											 
        return Co_NULL;                 /* Yes,error return                   */
    }

    if(title == Co_NULL){    
        return Co_NULL;
    }

    /* create application */
    app = GuiMalloc(sizeof(GuiApp));
    if (app == Co_NULL){    
        return Co_NULL;
    }
    
    _InitApp(app);

    app->tid = tid;

    /* set application title */
    app->name = title;

    /* create message queue */
    app->mq = CoCreateMbox(0)  /* FIFO */

    srvApp = GetServer();
    if(srvApp==Co_NULL){
        OSTCB[tid].userData = app;
        return app;
    }

    GUI_EVENT_INIT(&event, GUI_EVENT_APP_CREATE);
    event.app = app;

    if(GuiSend(srvApp, (struct GuiEvent)&event) == E_OK){
        OSTCB[tid].userData = app;
        return app;
    }

    GuiFree(app);    
    return RT_NULL;
}

/**
 *******************************************************************************
 * @brief      Delete a app	 
 * @param[in]  app   App ptr should delete		
 * @param[out] None
 * @retval     None			 
 *
 * @par Description
 * @details    This function is called to delete a app.
 *******************************************************************************
 */
void DeleteApp(P_GuiApp app)
{
    P_GuiApp serverApp;
    struct eventApp event;

    if(app == Co_NULL || app->tid == Co_NULL || app->mq == Co_NULL)
    {
        return;
    }

    GuiFree(app->name);
    app->name = Co_NULL
    CoDelMbox(app->mq, OPT_DEL_ANYWAY);
    TCBTbl[app->tid].userData=0;

    serverApp = GetServer();
    GUI_EVENT_INIT(&event, GUI_EVENT_APP_DESTROY);
    event.app = app;

    if(GuiSend(srvApp, (struct GuiEvent)&event) != E_OK){
        return;
    }

    GuiFree(app);
}

/**
 *******************************************************************************
 * @brief      Run a app loop
 * @param[in]  app   App ptr should run		
 * @param[out] None
 * @retval     None			 
 *
 * @par Description
 * @details    This function is called to run a app loop.
 *******************************************************************************
 */
void _appEventLoop(P_GuiApp app)
{
    StatusType result;
    U16 currentRef;
    struct GuiEvent *event;

    currentRef = ++app->refCnt;
    while (currentRef <= app->refCnt)
    {
        event = GuiRecv(app->mq, &result);
        if(result==E_OK){
            app->handler(event);
        }
    }
}

/**
 *******************************************************************************
 * @brief      Run a app	 
 * @param[in]  app   App ptr should run		
 * @param[out] None
 * @retval     None			 
 *
 * @par Description
 * @details    This function is called to run a app.
 *******************************************************************************
 */
void RunApp(P_GuiApp app)
{
    /* check whether app is exist */
    if (app == Co_NULL)
        return;

    /* check whether app's task is exist */
    if (app->tid == 0)
        return;

    /* check whether app's user data is exist */
    if (TCBTbl[app->tid].userData == 0)
        return;

    _appEventLoop(app);
}

/**
 *******************************************************************************
 * @brief      Exit a app	 
 * @param[in]  app   App ptr should exit		
 * @param[out] None
 * @retval     None			 
 *
 * @par Description
 * @details    This function is called to exit a app.
 *******************************************************************************
 */
void ExitApp(P_GuiApp app)
{
    if (app->refCnt == 0)
        return;
    
    app->refCnt--;
}

/**
 *******************************************************************************
 * @brief      Close a app	 
 * @param[in]  app   App ptr should close		
 * @param[out] None
 * @retval     None			 
 *
 * @par Description
 * @details    This function is called to close a app.
 *******************************************************************************
 
void CloseApp(P_GuiApp *app)
{

}*/

/**
 *******************************************************************************
 * @brief      Let a app sleep	 
 * @param[in]  app   App ptr should sleep
 * @param[in]  app   How long should the app sleep 		
 * @param[out] None
 * @retval     None			 
 *
 * @par Description
 * @details    This function is called to let a app sleep.
 *******************************************************************************
 */
void SleepApp(P_GuiApp *app, U32 sleepTick)
{
    /* check whether app is exist */
    if (app == Co_NULL)
        return;

    /* check whether app's task is exist */
    if (app->tid == Co_NULL)
        return;

    /* check whether app's user data is exist */
    if (app->userData == 0)
        return;

    InsertDelayList(app->tid, sleepTick);
}

P_GuiApp AppSelf()
{
    P_GuiApp app;
    OS_TID self;


    self = CoGetCurTaskID();
    app  = (P_GuiApp)TCBTbl[self].userData;

    return app;
}
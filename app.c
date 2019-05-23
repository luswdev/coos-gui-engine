/**
 *******************************************************************************
 * @file       app.c
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
#include "GuiApp.h"
#include "GuiSystem.h"

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
    P_GuiApp *app;
    OS_TID tid = CoGetCurTaskID();

    if(taskID == 0)                     /* Is idle task?                      */
    {											 
        return E_PROTECTED_TASK;        /* Yes,error return                   */
    }

    if(title == Co_NULL)
    {
        return E_TITLE_NULL;
    }

    /* create application */
    app = GuiMalloc(sizeof(GuiApp));
    if (app == Co_NULL)
    {
        return Co_NULL;
    }
    
    _InitApp(app);

    app->tid = tid;



    /* create message queue */
    //app->mq = CoCreateQueue

    /* set application title */
    //app->name = 

    return app;
}

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
void _InitApp(P_GuiApp *app)
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
    /* delete message queue */
    //


    GuiFree(app);
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
void RunApp(P_GuiApp *app)
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

    // run app here.
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
void ExitApp(P_GuiApp *app)
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
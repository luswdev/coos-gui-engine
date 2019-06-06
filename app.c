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
#include "stdio.h"
#include "string.h"

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
    app->mq         = 0;
    app->winCnt     = 0;
    app->winActiCnt = 0;
		app->handler    = AppEventHandler;
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
P_GuiApp CreateApp(char *title)
{
    P_GuiApp app;
    P_GuiApp srvApp;
    OS_TID tid = CoGetCurTaskID();
    struct eventApp event;

    if(tid == 0)
		{                     /* Is idle task?                      */   											 
        return Co_NULL;                 /* Yes,error return                   */
    }

    if(title == Co_NULL)
		{    
        return Co_NULL;
    }
    
    printf("creating a app name \"%s\" ...\n", title);

    /* create application */
    app = GuiMalloc(sizeof(GuiApp));
    if (app == Co_NULL)
		{    
        return Co_NULL;
    }
    
    _InitApp(app);

    app->tid = tid;

    /* set application title */
    app->name = GuiMalloc(sizeof(char)*(strlen(title)+1));
    strcpy(app->name,title);

    /* create message queue */
    app->mq = CoCreateMbox(EVENT_SORT_TYPE_FIFO);

    srvApp = GetServer();
    if(srvApp == Co_NULL)
		{
        TCBTbl[tid].userData = app;

        printf("[OK](this is the server app)\n");
        return app;
    }
		
    GUI_EVENT_INIT(&event.parent, GUI_EVENT_APP_CREATE, app);
    event.app = app;

    if(GuiSend(srvApp, &event.parent) == E_OK)
		{
        TCBTbl[tid].userData = app;

        printf("[OK] ptr=0x%p\n",app);
        return app;
    }

    GuiFree(app);

    printf("[Failed]\n");    
    return Co_NULL;
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

    if(app == Co_NULL || app->tid == 0 || app->mq == 0)
		{
        return;
    }

    printf("Deleting app \"%s\", ptr=0x%p\n", app->name, app);

    GuiFree(app->name);
    app->name = Co_NULL;
		
    CoDelMbox(app->mq, OPT_DEL_ANYWAY);
    TCBTbl[app->tid].userData=0;
		
    serverApp = GetServer();
    GUI_EVENT_INIT(&event.parent, GUI_EVENT_APP_DELE, app);
		
		printf("Initial event done, sender ptr=%p\n", event.parent.sender);
		
    event.app = app;

    if(GuiSend(serverApp, &event.parent) != E_OK)
		{	
       return;
    }
		
		GuiFree(app);
}

StatusType AppEventHandler(struct GuiEvent *event)
{
		if(event==Co_NULL)
		{
        return Co_FALSE;
    }
		
		printf("[%s]Handle a event, type no.%d\n", AppSelf()->name,(int)event->type);
		
		switch (event->type)
    {
			case GUI_EVENT_APP_DELE:
					ExitApp(((struct eventApp *)event)->app, 0);\
					break;
				
			default:
				printf("[%s]bad event\n", AppSelf()->name);
        return Co_FALSE;
				
		}
		
		return Co_TRUE;
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
    while(currentRef <= app->refCnt)
    {
        event = GuiRecv(app->mq, &result);
        if(result==E_OK)
				{
            printf("[%s]Recive a event.\n", app->name);

            app->handler(event);
						printf("[%s]Handle over\n", app->name);
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
		{
				return;
		}
        

    /* check whether app's task is exist */
    if (app->tid == 0)
		{
        return;
		}

    /* check whether app's user data is exist */
    if (TCBTbl[app->tid].userData == 0)
		{
        return;
		}

    printf("[%s]starting app...\n", app->name);
    _appEventLoop(app);
	  printf("[%s]runing time over.\n", app->name);
}

/**
 *******************************************************************************
 * @brief      Exit a app	 
 * @param[in]  app   App ptr should exit		
 * @param[in]  code  exit code		
 * @param[out] None
 * @retval     None			 
 *
 * @par Description
 * @details    This function is called to exit a app.
 *******************************************************************************
 */
void ExitApp(P_GuiApp app, U16 code)
{
    if (app->refCnt == 0)
		{
        return;
		}
		
		printf("Exiting app name \"%s\", code %d\n", app->name, code);
    
    app->refCnt--;
    app->exitCode = code;
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
 */
void CloseApp(P_GuiApp app)
{
		struct eventApp event;

    GUI_EVENT_INIT(&event.parent, GUI_EVENT_APP_DELE, AppSelf());
    event.app = app;

    GuiSend(app, &event.parent);
}

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
void SleepApp(P_GuiApp app, U32 sleepTick)
{
    /* check whether app is exist */
    if (app == Co_NULL)
		{
        return;
		}

    /* check whether app's task is exist */
    if (app->tid == 0)
		{
        return;
		}

    /* check whether app's user data is exist */
    if (app->userData == 0)
		{
        return;
		}

    CoTickDelay(sleepTick);
}

/**
 *******************************************************************************
 * @brief      get current app ptr	 
 * @param[in]  app   App ptr should sleep
 * @param[in]  app   How long should the app sleep 		
 * @param[out] None
 * @retval     app   current app ptr			 
 *
 * @par Description
 * @details    This function is called to let a app sleep.
 *******************************************************************************
 */
P_GuiApp AppSelf(void)
{
    P_GuiApp app;
    OS_TID self;


    self = CoGetCurTaskID();
    app  = (P_GuiApp)TCBTbl[self].userData;

    return app;
}

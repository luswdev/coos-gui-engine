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
void _cogui_app_init(cogui_app_t *app)
{
    app->name         = Co_NULL;
    app->refCnt       = 0;
    app->tid          = 0;
    app->mq           = 0;
    app->win_cnt      = 0;
    app->win_acti_cnt = 0;
	app->handler      = cogui_app_event_handler;
}

/**
 *******************************************************************************
 * @brief      Create a app	 
 * @param[in]  name     App title name		
 * @param[out] None
 * @retval     Co_NULL  Create app fail.
 * @retval     cogui_app_t *Create app successful.			 
 *
 * @par Description
 * @details    This function is called to create a app.
 *******************************************************************************
 */
cogui_app_t *cogui_app_create(char *title)
{
    cogui_app_t *app;
    cogui_app_t *srv_app;
    OS_TID tid = CoGetCurTaskID();
    struct cogui_event_app event;

    COGUI_ASSERT(tid != 0); /* Is idle task? */
    COGUI_ASSERT(title != Co_NULL);

    /* create application */
    app = cogui_malloc(sizeof(cogui_app_t));
    if (app == Co_NULL)
        return Co_NULL;
    
    _cogui_app_init(app);

    app->tid = tid;

    /* set application title */
    app->name = cogui_malloc(sizeof(char)*(strlen(title)+1));
    strcpy(app->name,title);

    /* create message queue */
    app->mq = CoCreateMbox(EVENT_SORT_TYPE_FIFO);

    srv_app = cogui_get_server();
    if(srv_app == Co_NULL) {
        TCBTbl[tid].userData = app;
        return app;
    }
		
    COGUI_EVENT_INIT(&event.parent, COGUI_EVENT_APP_CREATE);
    event.app = app;

    if(cogui_send(srv_app, &event.parent) == E_OK) {
        TCBTbl[tid].userData = app;
        return app;
    }

    cogui_free(app);
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
void cogui_app_delete(cogui_app_t *app)
{
    cogui_app_t *srv_app;
    struct cogui_event_app event;

    COGUI_ASSERT(app != Co_NULL);
    COGUI_ASSERT(app->tid);
    COGUI_ASSERT(app->mq);

    cogui_free(app->name);
    app->name = Co_NULL;
		
    CoDelMbox(app->mq, OPT_DEL_ANYWAY);
    TCBTbl[app->tid].userData = 0;
		
    srv_app = GetServer();
    COGUI_EVENT_INIT(&event.parent, COGUI_EVENT_APP_DELE);
    event.app = app;

    if(cogui_send(srv_app, &event.parent) != E_OK)
       return;
		
	cogui_free(app);
}

StatusType cogui_app_event_handler(struct GuiEvent *event)
{
	COGUI_ASSERT(event != Co_NULL);

	switch (event->type)
    {
	case COGUI_EVENT_APP_DELE:
		cogui_app_exit(((struct cogui_event_app *)event)->app, 0);
		break;
				
	default:
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
void _cogui_app_event_loop(cogui_app_t *app)
{
    StatusType result;
    U16 current_ref;
    struct cogui_event *event;

    current_ref = ++app->ref_cnt;
    while(current_ref <= app->ref_cnt) {
        event = cogui_recv(app->mq, &result);
        if(result == E_OK) {
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
void cogui_app_run(cogui_app_t *app)
{
    COGUI_ASSERT(app != Co_NULL);
    COGUI_ASSERT(app->tid);
    COGUI_ASSERT(TCBTbl[app->tid].userData);

    _cogui_app_event_loop(app);
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
void cogui_app_exit(cogui_app_t *app, U16 code)
{
    if (app->ref_cnt == 0)
        return;
    
    app->ref_cnt--;
    app->exit_code = code;
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
void cogui_app_close(cogui_app_t *app)
{
	struct eventApp event;

    GUI_EVENT_INIT(&event.parent, GUI_EVENT_APP_DELE);
    event.app = app;

    cogui_send(app, &event.parent);
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
void cogui_app_sleep(cogui_app_t *app, U32 sleep_tick)
{
    COGUI_ASSERT(app != Co_NULL);
    COGUI_ASSERT(app->tid);
    COGUI_ASSERT(app->user_data);

    CoTickDelay(sleep_tick);
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
cogui_app_t *cogui_app_self(void)
{
    cogui_app_t *app;
    OS_TID self;


    self = CoGetCurTaskID();
    app  = (cogui_app_t *)TCBTbl[self].userData;

    return app;
}

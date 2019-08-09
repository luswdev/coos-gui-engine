/**
 *******************************************************************************
 * @file       app.c
 * @version    V0.0.2 
 * @date       2019.8.9
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"
#include "stdio.h"
#include "string.h"

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

cogui_app_t *cogui_app_create(char *title)
{
    cogui_app_t *app;
    cogui_app_t *srv_app;
    OS_TID tid = CoGetCurTaskID();
    struct cogui_event_app event;

    COGUI_ASSERT(tid != 0);
    COGUI_ASSERT(title != Co_NULL);

    app = cogui_malloc(sizeof(cogui_app_t));
    if (app == Co_NULL)
        return Co_NULL;
    
    _cogui_app_init(app);

    app->tid = tid;

    app->name = cogui_malloc(sizeof(char)*(strlen(title)+1));
    strcpy(app->name,title);

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

void cogui_app_run(cogui_app_t *app)
{
    COGUI_ASSERT(app != Co_NULL);
    COGUI_ASSERT(app->tid);
    COGUI_ASSERT(TCBTbl[app->tid].userData);

    _cogui_app_event_loop(app);
}

void cogui_app_exit(cogui_app_t *app, U16 code)
{
    if (app->ref_cnt == 0)
        return;
    
    app->ref_cnt--;
    app->exit_code = code;
}

void cogui_app_close(cogui_app_t *app)
{
	struct eventApp event;

    GUI_EVENT_INIT(&event.parent, GUI_EVENT_APP_DELE);
    event.app = app;

    cogui_send(app, &event.parent);
}

void cogui_app_sleep(cogui_app_t *app, U32 sleep_tick)
{
    COGUI_ASSERT(app != Co_NULL);
    COGUI_ASSERT(app->tid);
    COGUI_ASSERT(app->user_data);

    CoTickDelay(sleep_tick);
}

cogui_app_t *cogui_app_self(void)
{
    cogui_app_t *app;
    OS_TID self;


    self = CoGetCurTaskID();
    app  = (cogui_app_t *)TCBTbl[self].userData;

    return app;
}

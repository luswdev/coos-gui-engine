/**
 *******************************************************************************
 * @file       app.c
 * @version    V0.1.1
 * @date       2020.01.04
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 */ 

#include <cogui.h>

cogui_window_t *main_page       = Co_NULL;

StatusType cogui_app_event_handler(struct cogui_event *event);

void _cogui_app_init(cogui_app_t *app)
{
    cogui_memset(app, 0, sizeof(cogui_app_t));

	app->handler      = cogui_app_event_handler;
	app->optional_handler      = Co_NULL;
}

cogui_app_t *cogui_app_create(char *title)
{
    cogui_app_t *app;
    cogui_app_t *srv_app;
    OS_TID tid = CoGetCurTaskID();
    struct cogui_event event;

    COGUI_ASSERT(tid != 0);
    COGUI_ASSERT(title != Co_NULL);

    app = cogui_malloc(sizeof(cogui_app_t));
    if (app == Co_NULL)
        return Co_NULL;
    
    _cogui_app_init(app);

    app->tid = tid;

    app->name = cogui_strdup((char *)title);

    app->mq = CoCreateMbox(EVENT_SORT_TYPE_PRIO);

    srv_app = cogui_get_server();
    if(srv_app == Co_NULL) {
        TCBTbl[tid].userData = app;
        return app;
    }
		
    COGUI_EVENT_INIT(&event, COGUI_EVENT_APP_CREATE);
    event.app = app;

    if(cogui_send_sync(srv_app, &event) == E_OK) {
        TCBTbl[tid].userData = app;
        return app;
    }

    cogui_free(app);
    return Co_NULL;
}

void cogui_app_delete(cogui_app_t *app)
{
    cogui_app_t *srv_app;
    struct cogui_event event;

    COGUI_ASSERT(app != Co_NULL);
    COGUI_ASSERT(app->tid);
    COGUI_ASSERT(app->mq);

    cogui_free(app->name);
    app->name = Co_NULL;
		
    CoDelMbox(app->mq, OPT_DEL_ANYWAY);
    TCBTbl[app->tid].userData = 0;
		
    srv_app = cogui_get_server();
    COGUI_EVENT_INIT(&event, COGUI_EVENT_APP_DELE);
    event.app = app;

    if(cogui_send_sync(srv_app, &event) != E_OK) {
       return;
    }
		
	cogui_free(app);
}

StatusType cogui_app_event_handler(struct cogui_event *event)
{
	COGUI_ASSERT(event != Co_NULL);

    cogui_printf("[%10s] Got event #%d.\r\n", cogui_app_self()->name, event->type);

	switch (event->type)
    {
	case COGUI_EVENT_APP_DELE:
		cogui_app_exit((event)->app, 0);
		break;

	case COGUI_EVENT_PAINT:
        if (cogui_app_self()->optional_handler != Co_NULL) {
            cogui_app_self()->optional_handler(event);
            break;
        }
        else 
            return Co_FALSE;

	default:
		return Co_FALSE;
				
	}
		
	return Co_TRUE;
}

static void _cogui_app_event_loop(cogui_app_t *app)
{
    StatusType  result;
    co_uint16_t current_ref;
    co_int32_t loop_cnt = 0;
    struct cogui_event *event;

    event = (struct cogui_event *)app->event_buffer;

    current_ref = ++app->ref_cnt;
    while(current_ref <= app->ref_cnt) {
        cogui_printf("[%10s] App event loop #%d.\r\n", app->name, loop_cnt++);
        result = cogui_recv(app->mq, event, 0);

        if(result == E_OK && event != Co_NULL) {
            cogui_printf("[%10s] Got a event no.%d\r\n", app->name, event->type);
            app->handler(event);
        }
    }
}

void cogui_app_run(cogui_app_t *app)
{
    COGUI_ASSERT(app != Co_NULL);
    COGUI_ASSERT(app->tid);
    COGUI_ASSERT(TCBTbl[app->tid].userData);

    if (app != cogui_get_server()){
        struct cogui_event event;
        COGUI_EVENT_INIT(&event, COGUI_EVENT_PAINT);
        event.app = app;

        cogui_send(cogui_get_server(), &event);
    }
    else {
        cogui_printf("[%10s] Create main window.\r\n", cogui_app_self()->name);
        main_page = cogui_main_window_create();
    }

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
	struct cogui_event event;

    COGUI_EVENT_INIT(&event, COGUI_EVENT_APP_DELE);
    event.app = app;

    cogui_send(app, &event);
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

/**
 *******************************************************************************
 * @file       app.c
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 */ 

#include <cogui.h>

cogui_window_t *main_page       = Co_NULL;

static StatusType cogui_app_event_handler(struct cogui_event *event);

/**
 *******************************************************************************
 * @brief      Initial application structure.
 * @param[in]  *app    Application structure pointer
 * @param[out] None
 * @retval     None 
 *******************************************************************************
 */
void _cogui_app_init(cogui_app_t *app)
{
    /* set all feild to zero first */
    cogui_memset(app, 0, sizeof(cogui_app_t));

    /* set app default event handler */
	app->handler = cogui_app_event_handler;
}

/**
 *******************************************************************************
 * @brief      Create a application
 * @param[in]  *title    How do we call this application.
 * @param[out] None
 * @retval     *app      The created application pointer. 
 * @retval     Co_NULL   If sync to server failed.
 *******************************************************************************
 */
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

    /* filled meta data */
    app->tid = tid;
    app->name = cogui_strdup((char *)title);
    app->mq = CoCreateMbox(EVENT_SORT_TYPE_FIFO);

    srv_app = cogui_get_server();
    if(srv_app == Co_NULL) {
        TCBTbl[tid].userData = app;     /* if we are creating server, just return here */
        return app;
    }
	
    /* if server is already created, sync with it */
    COGUI_EVENT_INIT(&event, COGUI_EVENT_APP_CREATE);
    event.app = app;

    /* if server ack OK, return here */
    if(cogui_server_post_event_sync(&event) == GUI_E_OK) {
        TCBTbl[tid].userData = app;
        return app;
    }

    /* if server not ack OK, free pointer and return Co_NULL */
    cogui_free(app);
    return Co_NULL;
}

/**
 *******************************************************************************
 * @brief      Delete a application
 * @param[in]  *app    Applicate to delete.
 * @param[out] None
 * @retval     None
 *******************************************************************************
 */
void cogui_app_delete(cogui_app_t *app)
{
    COGUI_ASSERT(app != Co_NULL);
    COGUI_ASSERT(app->tid);
    COGUI_ASSERT(app->mq);

    cogui_app_t *srv_app;
    struct cogui_event event;

    /* free application name buffer */
    cogui_free(app->name);
    app->name = Co_NULL;
	
    /* free event buffer */
    CoDelMbox(app->mq, OPT_DEL_ANYWAY);
    TCBTbl[app->tid].userData = 0;
	
    /* we should sync to server */
    srv_app = cogui_get_server();
    COGUI_EVENT_INIT(&event, COGUI_EVENT_APP_DELE);
    event.app = app;

    /* if server not ack OK, just return */
    if(cogui_send_sync(srv_app, &event) != GUI_E_OK) {
       return;
    }
	
    /* if server ack OK, free application buffer */
	cogui_free(app);
}

/**
 *******************************************************************************
 * @brief      Application running loop.
 * @param[in]  *app       Application pointer which should run.
 * @param[out] None
 * @retval     None
 *******************************************************************************
 */
static void _cogui_app_event_loop(cogui_app_t *app)
{
    StatusType  result;
    uint16_t current_ref;
    //uint8_t loop=0;
    struct cogui_event *event;

    event = (struct cogui_event *)app->event_buffer;

    current_ref = ++app->ref_cnt;
    while(current_ref <= app->ref_cnt) {
        //cogui_printf("[%s] App event loop #%d\r\n", app->name, loop++);
        result = cogui_recv(app->mq, event, 0);

        if(result == GUI_E_OK && event != Co_NULL) {
            //cogui_printf("[%s] Got a event no.%d\r\n", app->name, event->type);
            app->handler(event);
        }
    }
}

void cogui_app_run(cogui_app_t *app)
{
    COGUI_ASSERT(app != Co_NULL);
    COGUI_ASSERT(app->tid);
    COGUI_ASSERT(TCBTbl[app->tid].userData);

    if (app == cogui_get_server()){
        main_page = cogui_main_window_create();
    } else {
        app->win_id = cogui_main_page_app_install(app->name);
        cogui_window_refresh(main_page);
    }

    cogui_printf("[%s] app start loops.\r\n", app->name);
    _cogui_app_event_loop(app);
}

void cogui_app_exit(cogui_app_t *app, uint16_t code)
{
    if (app->ref_cnt == 0) {
        return;
    }
    
    app->ref_cnt--;
    app->exit_code = code;
}

StatusType cogui_app_close(cogui_app_t *app)
{
	struct cogui_event event;

    COGUI_EVENT_INIT(&event, COGUI_EVENT_APP_DELE);
    event.app = app;

    return cogui_send(app, &event);
}

void cogui_app_sleep(cogui_app_t *app, uint32_t sleep_tick)
{
    COGUI_ASSERT(app != Co_NULL);
    COGUI_ASSERT(app->tid);
    COGUI_ASSERT(app->user_data);

    CoTickDelay(sleep_tick);
}

/**
 *******************************************************************************
 * @brief      Get current application.
 * @param[in]  None
 * @param[out] None
 * @retval     *app      Current application pointer.
 *******************************************************************************
 */
cogui_app_t *cogui_app_self(void)
{
    cogui_app_t *app;
    OS_TID self;

    /* get current application in TCBTbl */
    self = CoGetCurTaskID();
    app  = (cogui_app_t *)TCBTbl[self].userData;

    return app;
}

/**
 *******************************************************************************
 * @brief      Default application event handler.
 * @param[in]  *event           Event buffer we get.
 * @param[out] None
 * @retval     GUI_E_OK         Handle event successfully.
 * @retval     GUI_E_ERROR      Occured some error while handle event.
 *******************************************************************************
 */
static StatusType cogui_app_event_handler(struct cogui_event *event)
{
	COGUI_ASSERT(event != Co_NULL);

    StatusType result = GUI_E_ERROR;

    //cogui_printf("[%s] Got a event no.%d\r\n", cogui_app_self(), event->type);

	switch (event->type)
    {
	case COGUI_EVENT_APP_DELE:
		cogui_app_exit((event)->app, 0);
        result = GUI_E_OK;
		break;

	case COGUI_EVENT_PAINT:
        if (cogui_app_self()->win) {
            cogui_window_show(cogui_app_self()->win);
        } else if (cogui_app_self()->optional_handler != Co_NULL) {
            result = cogui_app_self()->optional_handler(event);
        } else {
            result = GUI_E_ERROR;
        }
        cogui_mouse_show();
        break;
    
    /* mouse and keyboard event */
    case COGUI_EVENT_MOUSE_BUTTON:
    {
        cogui_point_t cursor_pt;
        cogui_app_t *eapp = cogui_app_self();
        cogui_window_t *ewin = eapp->win;
        cogui_widget_t *ewgt, *last_ewgt = ewin->last_mouse_event_widget;;
        cogui_mouse_get_position(&cursor_pt);
        ewgt = cogui_window_get_mouse_event_widget(ewin, cursor_pt.x, cursor_pt.y);

        if (ewgt != Co_NULL) {
            if (event->button & COGUI_MOUSE_BUTTON_DOWN) {
                cogui_widget_focus(ewgt);
                cogui_mouse_show();
            } else {
                if (ewgt->flag & COGUI_WIDGET_FLAG_TITLE) {
                    if (ewgt->flag & COGUI_WIDGET_FLAG_CLOSE_BTN && last_ewgt == ewgt) {
                        cogui_window_close(ewin);
                    } else if (ewgt->flag & COGUI_WIDGET_FLAG_MINI_BTN && last_ewgt == ewgt) {
                        cogui_window_hide(ewin);
                    }
                } else if (last_ewgt == ewgt && eapp->optional_handler != Co_NULL) {
                    COGUI_EVENT_INIT(event, COGUI_EVENT_MOUSE_CLICK);
                    event->widget = ewgt;
                    result = eapp->optional_handler(event);
                    cogui_mouse_show();
                } else {
                    cogui_mouse_show();
                }
            }
        }
        break;
    }

	default:
		result = GUI_E_ERROR;	
	}
		
	return result;
}

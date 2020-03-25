/**
 *******************************************************************************
 * @file       app.c
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 */ 

#include <cogui.h>

window_t *main_page       = Co_NULL;
static StatusType app_event_handler(struct event *event);

/**
 *******************************************************************************
 * @brief      Initial application structure.
 * @param[in]  *app    Application structure pointer
 * @param[out] None
 * @retval     None 
 *******************************************************************************
 */
void _app_init(app_t *app)
{
    cogui_memset(app, 0, sizeof(app_t));     /* set all feild to zero first   */
	app->handler = app_event_handler;        /* set app default event handler */
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
app_t *gui_app_create(char *title)
{
    ASSERT(title != Co_NULL);

    app_t *app;
    app_t *srv_app;
    OS_TID tid = CoGetCurTaskID();
    struct event event;

    ASSERT(tid != 0);

    app = gui_malloc(sizeof(app_t));
    if (app == Co_NULL) {
        return Co_NULL;     /* if malloc failed, return Co_NULL               */
    }
    
    _app_init(app);         /* first initial structure data to zero           */

    app->tid = tid;         /* filled meta data                               */
    app->name = gui_strdup((char *)title);   /* record application name       */
    app->mq = CoCreateMbox(EVENT_SORT_TYPE_FIFO); /* create a mailbox 
                                                                    for event */
    srv_app = gui_get_server();     /* check if server created or not         */
    if (srv_app == Co_NULL) {
        TCBTbl[tid].userData = app;     /* put app pointer to TCBTbl userData */
        return app;     /* if we are creating server, just return here        */
    }
	
    EVENT_INIT(&event, EVENT_APP_CREATE);     
    event.app = app;            /* if server is already created, sync with it */
    
    if (gui_server_post_event_sync(&event) == GUI_E_OK) {
        TCBTbl[tid].userData = app;     /* put app pointer to TCBTbl userData */             
        return app;            /* if server ack OK, return here               */
    }

    gui_free(app);   /* if server not ack OK, free pointer and return Co_NULL */
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
void gui_app_delete(app_t *app)
{
    ASSERT(app != Co_NULL);
    ASSERT(app->tid);
    ASSERT(app->mq);

    struct event event;

    gui_free(app->name);        /* free application name buffer               */
    app->name = Co_NULL;
    
    CoDelMbox(app->mq, OPT_DEL_ANYWAY);     /* free event buffer              */
    TCBTbl[app->tid].userData = 0;
	
    EVENT_INIT(&event, EVENT_APP_DELE);     /* we should sync to server       */
    event.app = app;

    if (gui_server_post_event_sync(&event) != GUI_E_OK) {
       return;              /* if server not ack OK, just return              */
    }
	
	gui_free(app);          /* if server ack OK, free application buffer      */
}

/**
 *******************************************************************************
 * @brief      Application running loop.
 * @param[in]  *app       Application pointer which should run.
 * @param[out] None
 * @retval     None
 *******************************************************************************
 */
static void _app_event_loop(app_t *app)
{
    StatusType  result;
    uint16_t current_ref;
    struct event *event;

    event = (struct event *)app->event_buffer;  /* set event buffer for recv  */

    current_ref = ++app->ref_cnt;
    while (current_ref <= app->ref_cnt) {
        result = gui_recv(app->mq, event, 0);   /* recv event WAIT FOREVER    */
        if (result == GUI_E_OK && event != Co_NULL) {
            app->handler(event);     /* call event handler if recv currently  */
        }
    }
}

/**
 *******************************************************************************
 * @brief      Run a application.
 * @param[in]  *app       Application pointer which should run.
 * @param[out] None
 * @retval     None
 *******************************************************************************
 */
void gui_app_run(app_t *app)
{
    ASSERT(app != Co_NULL);
    ASSERT(app->tid);
    ASSERT(TCBTbl[app->tid].userData);

    if (app == gui_get_server()){           /* create main window if it       */
        main_page = gui_main_window_create();           /* is server running  */
    } else {
        app->win_id = gui_main_page_app_install(app->name); /* install app if */
        gui_window_refresh(main_page);              /* it is user app running */
    }

    _app_event_loop(app);       /* then run loop while everythings done       */
}

/**
 *******************************************************************************
 * @brief      Exit a application.
 * @param[in]  *app       Application pointer which should exit.
 * @param[in]  code       Application exit code.
 * @param[out] None
 * @retval     None
 *******************************************************************************
 */
void gui_app_exit(app_t *app, uint16_t code)
{
    if (app->ref_cnt == 0) {
        return;
    }
    
    app->ref_cnt--;         /* minor reference count to kill loops            */
    app->exit_code = code;
}

/**
 *******************************************************************************
 * @brief      Close a application.
 * @param[in]  *app       Application pointer which should close.
 * @param[out] None
 * @retval     None
 *******************************************************************************
 */
StatusType gui_app_close(app_t *app)
{
	struct event event;

    EVENT_INIT(&event, EVENT_APP_DELE);
    event.app = app;            /* post delete event to app                   */

    return gui_send(app, &event);
}

/**
 *******************************************************************************
 * @brief      Sleep application.
 * @param[in]  *app        Application pointer which should sleep.
 * @param[in]  sleep_tick  How much tick to sleep.
 * @param[out] None
 * @retval     None
 *******************************************************************************
 */
void gui_app_sleep(app_t *app, uint32_t sleep_tick)
{
    ASSERT(app != Co_NULL);
    ASSERT(app->tid);
    ASSERT(app->user_data);

    CoTickDelay(sleep_tick);        /* call CoOS delay function               */
}

/**
 *******************************************************************************
 * @brief      Get current application.
 * @param[in]  None
 * @param[out] None
 * @retval     *app      Current application pointer.
 *******************************************************************************
 */
app_t *gui_app_self(void)
{
    app_t *app;
    OS_TID self;
    
    self = CoGetCurTaskID();    /* get current application in TCBTbl          */
    app  = (app_t *)TCBTbl[self].userData;  /* pointer saved in user data     */

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
static StatusType app_event_handler(struct event *event)
{
	ASSERT(event != Co_NULL);

    StatusType result = GUI_E_ERROR;

	switch (event->type)
    {
	case EVENT_APP_DELE:    /* handler app delete event                       */
		gui_app_exit((event)->app, 0);      /* call app exit with code 0      */
        result = GUI_E_OK;
		break;

	case EVENT_PAINT:       /* handler app paint event                        */
        if (gui_app_self()->win) {      /* if app window is already created   */
            gui_window_show(gui_app_self()->win);   /* show window currently  */
        } else if (gui_app_self()->optional_handler != Co_NULL) {/* otherwise */
            /* call app to create window                                      */
            result = gui_app_self()->optional_handler(event);   
        } else {
            result = GUI_E_ERROR;
        }
        gui_mouse_show();               /* show cursor                        */
        break;
    
    case EVENT_MOUSE_BUTTON:    /* handler mouse and keyboard event           */
    {
        point_t cpt;
        app_t *eapp = gui_app_self();
        window_t *ewin = eapp->win;
        widget_t *ewgt, *last_ewgt = ewin->last_mouse_event_widget;
        gui_mouse_get_position(&cpt);    /* get current cursor position */
        ewgt = gui_window_get_mouse_event_widget(ewin, cpt.x, cpt.y);

        if (ewgt != Co_NULL) {
            if (event->button & MOUSE_BUTTON_DOWN) {
                gui_widget_focus(ewgt); /* focus widget if mouse down         */
                gui_mouse_show();       /* show cursor                        */
            } else if (last_ewgt == ewgt) { /* click event raise              */
                if (ewgt->flag & COGUI_WIDGET_FLAG_TITLE) {
                    if (ewgt->flag & COGUI_WIDGET_FLAG_CLOSE_BTN) {    
                        gui_window_close(ewin);     /* close window           */
                    } else if (ewgt->flag & COGUI_WIDGET_FLAG_MINI_BTN) { 
                        gui_window_hide(ewin);      /* hide  window           */
                    }
                } else if (eapp->optional_handler != Co_NULL) {
                    EVENT_INIT(event, EVENT_MOUSE_CLICK);  
                    event->widget = ewgt;           /* send click event to    */   
                    result = eapp->optional_handler(event);/*  dest handler   */
                    gui_mouse_show();       /* show cursor                    */
                } else {
                    gui_mouse_show();       /* show cursor                    */
                }
            } else {
                gui_mouse_show();           /* show cursor                    */
            }
        }
        break;
    }

	default:
		result = GUI_E_ERROR;	/* set result to error                        */
	}
		
	return result;
}

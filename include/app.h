/**
 *******************************************************************************
 * @file       app.h
 * @version    V0.1.0  
 * @date       2019.9.29
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 */ 

#ifndef _COGUI_APP_H
#define _COGUI_APP_H

#include <CoOS.h>
#include <OsTime.h>
#include <OsTask.h>

struct cogui_event;

extern OSTCB    TCBTbl[CFG_MAX_USER_TASKS+SYS_TASK_NUM];
extern ECB      EventTbl[CFG_MAX_EVENT]; 

#define COGUI_APP_FLAG_EXITED  0x04
#define COGUI_APP_FLAG_SHOWN   0x08
#define COGUI_APP_FLAG_KEEP    0x80


struct cogui_app
{
    U8      id;
    char   *name;

    U32 flag;

    U16     ref_cnt;
    U16     exit_code;

    /* Task id */
    OS_TID tid;
    /* Message queue */
    OS_EventID   mq;

    U32     win_cnt;
    /* window activate count */
    U32     win_acti_cnt;

    /* the event handler */
    StatusType (*handler)(struct cogui_event *event);

    void    *user_data;
};
typedef struct cogui_app cogui_app_t;

cogui_app_t *cogui_app_create(char *name);
void _cogui_app_init(cogui_app_t *app);
void cogui_app_delete(cogui_app_t *app);

StatusType cogui_app_event_handler(struct cogui_event *event);

void cogui_app_run(cogui_app_t *app);
void cogui_app_exit(cogui_app_t *app, U16 code);
void cogui_app_close(cogui_app_t *app);
void cogui_app_sleep(cogui_app_t *app, U32 sleepTick);

cogui_app_t *cogui_app_self(void);

#endif /* _COGUI_APP_H */

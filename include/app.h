/**
 *******************************************************************************
 * @file       app.h
 * @version    V0.0.2  
 * @date       2019.8.9
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 */ 

#ifndef _COGUI_APP_H
#define _COGUI_APP_H

#include <CoOS.h>
#include <OsTime.h>
#include <OsTask.h>

extern OSTCB    TCBTbl[CFG_MAX_USER_TASKS+SYS_TASK_NUM];
extern ECB      EventTbl[CFG_MAX_EVENT]; 

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

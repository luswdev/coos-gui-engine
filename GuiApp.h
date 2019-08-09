/**
 *******************************************************************************
 * @file       GuiApp.h
 * @version    V0.0.1   
 * @date       2019.5.18
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 */ 

#ifndef _GUI_APP_H
#define _GUI_APP_H

/*---------------------------- Include ---------------------------------------*/
#include <CoOS.h>
#include <OsTime.h>
#include <OsTask.h>

/*---------------------------- Variable Define -------------------------------*/
extern OSTCB    TCBTbl[CFG_MAX_USER_TASKS+SYS_TASK_NUM];
extern ECB      EventTbl[CFG_MAX_EVENT]; 

/*---------------------------- Function declare ------------------------------*/
cogui_app_t *cogui_app_create(char *name);
void _cogui_app_init(cogui_app_t *app);
void cogui_app_delete(cogui_app_t *app);

StatusType cogui_app_event_handler(struct cogui_event *event);

void cogui_app_run(cogui_app_t *app);
void cogui_app_exit(cogui_app_t *app, U16 code);
void cogui_app_close(cogui_app_t *app);
void cogui_app_sleep(cogui_app_t *app, U32 sleepTick);

cogui_app_t *cogui_app_self(void);

#endif /* _GUI_APP_H */

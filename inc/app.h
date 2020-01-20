/**
 *******************************************************************************
 * @file       app.h
 * @version    V0.6.1
 * @date       2020.01.20
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 */ 

#ifndef __COGUI_APP_H__
#define __COGUI_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

struct cogui_event;
struct cogui_window;

extern OSTCB    TCBTbl[CFG_MAX_USER_TASKS+SYS_TASK_NUM];
extern ECB      EventTbl[CFG_MAX_EVENT]; 

/* application flag define field */
#define COGUI_APP_FLAG_EXITED  0x04
#define COGUI_APP_FLAG_SHOWN   0x08
#define COGUI_APP_FLAG_KEEP    0x80

struct cogui_app
{
    /* meta data field */
    co_uint8_t              id;                                             /**< application id                         */
    char *                  name;                                           /**< appilcation name                       */
    co_uint32_t             flag;                                           /**< application flag                       */
    co_uint16_t             ref_cnt;                                        /**< application reference count            */
    co_uint16_t             exit_code;                                      /**< application exit code number           */
    struct cogui_window *   win;                                            /**< window which belong this application   */
    co_uint8_t              event_buffer[sizeof(struct cogui_event)];       /**< application event buffer for loops     */

    /* CoOS kernel data field */
    OS_TID                  tid;                                            /**< which task its belong to               */
    OS_EventID              mq;                                             /**< mailbox pinter                         */

    /* private user data field */
    void *                  user_data;                                      /**< private user data                      */

    /* event handler field */
    StatusType (*handler)(struct cogui_event *event);                       /**< default event handler                  */
    StatusType (*optional_handler)(struct cogui_event *event);              /**< option event handler for users         */
};

/* new/kill a appication */
cogui_app_t *cogui_app_create(char *name);
void cogui_app_delete(cogui_app_t *app);

/* operation a appication */
void cogui_app_run(cogui_app_t *app);
void cogui_app_exit(cogui_app_t *app, co_uint16_t code);
void cogui_app_close(cogui_app_t *app);
void cogui_app_sleep(cogui_app_t *app, co_uint32_t sleepTick);

/* api for get current running application */
cogui_app_t *cogui_app_self(void);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_APP_H__ */

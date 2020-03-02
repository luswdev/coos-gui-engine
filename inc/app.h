/**
 *******************************************************************************
 * @file       app.h
 * @version    V0.7.2
 * @date       2020.03.01
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
    uint8_t                 id;                                             /**< application id                         */
    char *                  name;                                           /**< appilcation name                       */
    uint32_t                flag;                                           /**< application flag                       */
    uint16_t                ref_cnt;                                        /**< application reference count            */
    uint16_t                exit_code;                                      /**< application exit code number           */
    int16_t                 win_id;                                         /**< window which belong this application   */
    struct cogui_window *   win;                                            /**< window which belong this application   */
    uint8_t                 event_buffer[sizeof(struct cogui_event)];       /**< application event buffer for loops     */

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
void cogui_app_exit(cogui_app_t *app, uint16_t code);
StatusType cogui_app_close(cogui_app_t *app);
void cogui_app_sleep(cogui_app_t *app, uint32_t sleepTick);

/* api for get current running application */
cogui_app_t *cogui_app_self(void);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_APP_H__ */

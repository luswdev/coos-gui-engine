/**
 *******************************************************************************
 * @file       app.h
 * @version    V0.7.3
 * @date       2020.03.25
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 */ 

#ifndef __GUI_APP_H__
#define __GUI_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

struct event;
struct window;

/* application flag define field */
#define COGUI_APP_FLAG_EXITED  0x04
#define COGUI_APP_FLAG_SHOWN   0x08
#define COGUI_APP_FLAG_KEEP    0x80

struct app
{
    /* meta data field */
    uint8_t                 id;                                             /**< application id                         */
    char *                  name;                                           /**< appilcation name                       */
    uint32_t                flag;                                           /**< application flag                       */
    uint16_t                ref_cnt;                                        /**< application reference count            */
    uint16_t                exit_code;                                      /**< application exit code number           */
    int16_t                 win_id;                                         /**< window which belong this application   */
    struct window *         win;                                            /**< window which belong this application   */
    uint8_t                 event_buffer[sizeof(struct event)];             /**< application event buffer for loops     */

    /* CoOS kernel data field */
    OS_TID                  tid;                                            /**< which task its belong to               */
    OS_EventID              mq;                                             /**< mailbox pinter                         */

    /* private user data field */
    void *                  user_data;                                      /**< private user data                      */

    /* event handler field */
    StatusType (*handler)(struct event *event);                             /**< default event handler                  */
    StatusType (*optional_handler)(struct event *event);                    /**< option event handler for users         */
};

/* new/kill a appication */
app_t *gui_app_create(char *name);
void gui_app_delete(app_t *app);

/* operation a appication */
void gui_app_run(app_t *app);
void gui_app_exit(app_t *app, uint16_t code);
StatusType gui_app_close(app_t *app);
void gui_app_sleep(app_t *app, uint32_t sleepTick);

/* api for get current running application */
app_t *gui_app_self(void);

#ifdef __cplusplus
}
#endif

#endif /* __GUI_APP_H__ */

/**
 *******************************************************************************
 * @file       server.h
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      The server for gui engine.	
 *******************************************************************************
 */ 

#ifndef __GUI_SERVER_H__
#define __GUI_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* create server application */
void cogui_server_init(void);

/* post event to server */
StatusType cogui_server_post_event(struct event *event);
StatusType gui_server_post_event_sync(struct event *event);

/* get server pointer */
app_t *gui_get_server(void);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_SERVER_H__ */

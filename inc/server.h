/**
 *******************************************************************************
 * @file       server.h
 * @version    V0.6.1
 * @date       2020.01.20
 * @brief      The server for gui engine.	
 *******************************************************************************
 */ 

#ifndef __COGUI_SERVER_H__
#define __COGUI_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* create server application */
void cogui_server_init(void);

/* post event to server */
StatusType cogui_server_post_event(struct cogui_event *event);
StatusType cogui_server_post_event_sync(struct cogui_event *event);

/* get server pointer */
cogui_app_t *cogui_get_server(void);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_SERVER_H__ */

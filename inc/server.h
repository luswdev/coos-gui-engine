/**
 *******************************************************************************
 * @file       server.h
 * @version    V0.0.3
 * @date       2020.01.19
 * @brief      The server for gui engine.	
 *******************************************************************************
 */ 

#ifndef _COGUI_SERVER_H
#define _COGUI_SERVER_H

/* create server application */
void cogui_server_init(void);

/* post event to server */
StatusType cogui_server_post_event(struct cogui_event *event);
StatusType cogui_server_post_event_sync(struct cogui_event *event);

/* get server pointer */
cogui_app_t *cogui_get_server(void);

#endif /* _GUI_SERVER_H */

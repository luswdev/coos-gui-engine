/**
 *******************************************************************************
 * @file       server.h
 * @version    V0.0.2 
 * @date       2019.8.9
 * @brief      The server for gui engine.	
 *******************************************************************************
 */ 

#ifndef _COGUI_SERVER_H
#define _COGUI_SERVER_H

/*---------------------------- Function Define -------------------------------*/
StatusType cogui_server_post_event(struct cogui_event *event);

cogui_app_t *cogui_get_server(void);

void cogui_server_init(void);

#endif /* _GUI_SERVER_H */

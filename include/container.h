/**
 *******************************************************************************
 * @file       GuiContainer.h
 * @version    V0.0.1   
 * @date       2019.8.9
 * @brief      Some widget function for GUI engine's container.	
 *******************************************************************************
 */ 

#ifndef _COGUI_CONTAINER_H
#define _COGUI_CONTAINER_H

cogui_container_t *cogui_container_create(void);
void cogui_container_delete(cogui_container_t *container);

StatusType cogui_container_event_handler(cogui_widget_t *widget, struct cogui_event *event);

#endif /* _COGUI_CONTAINER_H */

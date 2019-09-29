/**
 *******************************************************************************
 * @file       GuiContainer.h
 * @version    V0.0.2   
 * @date       2019.9.29
 * @brief      Some widget function for GUI engine's container.	
 *******************************************************************************
 */ 

#ifndef _COGUI_CONTAINER_H
#define _COGUI_CONTAINER_H

struct cogui_box
{
    U16 orient;
    U16 borders_size;

    struct cogui_container *container;
};
typedef struct cogui_box cogui_box_t;

struct cogui_container
{
    cogui_widget_t *parent;

    StatusType (*handler)(struct cogui_event *event);

    /* layout box */
    cogui_box_t *layout_box;

    cogui_list_t children;

};
typedef struct cogui_container cogui_container_t;

cogui_container_t *cogui_container_create(void);
void cogui_container_delete(cogui_container_t *container);

StatusType cogui_container_event_handler(cogui_widget_t *widget, struct cogui_event *event);

#endif /* _COGUI_CONTAINER_H */

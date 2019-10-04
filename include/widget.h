/**
 *******************************************************************************
 * @file       widget.h
 * @version    V0.1.1
 * @date       2019.10.4
 * @brief      Some widget function for GUI engine's widget.	
 *******************************************************************************
 */ 

#ifndef _COGUI_WIDGET_H
#define _COGUI_WIDGET_H

#include "region.h"
#include "system.h"
#include "dc.h"

struct cogui_dc;
struct cogui_gc;
struct cogui_event;
struct cogui_widget;

/* widget flag */
#define COGUI_WIDGET_FLAG_INIT          0x00
#define COGUI_WIDGET_FLAG_SHOWN         0x01
#define COGUI_WIDGET_FLAG_FOCUS         0x02
#define COGUI_WIDGET_FLAG_FOCUSABLE     0x08

/* widget type */
#define COGUI_WIDGET_TYPE_INIT          0x00
#define COGUI_WIDGET_TYPE_WIDGET        0x01
#define COGUI_WIDGET_TYPE_WINDOW        0x02

#define COGUI_WIDGET(w) (struct cogui_widget *)(w)

typedef StatusType  (*event_handler_ptr)(struct cogui_widget *widget, struct cogui_event *event);

struct cogui_widget
{
    /* the widget that contains this widget */
    struct cogui_widget *parent;
    /* the window that contains this widget */
    struct cogui_window *top_level;
    /* the widget children and sibling */
    struct cogui_list_node sibling;

    S16 flag;
    S16 type;
    
    /* hardware device context */
    U64 dc_type;
    struct cogui_dc *dc_engine;

    /* the graphic context of widget */
    struct cogui_gc gc;

    /* the widget extent */
    struct cogui_rect extent;

    /* minimal width and height of widget */
    S16 min_width, min_height;
    /* widget align */
    S32 align;
    U16 border;
    U16 border_style;
    
    /* the screen node id */
    S32 screen_node_id;

    /* call back */
    StatusType  (*on_focus_in)(struct cogui_widget *widget, struct cogui_event *event);
    StatusType (*on_focus_out)(struct cogui_widget *widget, struct cogui_event *event);

    /* the event handler */
    StatusType (*handler)(struct cogui_widget *widget ,struct cogui_event *event);

    /* user private data */
    U32 user_data;
};
typedef struct cogui_widget cogui_widget_t;

/*---------------------------- Function Define -------------------------------*/
cogui_widget_t *cogui_widget_create(void);
void cogui_widget_delete(cogui_widget_t *widget);

StatusType cogui_widget_event_handler(cogui_widget_t *widget, struct cogui_event *event);

void cogui_widget_focus(cogui_widget_t *widget);
void cogui_widget_unfocus(cogui_widget_t *widget);

void cogui_widget_set_focus(cogui_widget_t *widget, event_handler_ptr handler);
void cogui_widget_set_unfocus(cogui_widget_t *widget, event_handler_ptr handler);

void cogui_widget_get_rect(cogui_widget_t *widget, cogui_rect_t *rect);
void cogui_widget_set_border(cogui_widget_t *widget, U32 style);
void cogui_widget_set_rect(cogui_widget_t *widget, cogui_rect_t *rect);
void cogui_widget_set_rectangle(cogui_widget_t *widget, S32 x, S32 y, S32 width, S32 height);
void cogui_widget_get_extent(cogui_widget_t *widget, cogui_rect_t *rect);

void cogui_widget_set_minsize(cogui_widget_t *widget, S32 width, S32 height);
void cogui_widget_set_minwidth(cogui_widget_t *widget, S32 width);
void cogui_widget_set_minheight(cogui_widget_t *widget, S32 height);

void cogui_widget_show(cogui_widget_t *widget);
StatusType cogui_widget_onshow(cogui_widget_t *widget, struct cogui_event *event);
void cogui_widget_hide(cogui_widget_t *widget);
StatusType cogui_widget_onhide(cogui_widget_t *widget, struct cogui_event *event);
void cogui_widget_update(cogui_widget_t *widget);

/* get the physical position of a logic point on widget */
void cogui_widget_point_l2p(cogui_widget_t *widget, cogui_point_t *point);
/* get the physical position of a logic rect on widget */
void cogui_widget_rect_l2p(cogui_widget_t *widget, cogui_rect_t *rect);

/* get the logic position of a physical point on widget */
void cogui_widget_point_p2l(cogui_widget_t *widget, cogui_point_t *point);
/* get the logic position of a physical rect on widget */
void cogui_widget_rect_p2l(cogui_widget_t *widget, cogui_rect_t *rect);

/* move widget and its children to a logic point */
void cogui_widget_move_to_logic(cogui_widget_t *widget, S32 dx, S32 dy);

/* get the next sibling of widget */
cogui_widget_t *cogui_widget_get_next_sibling(cogui_widget_t *widget);
/* get the prev sibling of widget */
cogui_widget_t *cogui_widget_get_prev_sibling(cogui_widget_t *widget);

#endif /* _COGUI_WIDGET_H */

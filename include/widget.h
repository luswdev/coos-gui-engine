/**
 *******************************************************************************
 * @file       widget.h
 * @version    V0.0.2
 * @date       2019.8.9
 * @brief      Some widget function for GUI engine's widget.	
 *******************************************************************************
 */ 

#ifndef _COGUI_WIDGET_H
#define _COGUI_WIDGET_H

/* widget flag */
#define COGUI_WIDGET_FLAG_DEFAULT       0x0000
#define COGUI_WIDGET_FLAG_SHOWN         0x0001
#define COGUI_WIDGET_FLAG_DISABLE       0x0002
#define COGUI_WIDGET_FLAG_FOCUS         0x0004
#define COGUI_WIDGET_FLAG_TRANSPARENT   0x0008
#define COGUI_WIDGET_FLAG_FOCUSABLE     0x0010
#define COGUI_WIDGET_FLAG_DC_VISIBLE    0x0100
#define COGUI_WIDGET_FLAG_IN_ANIM       0x0200
#define COGUI_WIDGET_FLAG_IS_CONTAINER  0x0400

/*---------------------------- Function Define -------------------------------*/
cogui_widget_t *cogui_widget_create(void);
void cogui_widget_delete(cogui_widget_t *widget);

StatusType cogui_widget_event_handler(cogui_widget_t *widget, struct cogui_event_t *event);

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
StatusType cogui_widget_onshow(cogui_widget_t *widget, struct cogui_event_t *event);
void cogui_widget_hide(cogui_widget_t *widget);
StatusType cogui_widget_onhide(cogui_widget_t *widget, struct cogui_event_t *event);
void cogui_widget_update(cogui_widget_t *widget);

/* get the physical position of a logic point on widget */
void cogui_widget_point_to_device(cogui_widget_t *widget, cogui_point_t *point);
/* get the physical position of a logic rect on widget */
void cogui_widget_rect_to_device(cogui_widget_t *widget, cogui_rect_t *rect);

/* get the logic position of a physical point on widget */
void cogui_widget_point_to_logic(cogui_widget_t *widget, cogui_point_t *point);
/* get the logic position of a physical rect on widget */
void cogui_widget_rect_to_logic(cogui_widget_t *widget, cogui_rect_t *rect);

/* move widget and its children to a logic point */
void cogui_widget_move_to_logic(cogui_widget_t *widget, S32 dx, S32 dy);

void cogui_widget_clip_parent(cogui_widget_t *widget);
void cogui_widget_clip_return(cogui_widget_t *widget);

/* update the clip info of widget */
void cogui_widget_update_clip(cogui_widget_t *widget);

/* get the next sibling of widget */
cogui_widget_t *cogui_widget_get_next_sibling(cogui_widget_t *widget);
/* get the prev sibling of widget */
cogui_widget_t *cogui_widget_get_prev_sibling(cogui_widget_t *widget);

#endif /* _COGUI_WIDGET_H */

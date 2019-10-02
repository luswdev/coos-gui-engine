/**
 *******************************************************************************
 * @file       window.h
 * @version    V0.0.2  
 * @date       2019.9.29
 * @brief      Some system function for GUI engine's event.	
 *******************************************************************************
 */ 

#ifndef _COGUI_WINDOW_H
#define _COGUI_WINDOW_H

#define COGUI_WIN_STYLE_NO_FOCUS            0x0001  /* non-focused window            */
#define COGUI_WIN_STYLE_NO_TITLE            0x0002  /* no title window               */
#define COGUI_WIN_STYLE_NO_BORDER           0x0004  /* no border window              */
#define COGUI_WIN_STYLE_CLOSEBOX            0x0008  /* window has the close button   */
#define COGUI_WIN_STYLE_MINIBOX             0x0010  /* window has the mini button    */

#define COGUI_WIN_STYLE_DESTROY_ON_CLOSE    0x0020  /* window is destroyed when closed */
#define COGUI_WIN_STYLE_ONTOP               0x0040  /* window is in the top layer    */
#define COGUI_WIN_STYLE_ONBTM               0x0080  /* window is in the bottom layer */
#define COGUI_WIN_STYLE_MAINWIN             0x0106  /* window is a main window       */

#define COGUI_WIN_MAGIC					  0xA5A55A5A		/* win magic flag */

#define COWINTITLE_HEIGHT         20
#define COWINTITLE_CB_WIDTH       16
#define COWINTITLE_CB_HEIGHT      16
#define COWINTITLE_BORDER_SIZE    2

/* window flag */
#define COGUI_WINDOW_FLAG_INIT        0x00
#define COGUI_WINDOW_FLAG_MODAL       0x01
#define COGUI_WINDOW_FLAG_CLOSED      0x02
#define COGUI_WINDOW_FLAG_ACTIVATE    0x04

#define COGUI_WIN_FLAG_CONNECTED      0x10

struct cogui_window
{
    struct cogui_widget *parent;

    /* update count */
    S64 update;

    /* drawing count */
    S64 drawing;
    cogui_rect_t drawing_rect;

    /* parent window. Co_NULL if the window is a top level window */
    struct cogui_window *parent_window;

    cogui_region_t outer_clip;
    cogui_rect_t outer_extent;

    cogui_widget_t *focus_widget;

    /* which app I belong */
    cogui_app_t *app;

    /* window style */
    U16 style;

    /* window state flag */
    U32 flag;

    /* last mouse event handled widget */
    cogui_widget_t *last_mouse_event_widget;

    /* window title */
    U8 *title;
    cogui_widget_t *_title_wgt;

    /* call back */
    StatusType (*on_activate)(cogui_widget_t * widget, struct cogui_event *event);
    StatusType (*on_deactivate)(cogui_widget_t * widget, struct cogui_event *event);
    StatusType (*on_close)(cogui_widget_t * widget, struct cogui_event *event);

    StatusType (*on_key)(cogui_widget_t * widget, struct cogui_event *event);

    /* reserved user data */
    void *user_data;

    /* Private data */
    S64 (*_do_show)(struct cogui_window *win);

    /* app ref_count */
    U16 app_ref_cnt;

    /* win magic flag, magic value is 0xA5A55A5A */
    U32	magic;
};
typedef struct cogui_window cogui_window_t;


cogui_window_t *cogui_window_create(cogui_window_t *parentWindow, U8 *title, cogui_rect_t *rect, U16 style);
void cogui_window_delete(cogui_window_t *win);

StatusType cogui_window_close(cogui_window_t *win);

U64 cogui_window_show(cogui_window_t *win);
U64 cogui_window_do_show(cogui_window_t *win);

void cogui_window_hide(cogui_window_t *win);

StatusType cogui_window_active(cogui_window_t *win);
StatusType cogui_window_is_activated(cogui_window_t *win);

void cogui_window_move(cogui_window_t *win, S32 x, S32 y);

void cogui_window_set_rect(cogui_window_t *win, cogui_rect_t *rect);

void cogui_window_set_onactivate(cogui_window_t *win, event_handler_ptr handler);
void cogui_window_set_ondeactive(cogui_window_t *win, event_handler_ptr handler);
void cogui_window_set_onclose(cogui_window_t *win, event_handler_ptr handler);
void cogui_window_set_onkey(cogui_window_t *win, event_handler_ptr handler);

StatusType cogui_window_event_handler(cogui_widget_t * win, struct cogui_event *event);

void cogui_window_set_title(cogui_window_t *win, const U8 *title);
U8 *cogui_window_get_title(cogui_window_t *win);

cogui_window_t *cogui_window_top_most_shown(void);
cogui_window_t *cogui_window_get_next_shown(void);

#endif /* _COGUI_WINDOW_H */

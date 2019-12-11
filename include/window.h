/**
 *******************************************************************************
 * @file       window.h
 * @version    V0.0.2  
 * @date       2019.10.5
 * @brief      Window management function header file.
 *******************************************************************************
 */ 

#ifndef _COGUI_WINDOW_H
#define _COGUI_WINDOW_H

/* window style */
#define COGUI_WINDOW_STYLE_NO_TITLE            0x01  /**< no title window               */
#define COGUI_WINDOW_STYLE_NO_BORDER           0x02  /**< no border window              */

#define COGUI_WINDOW_MAGIC					  0xA5A55A5A		/* win magic flag */

/* window flag */
#define COGUI_WINDOW_FLAG_INIT        0x00
#define COGUI_WINDOW_FLAG_SHOW        0x01

#define COGUI_WINDOW(w)     ((struct cogui_window *)(w))

/* enable (show) */
#define COGUI_WINDOW_ENABLE(w)          COGUI_WINDOW((w))->flag |= COGUI_WINDOW_FLAG_SHOW
#define COGUI_WINDOW_DISABLE(w)         COGUI_WINDOW((w))->flag &= ~COGUI_WINDOW_FLAG_SHOW
#define COGUI_WINDOW_IS_ENABLE(w)       (COGUI_WINDOW((w))->flag & COGUI_WINDOW_FLAG_SHOW)

#define COGUI_WINDOW_CREATE_WITH_TITLE()        cogui_window_create(~COGUI_WINDOW_STYLE_NO_TITLE)
#define COGUI_WINDOW_CREATE_WITHOUT_TITLE()     cogui_window_create(COGUI_WINDOW_STYLE_NO_TITLE)

struct cogui_window
{
    cogui_widget_t *widget_list;

    co_int16_t id;

    /* window style */
    co_uint16_t style;

    /* window state flag */
    co_int32_t flag;  

    /* update count */
    co_int64_t update;

    co_int32_t widget_cnt;

    /* drawing count */
    co_int64_t drawing;
    cogui_rect_t drawing_rect;

    cogui_widget_t *focus_widget;

    /* which app I belong */
    cogui_app_t *app;

    /* last mouse event handled widget */
    cogui_widget_t *last_mouse_event_widget;

    /* window title */
    cogui_widget_t *title;
    char *title_name;

    /* call back */
    StatusType (*on_activate)(cogui_widget_t *widget, struct cogui_event *event);
    StatusType (*on_deactivate)(cogui_widget_t *widget, struct cogui_event *event);

    StatusType (*on_key)(cogui_widget_t *widget, struct cogui_event *event);

    /* reserved user data */
    void *user_data;

    /* Private data */
    co_uint64_t (*_do_show)(struct cogui_window *win);
    StatusType  (*handler)(struct cogui_window *widget ,struct cogui_event *event);

    /* app ref_count */
    co_uint16_t app_ref_cnt;

    /* win magic flag, magic value is 0xA5A55A5A */
    co_uint32_t	magic;
};
typedef struct cogui_window cogui_window_t;

struct main_app_table {
    cogui_widget_t *app_icon;
    cogui_widget_t *app_title_box;
    char *          title;    
};


cogui_window_t *cogui_window_create(co_uint16_t style);
void cogui_window_delete(cogui_window_t *win);

cogui_window_t *cogui_main_window_create(void);

cogui_window_t *cogui_get_current_window(void);

StatusType cogui_window_close(cogui_window_t *win);

StatusType cogui_window_show(cogui_window_t *win);
StatusType cogui_window_onshow(cogui_window_t *win);

StatusType cogui_window_hide(cogui_window_t *win);
StatusType cogui_window_onhide(cogui_window_t *win);

StatusType cogui_window_active(cogui_window_t *win);
StatusType cogui_window_is_activated(cogui_window_t *win);

void cogui_window_set_onactivate(cogui_window_t *win, event_handler_ptr handler);
void cogui_window_set_ondeactive(cogui_window_t *win, event_handler_ptr handler);
void cogui_window_set_onkey(cogui_window_t *win, event_handler_ptr handler);

StatusType cogui_window_event_handler(struct cogui_window * win, struct cogui_event *event);

void cogui_window_set_title(cogui_window_t *win, const U8 *title);
U8 *cogui_window_get_title(cogui_window_t *win);

void cogui_assert_failed_page(const char* ex, co_uint16_t line, const char* func);

#endif /* _COGUI_WINDOW_H */

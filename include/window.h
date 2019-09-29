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

enum cogui_win_flag
{
    COGUI_WIN_FLAG_INIT        = 0x00,  /* init state              */
    COGUI_WIN_FLAG_MODAL       = 0x01,  /* modal mode window       */
    COGUI_WIN_FLAG_CLOSED      = 0x02,  /* window is closed        */
    COGUI_WIN_FLAG_ACTIVATE    = 0x04,  /* window is activated     */
    COGUI_WIN_FLAG_UNDER_MODAL = 0x08,  /* window is under modal
                                           show(modaled by other)  */
    COGUI_WIN_FLAG_CONNECTED   = 0x10,  /* connected to server */
    /* window is event_key dispatcher(dispatch it to the focused widget in
     * current window) _and_ a key handler(it should be able to handle keys
     * such as ESC). Both of dispatching and handling are in the same
     * function(rtgui_win_event_handler). So we have to distinguish between the
     * two modes.
     *
     * If this flag is set, we are in key-handling mode.
     */
    COGUI_WIN_FLAG_HANDLE_KEY  = 0x20,

    COGUI_WIN_FLAG_CB_PRESSED  = 0x40,
};

struct cogui_window
{
    struct GuiContainer *parent;

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
    enum cogui_win_flag flag;

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


cogui_window_t *WinCreate(cogui_window_t *parentWindow, U8 *title, cogui_rect_t *rect, U16 style);
void WinDele(cogui_window_t *win);

StatusType WinClose(cogui_window_t *win);

U64 WinShow(cogui_window_t *win);
U64 WinDoShow(cogui_window_t *win);

void WinHide(cogui_window_t *win);

StatusType WinActivate(cogui_window_t *win);
StatusType WinIsActivated(cogui_window_t *win);

void WinMove(cogui_window_t *win, S32 x, S32 y);

void WinSetRect(cogui_window_t *win, cogui_rect_t *rect);
void WinUpdateClip(cogui_window_t *win);

void WinSetOnactivate(cogui_window_t *win, event_handler_ptr handler);
void WinSetOndeactivate(cogui_window_t *win, event_handler_ptr handler);
void WinSetOnclose(cogui_window_t *win, event_handler_ptr handler);
void WinSetOnkey(cogui_window_t *win, event_handler_ptr handler);

StatusType WinEventHandler(cogui_widget_t * win, struct cogui_event *event);

void WinSetRect(cogui_window_t *win, cogui_rect_t *rect);
void WinSetTitle(cogui_window_t *win, const U8 *title);
U8 *WinGetTitle(cogui_window_t *win);

cogui_window_t *WinGetTopmostShown(void);
cogui_window_t *WinGetNextShown(void);

#endif /* _COGUI_WINDOW_H */

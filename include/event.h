/**
 *******************************************************************************
 * @file       GuiEvent.h
 * @version    V0.0.1   
 * @date       2019.5.19
 * @brief      Some system function for GUI engine's event.	
 *******************************************************************************
 */ 

#ifndef _COGUI_EVENT_H
#define _COGUI_EVENT_H

/*---------------------------- Include ---------------------------------------*/
#include "cogui.h"

enum cogui_event_type
{
    /* applications event */
    COGUI_EVENT_APP_CREATE = 0,        /* create an application */
    COGUI_EVENT_APP_DELE,              /* destroy an application */
    COGUI_EVENT_APP_ACTIVATE,          /* activate an application */

    /* window event */
    COGUI_EVENT_WIN_CREATE,            /* create a window       */
    COGUI_EVENT_WIN_DELE,              /* destroy a window      */
    COGUI_EVENT_WIN_SHOW,              /* show a window         */
    COGUI_EVENT_WIN_HIDE,              /* hide a window         */
    COGUI_EVENT_WIN_ACTIVATE,          /* activate a window     */
    COGUI_EVENT_WIN_DEACTIVATE,        /* deactivate a window   */
    COGUI_EVENT_WIN_CLOSE,             /* close a window        */
    COGUI_EVENT_WIN_MOVE,              /* move a window         */
    COGUI_EVENT_WIN_RESIZE,            /* resize a window       */
    COGUI_EVENT_WIN_TITLE,             /* set window title      */
    COGUI_EVENT_WIN_UPDATE_END,        /* update done for window */

    /* mouse and keyboard event */
    COGUI_EVENT_MOUSE_MOTION,          /* mouse motion          */
    COGUI_EVENT_MOUSE_BUTTON,          /* mouse button info     */
    COGUI_EVENT_KBD,                   /* keyboard info         */
		
		/* user command event. It should always be the last command type. */
    COGUI_EVENT_COMMAND,               /* user command          */
};

/*---------------------------- structure -------------------------------------*/
struct cogui_event {
    /* the event type */
    enum cogui_event_type type;

    /* the event sender */
    cogui_app_t *sender;

    /* mailbox to acknowledge request */
    OS_EventID ack;
};

#define _COGUI_EVENT_ELEMENT           \
    struct cogui_event parent;         \
    P_GuiWin *win;                     \

#define COGUI_EVENT_INIT(e,t,s)        \
{                                      \
    (e)->type   = (t);                 \
    (e)->sender = cogui_app_self();    \
    (e)->ack    = 0;      			   \
}                                      \

struct cogui_event_app
{
    struct cogui_event parent; 

    cpgui_app_t *app;
};

struct cogui_event_mouse
{
    _COGUI_EVENT_ELEMENT

    U16 x, y;
    U16 button;

    /* id of session(from up to down) */
    U32 id;

    /* window activate count */
    U32 win_acti_cnt;

    cpgui_app_t *app;
};

#define COGUI_MOUSE_BUTTON_LEFT         0x01
#define COGUI_MOUSE_BUTTON_RIGHT        0x02
#define COGUI_MOUSE_BUTTON_MIDDLE       0x03
#define COGUI_MOUSE_BUTTON_WHEELUP      0x04
#define COGUI_MOUSE_BUTTON_WHEELDOWN    0x08

#define COGUI_MOUSE_BUTTON_DOWN         0x10
#define COGUI_MOUSE_BUTTON_UP           0x20

struct cogui_event_kbd
{
    _COGUI_EVENT_ELEMENT

    /* window activate count */
    U32 win_acti_cnt;

    U16 type;         /* key up or down */
    U16 key;          /* current key */
    U16 mod;          /* current key modifiers */
    U16 ascii_code;   /* character */

    cogui_app_t *app;
};

struct cogui_event_win
{
    _COGUI_EVENT_ELEMENT
};


struct cogui_event_win_create
{
    _COGUI_EVENT_ELEMENT
    P_GuiWin parentWinow;
};

struct cogui_event_win_move
{
    _COGUI_EVENT_ELEMENT
    S16 x, y;
};

struct cogui_event_win_resize
{
    _COGUI_EVENT_ELEMENT
    GuiRect rect;
};

struct cogui_event_win_set_title
{
    _COGUI_EVENT_ELEMENT
    U8 *title;
};

#endif

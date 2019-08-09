/**
 *******************************************************************************
 * @file       event.h
 * @version    V0.0.2   
 * @date       2019.8.9
 * @brief      Some system function for GUI engine's event.	
 *******************************************************************************
 */ 

#ifndef _COGUI_EVENT_H
#define _COGUI_EVENT_H

#include "cogui.h"

enum cogui_event_type
{
    /* applications event */
    COGUI_EVENT_APP_CREATE = 0,
    COGUI_EVENT_APP_DELE,
    COGUI_EVENT_APP_ACTIVATE,

    /* window event */
    COGUI_EVENT_WIN_CREATE,
    COGUI_EVENT_WIN_DELE,
    COGUI_EVENT_WIN_SHOW,
    COGUI_EVENT_WIN_HIDE,
    COGUI_EVENT_WIN_ACTIVATE,
    COGUI_EVENT_WIN_DEACTIVATE,
    COGUI_EVENT_WIN_CLOSE,
    COGUI_EVENT_WIN_MOVE,
    COGUI_EVENT_WIN_RESIZE,
    COGUI_EVENT_WIN_TITLE,
    COGUI_EVENT_WIN_UPDATE_END,

    /* mouse and keyboard event */
    COGUI_EVENT_MOUSE_MOTION,
    COGUI_EVENT_MOUSE_BUTTON,
    COGUI_EVENT_KBD,

    COGUI_EVENT_COMMAND,
};

struct cogui_event {
    enum cogui_event_type type;

    cogui_app_t *sender;

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

    U32 id;

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

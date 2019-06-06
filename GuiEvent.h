/**
 *******************************************************************************
 * @file       GuiEvent.h
 * @version    V0.0.1   
 * @date       2019.5.19
 * @brief      Some system function for GUI engine's event.	
 *******************************************************************************
 */ 

#ifndef _GUI_EVENT_H
#define _GUI_EVENT_H

/*---------------------------- Include ---------------------------------------*/
#include "cogui.h"

enum eventType
{
    /* applications event */
    GUI_EVENT_APP_CREATE=0,            /* create an application */
    GUI_EVENT_APP_DELE,           /* destroy an application */
    GUI_EVENT_APP_ACTIVATE,          /* activate an application */

    /* window event */
    GUI_EVENT_WIN_CREATE,            /* create a window       */
    GUI_EVENT_WIN_DELE,           /* destroy a window      */
    GUI_EVENT_WIN_SHOW,              /* show a window         */
    GUI_EVENT_WIN_HIDE,              /* hide a window         */
    GUI_EVENT_WIN_ACTIVATE,          /* activate a window     */
    GUI_EVENT_WIN_DEACTIVATE,        /* deactivate a window   */
    GUI_EVENT_WIN_CLOSE,             /* close a window        */
    GUI_EVENT_WIN_MOVE,              /* move a window         */
    GUI_EVENT_WIN_RESIZE,            /* resize a window       */
    GUI_EVENT_WIN_TITLE,             /* set window title      */
    GUI_EVENT_WIN_UPDATE_END,        /* update done for window */

    /* mouse and keyboard event */
    GUI_EVENT_MOUSE_MOTION,          /* mouse motion          */
    GUI_EVENT_MOUSE_BUTTON,          /* mouse button info     */
    GUI_EVENT_KBD,                   /* keyboard info         */
		
		/* user command event. It should always be the last command type. */
    GUI_EVENT_COMMAND,      /* user command          */
};

/*---------------------------- structure -------------------------------------*/
struct GuiEvent {
    /* the event type */
    enum eventType type;

    /* the event sender */
    P_GuiApp sender;

    /* mailbox to acknowledge request */
    OS_EventID ack;
};

#define _GUI_EVENT_ELEMENT                  \
    struct GuiEvent parent;                 \
    P_GuiWin *win;                          \

#define GUI_EVENT_INIT(e,t,s)   \
{                               \
    (e)->type   = (t);          \
    (e)->sender = (s);    			\
    (e)->ack    = 0;      			\
}                               \

struct eventApp
{
    struct GuiEvent parent; 

    P_GuiApp app;
};

struct eventMouse
{
    _GUI_EVENT_ELEMENT

    U16 x, y;
    U16 button;

    /* id of session(from up to down) */
    U32 id;

    /* window activate count */
    U32 winActiCnt;

    P_GuiApp app;
};

#define GUI_MOUSE_BUTTON_LEFT         0x01
#define GUI_MOUSE_BUTTON_RIGHT        0x02
#define GUI_MOUSE_BUTTON_MIDDLE       0x03
#define GUI_MOUSE_BUTTON_WHEELUP      0x04
#define GUI_MOUSE_BUTTON_WHEELDOWN    0x08

#define GUI_MOUSE_BUTTON_DOWN         0x10
#define GUI_MOUSE_BUTTON_UP           0x20

struct eventKbd
{
    _GUI_EVENT_ELEMENT

    /* window activate count */
    U32 winActiCnt;

    U16 type;         /* key up or down */
    U16 key;          /* current key */
    U16 mod;          /* current key modifiers */
    U16 asciiCode;    /* character */

    P_GuiApp app;
};

struct eventWin
{
    _GUI_EVENT_ELEMENT
};


struct eventWinCreate
{
    _GUI_EVENT_ELEMENT
    P_GuiWin parentWinow;
};

struct eventWinMove
{
    _GUI_EVENT_ELEMENT
    S16 x, y;
};

struct eventWinResize
{
    _GUI_EVENT_ELEMENT
    GuiRect rect;
};

struct eventWinSetTitle
{
    _GUI_EVENT_ELEMENT
    U8 *title;
};

#endif

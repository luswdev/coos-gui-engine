/**
 *******************************************************************************
 * @file       GuiEvent.h
 * @version    V0.0.1   
 * @date       2019.5.19
 * @brief      Some system function for GUI engine's event.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 
/*---------------------------- Include ---------------------------------------*/
#include "GuiSystem.h"
#include "GuiApp.h"
#include "kbdDef.h"
#include "GuiWindow.h"

enum eventType
{
    /* mouse and keyboard event */
    RTGUI_EVENT_MOUSE_MOTION,          /* mouse motion          */
    RTGUI_EVENT_MOUSE_BUTTON,          /* mouse button info     */
    RTGUI_EVENT_KBD,                   /* keyboard info         */

};

struct GuiEvent {
    /* the event type */
    enum eventType type;

    /* the event sender */
    P_GuiApp sender;

    /* mailbox to acknowledge request */
    void* ack;
};

#define _GUI_EVENT_ELEMENT                  \
    struct GuiEvent parent;                 \
    P_GuiWin *win                           \

#define GUI_EVENT_INIT(e)   \
{                           \
    e->sender =                         \
}                           \

struct eventMouse
{
    _GUI_EVENT_ELEMENT

    U16 x, y;
    U16 button;

    /* id of session(from up to down) */
    U32 id;

    /* window activate count */
    U32 winActiCnt;
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
}
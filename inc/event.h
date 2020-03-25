/**
 *******************************************************************************
 * @file       event.h
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      Some system function for GUI engine's event.	
 *******************************************************************************
 */ 

#ifndef __GUI_EVENT_H__
#define __GUI_EVENT_H__

#ifdef __cplusplus
extern "C" {
#endif

struct app;
struct window;

/* applications event */
#define EVENT_APP_CREATE          (uint8_t)0
#define EVENT_APP_DELE            (uint8_t)1
#define EVENT_APP_ACTIVATE        (uint8_t)2

/* widget event */
#define EVENT_WIDGET_SHOW         (uint8_t)3
#define EVENT_WIDGET_HIDE         (uint8_t)4
#define EVENT_WIDGET_MOVE         (uint8_t)5

/* window event */
#define EVENT_WINDOW_CREATE       (uint8_t)6
#define EVENT_WINDOW_DELE         (uint8_t)7
#define EVENT_WINDOW_SHOW         (uint8_t)8
#define EVENT_WINDOW_HIDE         (uint8_t)9
#define EVENT_WINDOW_CLOSE        (uint8_t)10
#define EVENT_WINDOW_TITLE        (uint8_t)11

/* mouse and keyboard event */
#define EVENT_MOUSE_MOTION        (uint8_t)12
#define EVENT_MOUSE_BUTTON        (uint8_t)13
#define EVENT_MOUSE_CLICK         (uint8_t)14
#define EVENT_KBD                 (uint8_t)15
#define EVENT_PAINT               (uint8_t)16
#define EVENT_COMMAND             (uint8_t)17

struct event {
    uint8_t type;

    struct app *sender;

    OS_EventID ack;

    struct app *app;
    struct window *win;
    struct widget *widget;

    int32_t dx, dy;
    uint16_t button;

    uint16_t kbd_type;         /* key up or down */
    uint16_t key;          /* current key */
    uint16_t mod;          /* current key modifiers */
    uint8_t ascii_code;   /* character */

    char *title;
};
typedef struct event event_t;

#define EVENT_INIT(e,t)                 \
{                                       \
    (e)->type   = (t);                  \
    (e)->sender = gui_app_self();       \
    (e)->ack    = 0;      			    \
}                                       \

#define MOUSE_BUTTON_NONE         0x00
#define MOUSE_BUTTON_LEFT         0x01
#define MOUSE_BUTTON_RIGHT        0x02
#define MOUSE_BUTTON_BOTH         0x03

#define MOUSE_BUTTON_DOWN         0x10
#define MOUSE_BUTTON_UP           0x20

#ifdef __cplusplus
}
#endif

#endif /* __GUI_EVENT_H__ */

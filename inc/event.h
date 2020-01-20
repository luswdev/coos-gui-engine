/**
 *******************************************************************************
 * @file       event.h
 * @version    V0.6.1
 * @date       2020.01.20
 * @brief      Some system function for GUI engine's event.	
 *******************************************************************************
 */ 

#ifndef __COGUI_EVENT_H__
#define __COGUI_EVENT_H__

#ifdef __cplusplus
extern "C" {
#endif

struct cogui_app;
struct cogui_window;

/* applications event */
#define COGUI_EVENT_APP_CREATE          (co_uint8_t)0
#define COGUI_EVENT_APP_DELE            (co_uint8_t)1
#define COGUI_EVENT_APP_ACTIVATE        (co_uint8_t)2

/* widget event */
#define COGUI_EVENT_WIDGET_SHOW         (co_uint8_t)3
#define COGUI_EVENT_WIDGET_HIDE         (co_uint8_t)4
#define COGUI_EVENT_WIDGET_MOVE         (co_uint8_t)5

/* window event */
#define COGUI_EVENT_WINDOW_CREATE       (co_uint8_t)6
#define COGUI_EVENT_WINDOW_DELE         (co_uint8_t)7
#define COGUI_EVENT_WINDOW_SHOW         (co_uint8_t)8
#define COGUI_EVENT_WINDOW_HIDE         (co_uint8_t)9
#define COGUI_EVENT_WINDOW_CLOSE        (co_uint8_t)10
#define COGUI_EVENT_WINDOW_TITLE        (co_uint8_t)11

/* mouse and keyboard event */
#define COGUI_EVENT_MOUSE_MOTION        (co_uint8_t)12
#define COGUI_EVENT_MOUSE_BUTTON        (co_uint8_t)13
#define COGUI_EVENT_KBD                 (co_uint8_t)14
#define COGUI_EVENT_PAINT               (co_uint8_t)15
#define COGUI_EVENT_COMMAND             (co_uint8_t)16


struct cogui_event {
    co_uint8_t type;

    struct cogui_app *sender;

    OS_EventID ack;

    struct cogui_app *app;
    struct cogui_window *win;

    co_uint16_t x, y;
    co_uint16_t button;

    co_uint32_t id;

    co_uint32_t win_acti_cnt;

    co_uint16_t kbd_type;         /* key up or down */
    co_uint16_t key;          /* current key */
    co_uint16_t mod;          /* current key modifiers */
    co_uint16_t ascii_code;   /* character */

    char *title;
};

#define COGUI_EVENT_INIT(e,t)          \
{                                      \
    (e)->type   = (t);                 \
    (e)->sender = cogui_app_self();    \
    (e)->ack    = 0;      			   \
}                                      \


#define COGUI_MOUSE_BUTTON_LEFT         0x01
#define COGUI_MOUSE_BUTTON_RIGHT        0x02
#define COGUI_MOUSE_BUTTON_MIDDLE       0x03
#define COGUI_MOUSE_BUTTON_WHEELUP      0x04
#define COGUI_MOUSE_BUTTON_WHEELDOWN    0x08

#define COGUI_MOUSE_BUTTON_DOWN         0x10
#define COGUI_MOUSE_BUTTON_UP           0x20

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_EVENT_H__ */

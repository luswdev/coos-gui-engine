/**
 *******************************************************************************
 * @file       event.h
 * @version    V0.7.1
 * @date       2020.02.23
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
#define COGUI_EVENT_APP_CREATE          (uint8_t)0
#define COGUI_EVENT_APP_DELE            (uint8_t)1
#define COGUI_EVENT_APP_ACTIVATE        (uint8_t)2

/* widget event */
#define COGUI_EVENT_WIDGET_SHOW         (uint8_t)3
#define COGUI_EVENT_WIDGET_HIDE         (uint8_t)4
#define COGUI_EVENT_WIDGET_MOVE         (uint8_t)5

/* window event */
#define COGUI_EVENT_WINDOW_CREATE       (uint8_t)6
#define COGUI_EVENT_WINDOW_DELE         (uint8_t)7
#define COGUI_EVENT_WINDOW_SHOW         (uint8_t)8
#define COGUI_EVENT_WINDOW_HIDE         (uint8_t)9
#define COGUI_EVENT_WINDOW_CLOSE        (uint8_t)10
#define COGUI_EVENT_WINDOW_TITLE        (uint8_t)11

/* mouse and keyboard event */
#define COGUI_EVENT_MOUSE_MOTION        (uint8_t)12
#define COGUI_EVENT_MOUSE_BUTTON        (uint8_t)13
#define COGUI_EVENT_MOUSE_CLICK         (uint8_t)14
#define COGUI_EVENT_KBD                 (uint8_t)15
#define COGUI_EVENT_PAINT               (uint8_t)16
#define COGUI_EVENT_COMMAND             (uint8_t)17


struct cogui_event {
    uint8_t type;

    struct cogui_app *sender;

    OS_EventID ack;

    struct cogui_app *app;
    struct cogui_window *win;
    struct cogui_widget *widget;

    int32_t dx, dy;
    uint16_t button;

    uint32_t id;

    uint32_t win_acti_cnt;

    uint16_t kbd_type;         /* key up or down */
    uint16_t key;          /* current key */
    uint16_t mod;          /* current key modifiers */
    uint16_t ascii_code;   /* character */

    char *title;
};

#define COGUI_EVENT_INIT(e,t)          \
{                                      \
    (e)->type   = (t);                 \
    (e)->sender = cogui_app_self();    \
    (e)->ack    = 0;      			   \
}                                      \

#define COGUI_MOUSE_BUTTON_NONE         0x00
#define COGUI_MOUSE_BUTTON_LEFT         0x01
#define COGUI_MOUSE_BUTTON_RIGHT        0x02
#define COGUI_MOUSE_BUTTON_BOTH         0x03

#define COGUI_MOUSE_BUTTON_DOWN         0x10
#define COGUI_MOUSE_BUTTON_UP           0x20

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_EVENT_H__ */

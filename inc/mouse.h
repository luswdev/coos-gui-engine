/**
 *******************************************************************************
 * @file       mouse.h
 * @version    V0.6.1
 * @date       2020.01.20
 * @brief      The mouse action for gui engine.	
 *******************************************************************************
 */ 

#ifndef __COGUI_MOUSE_H__
#define __COGUI_MOUSE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define COGUI_MOUSE_SPEED_FAST      2
#define COGUI_MOUSE_SPEED_MIDDLE    4
#define COGUI_MOUSE_SPEED_SLOW      8

#define COGUI_CHECK_CURSOR()    \
{                               \
    if (_cursor == Co_NULL) {   \
        _cogui_mouse_init();    \
    }                           \
}                               \

struct cogui_cursor
{
    co_uint16_t cx, cy;

    co_uint8_t speed;

    cogui_widget_t *cursor_widget;
};

void cogui_mouse_set_position(co_uint16_t x, co_uint16_t y);
void cogui_mouse_set_speed(co_uint8_t speed);
void cogui_mouse_move_to(co_uint16_t x, co_uint16_t y);
void cogui_mouse_move_delta(co_int32_t dx,co_int32_t dy);

void cogui_mouse_restore(void);
void cogui_mouse_show(void);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_MOUSE_H__ */

/**
 *******************************************************************************
 * @file       mouse.h
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      The mouse action for gui engine.	
 *******************************************************************************
 */ 

#ifndef __GUI_MOUSE_H__
#define __GUI_MOUSE_H__

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

struct cursor
{
    uint16_t cx, cy;
    uint8_t speed;

    widget_t *cursor_widget;

    uint32_t frame_buffer;
    color_t save_picture[16][16]; 
};

void cogui_mouse_return_picture(void);

void cogui_mouse_set_position(uint16_t x, uint16_t y);
void cogui_mouse_set_speed(uint8_t speed);
void cogui_mouse_move_to(uint16_t x, uint16_t y);
void cogui_mouse_move_delta(int32_t dx,int32_t dy);

void gui_mouse_get_position(point_t *pt);

void cogui_mouse_restore(void);
void gui_mouse_show(void);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_MOUSE_H__ */

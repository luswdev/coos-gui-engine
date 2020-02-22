/**
 *******************************************************************************
 * @file       mouse.c
 * @version    V0.7.0
 * @date       2020.02.22
 * @brief      The mouse action for gui engine.	
 *******************************************************************************
 */ 

#include <cogui.h>

struct cogui_cursor *_cursor;
extern cogui_window_t *main_page;

void _cogui_mouse_init()
{
    _cursor = cogui_malloc(sizeof(struct cogui_cursor));
    COGUI_ASSERT(_cursor != Co_NULL);

    _cursor->cursor_widget = cogui_widget_create(main_page);
	cogui_widget_set_rectangle(_cursor->cursor_widget, 0, 0, 241, 321);
	_cursor->cursor_widget->gc.foreground = COGUI_WHITE;

    cogui_mouse_set_position(105, 155);
    cogui_mouse_set_speed(COGUI_MOUSE_SPEED_MIDDLE);
}

void cogui_mouse_set_position(co_uint16_t x, co_uint16_t y)
{
    COGUI_CHECK_CURSOR();

    _cursor->cx = x;
    _cursor->cy = y;
    
    cogui_mouse_show();
}

void cogui_mouse_set_speed(co_uint8_t speed)
{
    COGUI_CHECK_CURSOR();

    _cursor->speed = speed;
}

void cogui_mouse_move_to(co_uint16_t x,co_uint16_t y)
{
    COGUI_CHECK_CURSOR();

    if (x > 230) {
        x = 230;
    }
    if (y > 310) {
        y = 310;
    }

    cogui_mouse_restore();
    cogui_mouse_set_position(x, y);
}

void cogui_mouse_move_delta(co_int32_t dx,co_int32_t dy)
{
    COGUI_CHECK_CURSOR();
    
    co_int32_t x = _cursor->cx + dx/_cursor->speed;
    co_int32_t y = _cursor->cy + dy/_cursor->speed;

    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }

    if (x || y)
        cogui_mouse_move_to(x, y);
}

void cogui_mouse_restore(void)
{
    COGUI_CHECK_CURSOR();
}

void cogui_mouse_show(void)
{
    COGUI_CHECK_CURSOR();

    cogui_dc_draw_line(_cursor->cursor_widget->dc_engine, _cursor->cx,  _cursor->cx+10, _cursor->cy, _cursor->cy+10);
}

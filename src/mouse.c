/**
 *******************************************************************************
 * @file       mouse.c
 * @version    V0.7.1
 * @date       2020.02.23
 * @brief      The mouse action for gui engine.	
 *******************************************************************************
 */ 

#include <cogui.h>

struct cogui_cursor *_cursor=Co_NULL;
extern cogui_window_t *main_page;
bool_t first_show = 1;

void _cogui_mouse_init()
{
    _cursor = cogui_malloc(sizeof(struct cogui_cursor));
    COGUI_ASSERT(_cursor != Co_NULL);

    cogui_memset(_cursor, 0, sizeof(struct cogui_cursor));

    _cursor->cursor_widget = cogui_widget_create(main_page);
	cogui_widget_set_rectangle(_cursor->cursor_widget, 0, 0, 240, 320);
    cogui_widget_set_font(_cursor->cursor_widget, &tm_symbol_16x16);

    _cursor->frame_buffer = ((struct cogui_dc_hw *)(_cursor->cursor_widget->dc_engine))->hw_driver->frame_buffer;

    first_show = 1;

    cogui_mouse_set_speed(COGUI_MOUSE_SPEED_MIDDLE);
    cogui_mouse_set_position(105, 155);
}

void cogui_mouse_return_picture(void)
{
    COGUI_CHECK_CURSOR();
    uint16_t i, j;

    for (i=0; i<16; i++) {
        for (j=0; j<16; j++) {
            cogui_dc_draw_point(_cursor->cursor_widget->dc_engine, _cursor->cx+j, _cursor->cy+i, _cursor->save_picture[i][j]);
        }
    }
}

void cogui_mouse_set_position(uint16_t x, uint16_t y)
{
    COGUI_CHECK_CURSOR();

    _cursor->cx = x;
    _cursor->cy = y;
    
    cogui_mouse_show();
}

void cogui_mouse_set_speed(uint8_t speed)
{
    COGUI_CHECK_CURSOR();

    _cursor->speed = speed;
}

void cogui_mouse_move_to(uint16_t x,uint16_t y)
{
    COGUI_CHECK_CURSOR();

    if (x > 238) {
        x = 238;
    }
    if (y > 318) {
        y = 318;
    }

    if (_cursor->cx == x && _cursor->cy == y) {
        return;
    }

    if (!first_show) {
        cogui_mouse_return_picture();
    }

    cogui_mouse_set_position(x, y);
}

void cogui_mouse_move_delta(int32_t dx,int32_t dy)
{
    COGUI_CHECK_CURSOR();
    
    int32_t x = _cursor->cx + dx/_cursor->speed;
    int32_t y = _cursor->cy + dy/_cursor->speed;

    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }

    cogui_mouse_move_to(x, y);
}

void cogui_mouse_get_position(cogui_point_t *pt)
{
    pt->x = _cursor->cx;
    pt->y = _cursor->cy;
}

void cogui_mouse_restore(void)
{
    COGUI_CHECK_CURSOR();
    uint32_t start_pt = _cursor->frame_buffer;
    uint16_t i, j;
    uint16_t buf;

    for (i=0; i<16; i++) {
        start_pt = _cursor->frame_buffer + 2*(240*(_cursor->cy+i) + _cursor->cx);
        for (j=0; j<16; j++) {
            buf = *(uint16_t *)start_pt;
            _cursor->save_picture[i][j] = buf;
            start_pt += 2;
        }
    }
    first_show = 0;
}

void cogui_mouse_show(void)
{
    COGUI_CHECK_CURSOR();

    cogui_mouse_restore();

    cogui_rect_t rect;
    COGUI_SET_RECT(&rect, _cursor->cx, _cursor->cy, 16, 16);

	_cursor->cursor_widget->gc.foreground = white;
    cogui_dc_draw_text(_cursor->cursor_widget->dc_engine, &rect, "#");
	_cursor->cursor_widget->gc.foreground = black;
    cogui_dc_draw_text(_cursor->cursor_widget->dc_engine, &rect, "$");
}

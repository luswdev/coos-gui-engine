/**
 *******************************************************************************
 * @file       mouse.c
 * @version    V0.0.1   
 * @date       2019.8.9
 * @brief      The mouse action for gui engine.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"

struct cogui_cursor *_cursor;

void cogui_mouse_init();

void cogui_mouse_set_pos(S32 x, S32 y)
{
    _cursor->cx = x;
    _cursor->cy = y;
}

void cogui_mouse_move_to(S32 x,S32 y)
{

}
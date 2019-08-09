/**
 *******************************************************************************
 * @file       mouse.c
 * @version    V0.0.1   
 * @date       2019.5.23
 * @brief      The mouse action for gui engine.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"

struct guiCursor *_cursor;

void MouseInit();

void MouseSetPos(S32 x, S32 y)
{
    _cursor->cx = x;
    _cursor->cy = y;
}

void MouseMoveTo(S32 x,S32 y)
{

}
/**
 *******************************************************************************
 * @file       mouse.c
 * @version    V0.0.1   
 * @date       2019.5.23
 * @brief      The mouse action for gui engine.	
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "cogui.h"

/*---------------------------- Variable Define -------------------------------*/
struct guiCursor *_cursor;

void MouseInit();

void MouseSetPos(S32 x, S32 y)
{
    /* move current cursor */
    _cursor->cx = x;
    _cursor->cy = y;
}

void MouseMoveTo(S32 x,S32 y)
{

}
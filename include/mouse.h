/**
 *******************************************************************************
 * @file       mouse.h
 * @version    V0.0.1   
 * @date       2019.5.23
 * @brief      The mouse action for gui engine.	
 *******************************************************************************
 */ 

#ifndef _COGUI_MOUSE_H
#define _COGUI_MOUSE_H

/*---------------------------- structure -------------------------------------*/
struct guiCursor
{
    /* current cursor x and y */
    U16 cx, cy;
};

void MouseSetPos(S32 x, S32 y);
void MouseMoveTo(S32 x, S32 y);

#endif /* _COGUI_MOUSE_H */

/**
 *******************************************************************************
 * @file       mouse.h
 * @version    V0.0.1   
 * @date       2019.8.9
 * @brief      The mouse action for gui engine.	
 *******************************************************************************
 */ 

#ifndef _COGUI_MOUSE_H
#define _COGUI_MOUSE_H

/*---------------------------- structure -------------------------------------*/
struct cogui_couser
{
    U16 cx, cy;
};

void cogui_mouse_set_pos(S32 x, S32 y);
void cogui_mouse_move_to(S32 x, S32 y);

#endif /* _COGUI_MOUSE_H */

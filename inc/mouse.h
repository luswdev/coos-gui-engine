/**
 *******************************************************************************
 * @file       mouse.h
 * @version    V0.0.2 
 * @date       2020.01.20
 * @brief      The mouse action for gui engine.	
 *******************************************************************************
 */ 

#ifndef __COGUI_MOUSE_H__
#define __COGUI_MOUSE_H__

#ifdef __cplusplus
extern "C" {
#endif

struct cogui_couser
{
    U16 cx, cy;
};

void cogui_mouse_set_pos(S32 x, S32 y);
void cogui_mouse_move_to(S32 x, S32 y);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_MOUSE_H__ */

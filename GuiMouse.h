/**
 *******************************************************************************
 * @file       GuiMouse.h
 * @version    V0.0.1   
 * @date       2019.5.23
 * @brief      The mouse action for gui engine.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "GuiSystem.h"
#include "GuiDriver.h"

struct guiCursor
{
    /* current cursor x and y */
    U16 cx, cy;
}

void MouseSetPos(S32 x, S32 y);

/**
 *******************************************************************************
 * @file       topwin.c
 * @version    V0.0.1   
 * @date       2019.5.24
 * @brief      The top window management for gui engine.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "GuiTopwin.h"

CoList _guiTopwinList;

P_TopWin _getTopwinFromTree(P_CoList list, S32 x, S32 y)
{
    P_CoList node;

    for(node=list->next; node != list; node=node->next){

    }
}

P_TopWin GetTopWin(S32 x, S32 y)
{
    return _getTopwinFromTree(_guiTopwinList, x, y);
}
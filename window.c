/**
 ********************************************************************************
 * @file       window.c
 * @version    V0.0.1   
 * @date       2019.5.23
 * @brief      Some system function for GUI engine's event.	
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "cogui.h"

S32 _InitWin(P_GuiWin win, P_GuiWin parentWindow, U8 *title, P_GuiRect rect, U16 style)
{
    if (win==Co_NULL){
        return -1;
    }

    /* set parent window */
    win->parentWindow = parentWindow;

    /* set title, rect and style */
    if (title != RT_NULL){
        win->title = title;
    }
    else{
        win->title = RT_NULL;
    }

    WidgetSetRect((P_GuiWidget)win, rect);
    win->style = style;

    if (!((style & GUI_WIN_STYLE_NO_TITLE) && (style & GUI_WIN_STYLE_NO_BORDER))){
        
    }
}

P_GuiWin WinCreate(P_GuiWin parentWindow, U8 *title, P_GuiRect rect, U16 style)
{
    P_GuiWin win;

    win = GuiMalloc(sizeof(Guiwin))
    if(win==Co_NULL){
        return Co_NULL;
    }
    
    if(_InitWin(win, parentWindow, title, rect, style)!=0){
        WinDele(win);
        return Co_NULL;
    }

    return win;
}

void WinDele(P_GuiWin win)
{

}
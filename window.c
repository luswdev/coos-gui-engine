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

StatusType _WinCreateInServer(P_GuiWin win){
    if(!(win->flag & RTGUI_WIN_FLAG_CONNECTED)){
        struct eventWinCreate event;

        GUI_EVENT_INIT(&event, GUI_EVENT_WIN_CREATE);

        /* send win create event to server */
        event.parent_window = win->parent_window;
        event.win           = win;
        event.parent.user   = win->style;

        if(ServerPostEvent((struct GuiEvent *)&event)!=E_OK){
            return Co_FALSE;
        }
    }

    return Co_TRUE;
}

S32 _InitWin(P_GuiWin win, P_GuiWin parentWindow, U8 *title, P_GuiRect rect, U16 style)
{
    if(win==Co_NULL){
        return -1;
    }

    /* set parent window */
    win->parentWindow = parentWindow;

    /* set title, rect and style */
    if(title != RT_NULL){
        win->title = title;
    }
    else{
        win->title = RT_NULL;
    }

    WidgetSetRect((P_GuiWidget)win, rect);
    win->style = style;

    if(!((style & GUI_WIN_STYLE_NO_TITLE) && (style & GUI_WIN_STYLE_NO_BORDER))){
        GuiRect trect = *rect;

        win->_titleWgt = GuiMalloc(sizeof(GuiWidget));
        if(win->_titleWgt != Co_NULL){
            win->_titleWgt->topLevel = win;
        }
        else{
            return -1;
        }

        if(!(style & GUI_WIN_STYLE_NO_BORDER)){
            RectInflate(&trect, WINTITLE_BORDER_SIZE);
        }
        if(!(style & GUI_WIN_STYLE_NO_TITLE)){
            trect.y1 -= WINTITLE_HEIGHT;
        }
        WinSetRect(win->_title_wgt, &trect);

        /* Update the clip of the wintitle manually. */
        RegionSubtractRect(&win->_title_wgt->clip, &win->_title_wgt->clip,(P_GuiWidget)&win->extent);

        /* The window title is always un-hidden for simplicity. */
        WidgetShow(win->_title_wgt);
        RegionInitWithExtents(&win->outerClip, &trect);
        win->outerExtent = trect;
    }
    else{
        RegionInitWithExtents(&win->outer_clip, rect);
        win->outerExtent = *rect;
    }

    if(_WinCreateInServer(win) == Co_FALSE){
        return -1;
    }

    win->app->winCnt++;
    return 0;
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
    win->magic = 0;

    /* close the window first if it's not. */
    if(!(win->flag & GUI_WIN_FLAG_CLOSED)){
        struct eventWin event;

        GUI_EVENT_INIT(&event, GUI_EVENT_WIN_CLOSE);
        event.win = win; 

        if(win->style & GUI_WIN_STYLE_DESTROY_ON_CLOSE){
            _WinDealClose(win, (struct GuiEvent *)&eclose, Co_TRUE);
            return 0;
        }
        else{
            _WinDealClose(win, (struct GuiEvent *)&eclose, Co_TRUE);
        }
    }
}

StatusType _WinDealClose(P_GuiWin win, struct GuiEvent *event, StatusType force_close)
{
    if(win->onClose != Co_NULL){
        if ((win->onClose((P_GuiWidget)(win), event) == Co_FALSE) && !force_close){
            return Co_FALSE;
        }
    }

    WinHide(win);

    win->flag |= GUI_WIN_FLAG_CLOSED;

    win->app->winCnt--;
    if(win->app->winCnt == 0 && !(win->app->flag & GUI_APP_FLAG_KEEP)){
        ExitApp(AppSelf(), 0);
    }

    if (win->style & GUI_WIN_STYLE_DESTROY_ON_CLOSE){
        WinDele(win);
    }

    return Co_TRUE;
}

StatusType WinClose(P_GuiWin win)
{
    struct eventWin event;

    GUI_EVENT_INIT(&event, GUI_EVENT_WIN_CLOSE);
    event.win = win;

    return _rtgui_win_deal_close(win, (struct GuiEvent *)&event, Co_FALSE);
}

U64 WinDoShow(P_GuiWin win)
{

}

U64 WinShow(P_GuiWin win, StatusType is_modal)
{
    
}

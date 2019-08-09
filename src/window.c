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

/**
 *******************************************************************************
 * @brief      create window in server
 * @param[in]  win      window ptr		
 * @param[out] None
 * @retval     Co_FALSE     failed		 
 * @retval     Co_TRUE      success		 
 *
 * @par Description
 * @details    This function is called to create a window in server.
 *******************************************************************************
 */
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

/**
 *******************************************************************************
 * @brief      inital window
 * @param[in]  win              window ptr		
 * @param[in]  parentWindow     parent window ptr		
 * @param[in]  rect             window rect		
 * @param[in]  style            window style		
 * @param[out] None
 * @retval     -1               bad		 
 * @retval     0                good		 
 *
 * @par Description
 * @details    This function is called to inital a window.
 *******************************************************************************
 */
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

/**
 *******************************************************************************
 * @brief      create window	
 * @param[in]  parentWindow     parent window ptr		
 * @param[in]  rect             window rect		
 * @param[in]  style            window style		
 * @param[out] None
 * @retval     win              window ptr		 
 * @retval     Co_NULL          failed	 
 *
 * @par Description
 * @details    This function is called to create a window.
 *******************************************************************************
 */
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

/**
 *******************************************************************************
 * @brief      delete window	
 * @param[in]  win      window ptr		
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to delete a window.
 *******************************************************************************
 */
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

/**
 *******************************************************************************
 * @brief      close window
 * @param[in]  win              window ptr		
 * @param[in]  event            event ptr		
 * @param[in]  force_close      need to force close?		
 * @param[out] None
 * @retval     Co_FALSE		    bad
 * @retval     Co_TRUE		    good
 *
 * @par Description
 * @details    This function is called to close a window.
 *******************************************************************************
 */
StatusType _WinDealClose(P_GuiWin win, struct GuiEvent *event, StatusType forceClose)
{
    if(win->onClose != Co_NULL){
        if ((win->onClose((P_GuiWidget)(win), event) == Co_FALSE) && !forceClose){
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

/**
 *******************************************************************************
 * @brief      close window
 * @param[in]  win              window ptr			
 * @param[out] None
 * @retval     Co_FALSE		    bad
 * @retval     Co_TRUE		    good	 
 *
 * @par Description
 * @details    This function is called to close a window.
 *******************************************************************************
 */
StatusType WinClose(P_GuiWin win)
{
    struct eventWin event;

    GUI_EVENT_INIT(&event, GUI_EVENT_WIN_CLOSE);
    event.win = win;

    return _rtgui_win_deal_close(win, (struct GuiEvent *)&event, Co_FALSE);
}

/**
 *******************************************************************************
 * @brief      let window show (system function)
 * @param[in]  win              window ptr		
 * @param[out] None
 * @retval     -1		 
 *
 * @par Description
 * @details    This function is called to let a window show.
 *******************************************************************************
 */
U64 WinDoShow(P_GuiWin win)
{
    U16 exitCode = -1;
    P_GuiApp app;
    struct eventWin event;

    GUI_EVENT_INIT(&event, GUI_EVENT_WIN_SHOW);
    event.win = win;

    if(win==Co_NULL){
        return exitCode;
    }

    win->flag &= ~GUI_WIN_FLAG_CLOSED;
    win->flag &= ~GUI_WIN_FLAG_CB_PRESSED;

    if (!(win->flag & GUI_WIN_FLAG_CONNECTED)){
        if (_WinCreateInServer(win) == Co_FALSE){
            return exitCode;
        }
    } 

    /* set window unhidden before notify the server */
    WidgetShow((P_GuiWidget)win);

    if(ServerPostEvent((struct GuiEvent *)&eshow) != E_OK){
        /* It could not be shown if a parent window is hidden. */
        WidgetHide((P_GuiWidget)win);
        return exitCode;
    }

    if (win->focused_widget == Co_NULL){
        WidgetFocus((P_GuiWidget)win);
    }

    app = win->app;
    if(app == RT_NULL){
        return exitCode;
    }

    return exitCode;
}

/**
 *******************************************************************************
 * @brief      let window show
 * @param[in]  win              window ptr		
 * @param[out] None
 * @retval     -1		 
 *
 * @par Description
 * @details    This function is called to let a window show.
 *******************************************************************************
 */
U64 WinShow(P_GuiWin win)
{
    (P_GuiWidget)win->flag |= GUI_WIDGET_FLAG_SHOWN;

    win->magic = GUI_WIN_MAGIC;

    if(win->_doShow){
        return win->_doShow(win);
    }

    return WinDoShow(win)
}

/**
 *******************************************************************************
 * @brief      let window hide
 * @param[in]  win              window ptr		
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to let a window hide.
 *******************************************************************************
 */
void WinHide(P_GuiWin win)
{
    if(win==Co_NULL){
        return;
    }

    if(!((P_GuiWidget)win->flag & GUI_WIDGET_FLAG_SHOWN) && win->flag & GUI_WIN_FLAG_CONNECTED){
        /* send hidden message to server */
        struct eventWin event;
        GUI_EVENT_INIT(&event, GUI_EVENT_WIN_HIDE);
        event.win = win;

        if (ServerPostEvent((struct GuiEvent *)&event) != E_OK){
            return;
        }

        WidgetHide((P_GuiWidget)win);
        win->flag &= ~GUI_WIN_FLAG_ACTIVATE;
    }
}

/**
 *******************************************************************************
 * @brief      update window's clip
 * @param[in]  win              window ptr		
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to update window's clip.
 *******************************************************************************
 */
void WinUpdateClip(P_GuiWin win)
{
    P_GuiContainer cnt;
    P_CoSList node;

    if(win==Co_NULL){
        return;
    }

    if(win&GUI_WIN_FLAG_CLOSED){
        return;
    }

    if(win->_titleWgt){
        /* Reset the inner clip of title. */
        win->_titleWgt->extent = win->outerExtent;
        RegionCopy(&win->_titleWgt->clip, &win->outerClip);
        RegionSubtractRect(&win->_titleWgt->clip, &win->_titleWgt->clip, (P_GuiWidget)win->extent);

        /* Reset the inner clip of window. */
        RegionIntersectRect(&(P_GuiWidget)win->clip, &win->outerClip, &(P_GuiWidget)win->extent);
    }
    else{
        (P_GuiWidget)win->extent = win->outerExtent;
        RegionCopy(&(P_GuiWidget)win->clip, &win->outerClip);
    }

    /* update the clip info of each child */
    cnt = (P_GuiContainer)win;
    for(node=&cnt->children->next; node!=Co_NULL; node=node->next){
        P_GuiWidget child = (P_GuiWidget)node->sibling;

        WidgetUpdateClip(child);
    }
}

/**
 *******************************************************************************
 * @brief      active window
 * @param[in]  win              window ptr		
 * @param[out] None
 * @retval     E_NOSYS      if cannot find server app
 * @retval     E_ERROR      if post failed
 * @retval     E_OK         if post success			 
 *
 * @par Description
 * @details    This function is called to active a window.
 *******************************************************************************
 */
StatusType WinActivate(P_GuiWin win)
{
    struct eventWin event;
    GUI_EVENT_INIT(&event, GUI_EVENT_WIN_ACTIVATE);
    event.win = win;

    return ServerPostEvent((struct GuiEvent *)&event);
}

/**
 *******************************************************************************
 * @brief      check if window is active 
 * @param[in]  win              window ptr		
 * @param[out] None
 * @retval     Co_TRUE          success		 
 * @retval     Co_FALSE         failed		 
 *
 * @par Description
 * @details    This function is called to check if window is active .
 *******************************************************************************
 */
StatusType WinIsActivated(P_GuiWin win)
{
    if(win == Co_NULL){
        return RT_FALSE;
    }

    if (win->flag & GUI_WIN_FLAG_ACTIVATE){
        return Co_TRUE;
    }

    return Co_FALSE;
}

/**
 *******************************************************************************
 * @brief      move window
 * @param[in]  win              window ptr
 * @param[in]  x                position x
 * @param[in]  y                position y
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to move a window.
 *******************************************************************************
 */
void WinMove(P_GuiWin win, S32 x, S32 y)
{
    P_GuiWidget widget;
    struct eventWinMove event;
    S32 dx, dy;

    GUI_EVENT_INIT(&event, GUI_EVENT_WIN_MOVE);

    if(win==Co_NULL){
        return;
    }

    if(win->_titleWgt){
        widget = win->_titleWgt;
        dx = x - widget->extent.x;
        dy = y - widget->extent.y;
        WidgetMoveToLogic(widget, dx, dy);

        widget = (P_GuiWidget)win;
        WidgetMoveToLogic(widget, dx, dy);
    }
    else{
        widget = (P_GuiWidget)win;
        dx = x - widget->extent.x;
        dy = y - widget->extent.y;
        WidgetMoveToLogic(widget, dx, dy);
    }
    RectMove(&win->outerExtent, dx, dy);

    if(win->flag & GUI_WIN_FLAG_CONNECTED){
        WidgetHide((P_GuiWidget)win);

        event.win = win;
        event.x   = x;
        event.y   = y;
        if(ServerPostEvent((struct event *)&event)!=E_OK){
            return;
        }
    }

    WidgetShow((P_GuiWidget)win);
}

/**
 *******************************************************************************
 * @brief      window's event handler
 * @param[in]  win              window ptr		
 * @param[in]  event            event ptr		
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to window's event handler.
 *******************************************************************************
 */
StatusType WinEventHandler(P_GuiWidget win, struct GuiEvent *event)
{
    P_GuiWin window;

    if(win==Co_NULL || event==Co_NULL){
        return Co_FALSE;
    }

    window = (P_GuiWin)win;

    switch (event->type){
    case GUI_EVENT_WIN_SHOW:
        WinDoShow(win);
        break;

    case GUI_EVENT_WIN_HIDE:
        WinHide(win);
        break;

    case GUI_EVENT_WIN_CLOSE:
        _WinDealClose(win, event, Co_FALSE);
        /* don't broadcast WIN_CLOSE event to others */
        return Co_TRUE;

    case GUI_EVENT_WIN_MOVE:
    {
        struct eventWinMove *emove = (struct eventWinMove *)event;

        /* move window */
        WinMove(win, emove->x, emove->y);
    }
    break;

    case GUI_EVENT_WIN_ACTIVATE:
        if(!((P_GuiWidget)win->flag & GUI_WIDGET_FLAG_SHOWN)){
            /* activate a hide window */
            return Co_TRUE;
        }

        win->flag |= GUI_WIN_FLAG_ACTIVATE;
        /* There are many cases where the paint event will follow this activate
         * event and just repaint the title is not a big deal. So just repaint
         * the title if there is one. If you want to update the content of the
         * window, do it in the on_activate callback.*/
        if (win->_titleWgt)
            WidgetUpdate(win->_titleWgt);

        if (win->onActivate != Co_NULL)
        {
            win->onActivate((P_GuiWidget)win, event);
        }
        break;

    default:
        break;
    }

    return Co_FALSE;
}

/**
 *******************************************************************************
 * @brief      resize window
 * @param[in]  win              window ptr		
 * @param[in]  rect             new size	
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to resize window.
 *******************************************************************************
 */
void WinSetRect(P_GuiWin win, P_GuiRect rect)
{
    struct eventWinResize event;

    if(win==Co_NULL || rect==Co_NULL){
        return;
    }

    (P_GuiWidget)win->extent = *rect;

    if(win->flag&GUI_WIN_FLAG_CONNECTED){
        /* set window resize event to server */
        GUI_EVENT_INIT(&event, GUI_EVENT_WIN_RESIZE);
        event.win = win;
        event.rect = *rect;

        ServerPostEvent(&(struct GuiEvent *)event);
    }
}

/**
 *******************************************************************************
 * @brief      set window's onactivate handler
 * @param[in]  win              window ptr		
 * @param[in]  handler          handler function	
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set window's onactivate handler.
 *******************************************************************************
 */
void WinSetOnactivate(P_GuiWin win, EventHandlerPtr handler)
{
    if(win!=Co_NULL){
        win->onActivate = handler;
    }
}

/**
 *******************************************************************************
 * @brief      set window's ondeactivate handler
 * @param[in]  win              window ptr		
 * @param[in]  handler          handler function	
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set window's ondeactivate handler.
 *******************************************************************************
 */
void WinSetOndeactivate(P_GuiWin win, EventHandlerPtr handler)
{
    if(win!=Co_NULL){
        win->onDeactivate = handler;
    }
}

/**
 *******************************************************************************
 * @brief      set window's onclose handler
 * @param[in]  win              window ptr		
 * @param[in]  handler          handler function	
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set window's onclose handler.
 *******************************************************************************
 */
void WinSetOnclose(P_GuiWin win, EventHandlerPtr handler)
{
    if(win!=Co_NULL){
        win->onClose = handler;
    }
}

/**
 *******************************************************************************
 * @brief      set window's onkey handler
 * @param[in]  win              window ptr		
 * @param[in]  handler          handler function	
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set window's onkey handler.
 *******************************************************************************
 */
void WinSetOnkey(P_GuiWin win, EventHandlerPtr handler)
{
    if(win!=Co_NULL){
        win->onKey = handler;
    }
}

/**
 *******************************************************************************
 * @brief      set window's title
 * @param[in]  win              window ptr		
 * @param[in]  title            title	
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to set window's title.
 *******************************************************************************
 */
void WinSetTitle(P_GuiWin win, const U8 *title)
{
    /* send title to server */
    if(win->flag & GUI_WIN_FLAG_CONNECTED){
        struct eventWinSetTitle event;

        GUI_EVENT_INIT(&event, GUI_EVENT_WIN_TITLE);

        event.win = win;
        event.title = title;

        ServerPostEvent(&(struct GuiEvent *)event);
    }

    /* modify in local side */
    if(win->title != Co_NULL){
        GuiFree(win->title);
        win->title = Co_NULL;
    }

    if(title != Co_NULL){
        win->title = title;
    }
}

/**
 *******************************************************************************
 * @brief      get window's title
 * @param[in]  win              window ptr		
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is called to get window's title.
 *******************************************************************************
 */
U8 *WinGetTitle(P_GuiWin win)
{
    if(win!=Co_NULL){
        return win->title;
    }
}

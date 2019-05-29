/**
 *******************************************************************************
 * @file       GuiWindow.h
 * @version    V0.0.1   
 * @date       2019.5.23
 * @brief      Some system function for GUI engine's event.	
 *******************************************************************************
 */ 

#ifndef _GUI_WINDOW_H
#define _GUI_WINDOW_H

#define GUI_WIN_STYLE_NO_FOCUS            0x0001  /* non-focused window            */
#define GUI_WIN_STYLE_NO_TITLE            0x0002  /* no title window               */
#define GUI_WIN_STYLE_NO_BORDER           0x0004  /* no border window              */
#define GUI_WIN_STYLE_CLOSEBOX            0x0008  /* window has the close button   */
#define GUI_WIN_STYLE_MINIBOX             0x0010  /* window has the mini button    */

#define GUI_WIN_STYLE_DESTROY_ON_CLOSE    0x0020  /* window is destroyed when closed */
#define GUI_WIN_STYLE_ONTOP               0x0040  /* window is in the top layer    */
#define GUI_WIN_STYLE_ONBTM               0x0080  /* window is in the bottom layer */
#define GUI_WIN_STYLE_MAINWIN             0x0106  /* window is a main window       */

#define GUI_WIN_MAGIC					  0xA5A55A5A		/* win magic flag */

#define WINTITLE_HEIGHT         20
#define WINTITLE_CB_WIDTH       16
#define WINTITLE_CB_HEIGHT      16
#define WINTITLE_BORDER_SIZE    2

enum guiWinFlag
{
    GUI_WIN_FLAG_INIT        = 0x00,  /* init state              */
    GUI_WIN_FLAG_MODAL       = 0x01,  /* modal mode window       */
    GUI_WIN_FLAG_CLOSED      = 0x02,  /* window is closed        */
    GUI_WIN_FLAG_ACTIVATE    = 0x04,  /* window is activated     */
    GUI_WIN_FLAG_UNDER_MODAL = 0x08,  /* window is under modal
                                           show(modaled by other)  */
    GUI_WIN_FLAG_CONNECTED   = 0x10,  /* connected to server */
    /* window is event_key dispatcher(dispatch it to the focused widget in
     * current window) _and_ a key handler(it should be able to handle keys
     * such as ESC). Both of dispatching and handling are in the same
     * function(rtgui_win_event_handler). So we have to distinguish between the
     * two modes.
     *
     * If this flag is set, we are in key-handling mode.
     */
    GUI_WIN_FLAG_HANDLE_KEY  = 0x20,

    GUI_WIN_FLAG_CB_PRESSED  = 0x40,
};

/*---------------------------- structure -------------------------------------*/
typedef struct window
{
    GuiContainer parent;

    /* update count */
    S64 update;

    /* drawing count */
    S64 drawing;
    GuiRect drawingRect;

    /* parent window. Co_NULL if the window is a top level window */
    struct window *parentWindow;

    GuiRegion outerClip;
    GuiRect outerExtent;

    P_GuiWidget foucsWidget;

    /* which app I belong */
    P_GuiApp app;

    /* window style */
    U16 style;

    /* window state flag */
    enum guiWinFlag flag

    /* last mouse event handled widget */
    P_GuiWidget lastMeventWidget;

    /* window title */
    U8 *title;
    P_GuiWidget _titleWgt;

    /* call back */
    StatusType (*onActivate)(P_GuiWidget widget, struct GuiEvent *event);
    StatusType (*onDeactivate)(P_GuiWidget widget, struct GuiEvent *event);
    StatusType (*onClose)(P_GuiWidget widget, struct GuiEvent *event);

    StatusType (*onKey)(P_GuiWidget widget, struct GuiEvent *event);

    /* reserved user data */
    void *userData;

    /* Private data */
    S64 (*_doShow)(struct window *win);

    /* app ref_count */
    U16 appRefCnt;

    /* win magic flag, magic value is 0xA5A55A5A */
    U32	magic;

}GuiWin,*P_GuiWin;

/*---------------------------- Function Define -------------------------------*/
P_GuiWin WinCreate(P_GuiWin parentWindow, U8 *title, P_GuiRect rect, U16 style);
void WinDele(P_GuiWin win);

StatusType WinClose(P_GuiWin win);

U64 WinShow(P_GuiWin win);
U64 WinDoShow(P_GuiWin win);

void WinHide(P_GuiWin win);

StatusType WinActivate(P_GuiWin win);
StatusType WinIsActivated(P_GuiWin win);

void WinMove(P_GuiWin win, S32 x, S32 y);

/* reset extent of window */
void WinSetRect(P_GuiWin win, P_GuiRect rect);
void WinUpdateClip(P_GuiWin win);

void WinSetOnactivate(P_GuiWin win, EventHandlerPtr handler);
void WinSetOndeactivate(P_GuiWin win, EventHandlerPtr handler);
void WinSetOnclose(P_GuiWin win, EventHandlerPtr handler);
void WinSetOnkey(P_GuiWin win, EventHandlerPtr handler);

StatusType WinEventHandler(P_GuiWidget win, struct GuiEvent *event);

void WinSetRect(P_GuiWin win, P_GuiRect rect);
void WinSetTitle(P_GuiWin win, const U8 *title);
U8 *WinGetTitle(P_GuiWin win);

P_GuiWin WinGetTopmostShown(void);
P_GuiWin WinGetNextShown(void);

#endif /* _GUI_WINDOW_H */
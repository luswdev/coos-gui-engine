/**
 *******************************************************************************
 * @file       window.h
 * @version    V0.0.1   
 * @date       2019.5.23
 * @brief      Some system function for GUI engine's event.	
 *******************************************************************************
 */ 

#ifndef _COGUI_WINDOW_H
#define _COGUI_WINDOW_H

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

P_GuiWin WinCreate(P_GuiWin parentWindow, U8 *title, P_GuiRect rect, U16 style);
void WinDele(P_GuiWin win);

StatusType WinClose(P_GuiWin win);

U64 WinShow(P_GuiWin win);
U64 WinDoShow(P_GuiWin win);

void WinHide(P_GuiWin win);

StatusType WinActivate(P_GuiWin win);
StatusType WinIsActivated(P_GuiWin win);

void WinMove(P_GuiWin win, S32 x, S32 y);

void WinSetRect(P_GuiWin win, P_GuiRect rect);
void WinUpdateClip(P_GuiWin win);

void WinSetOnactivate(P_GuiWin win, EventHandlerPtr handler);
void WinSetOndeactivate(P_GuiWin win, EventHandlerPtr handler);
void WinSetOnclose(P_GuiWin win, EventHandlerPtr handler);
void WinSetOnkey(P_GuiWin win, EventHandlerPtr handler);

StatusType WinEventHandler(cogui_widget_t * win, struct GuiEvent *event);

void WinSetRect(P_GuiWin win, P_GuiRect rect);
void WinSetTitle(P_GuiWin win, const U8 *title);
U8 *WinGetTitle(P_GuiWin win);

P_GuiWin WinGetTopmostShown(void);
P_GuiWin WinGetNextShown(void);

#endif /* _COGUI_WINDOW_H */

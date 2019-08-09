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

#define COGUI_WIN_STYLE_NO_FOCUS            0x0001  /* non-focused window            */
#define COGUI_WIN_STYLE_NO_TITLE            0x0002  /* no title window               */
#define COGUI_WIN_STYLE_NO_BORDER           0x0004  /* no border window              */
#define COGUI_WIN_STYLE_CLOSEBOX            0x0008  /* window has the close button   */
#define COGUI_WIN_STYLE_MINIBOX             0x0010  /* window has the mini button    */

#define COGUI_WIN_STYLE_DESTROY_ON_CLOSE    0x0020  /* window is destroyed when closed */
#define COGUI_WIN_STYLE_ONTOP               0x0040  /* window is in the top layer    */
#define COGUI_WIN_STYLE_ONBTM               0x0080  /* window is in the bottom layer */
#define COGUI_WIN_STYLE_MAINWIN             0x0106  /* window is a main window       */

#define COGUI_WIN_MAGIC					  0xA5A55A5A		/* win magic flag */

#define COWINTITLE_HEIGHT         20
#define COWINTITLE_CB_WIDTH       16
#define COWINTITLE_CB_HEIGHT      16
#define COWINTITLE_BORDER_SIZE    2

cogui_window_t *WinCreate(cogui_window_t *parentWindow, U8 *title, cogui_rect_t *rect, U16 style);
void WinDele(cogui_window_t *win);

StatusType WinClose(cogui_window_t *win);

U64 WinShow(cogui_window_t *win);
U64 WinDoShow(cogui_window_t *win);

void WinHide(cogui_window_t *win);

StatusType WinActivate(cogui_window_t *win);
StatusType WinIsActivated(cogui_window_t *win);

void WinMove(cogui_window_t *win, S32 x, S32 y);

void WinSetRect(cogui_window_t *win, cogui_rect_t *rect);
void WinUpdateClip(cogui_window_t *win);

void WinSetOnactivate(cogui_window_t *win, event_handler_ptr handler);
void WinSetOndeactivate(cogui_window_t *win, event_handler_ptr handler);
void WinSetOnclose(cogui_window_t *win, event_handler_ptr handler);
void WinSetOnkey(cogui_window_t *win, event_handler_ptr handler);

StatusType WinEventHandler(cogui_widget_t * win, struct cogui_event *event);

void WinSetRect(cogui_window_t *win, cogui_rect_t *rect);
void WinSetTitle(cogui_window_t *win, const U8 *title);
U8 *WinGetTitle(cogui_window_t *win);

cogui_window_t *WinGetTopmostShown(void);
cogui_window_t *WinGetNextShown(void);

#endif /* _COGUI_WINDOW_H */

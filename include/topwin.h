/**
 *******************************************************************************
 * @file       topwin.h
 * @version    V0.0.2   
 * @date       2019.9.29
 * @brief      The top window management for gui engine.	
 *******************************************************************************
 */ 

#ifndef _COGUI_TOPWIN_H
#define _COGUI_TOPWIN_H

struct cogui_topwin
{
    /* the window id */
    cogui_window_t *wid;

    /* which app belong */
    cogui_app_t *app;

};
typedef struct cogui_topwin cogui_topwin_t;

cogui_topwin_t *GetTopWin(S32 x, S32 y);
cogui_topwin_t *GetTopWinFocus(void);

#endif /* _COGUI_TOPWIN_H */

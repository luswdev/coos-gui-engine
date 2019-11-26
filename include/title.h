/**
 ********************************************************************************
 * @file       title.h
 * @version    V0.0.1
 * @date       2019.10.7
 * @brief      Title widget header file.
 *******************************************************************************
 */ 

#ifndef _COGUI_TITLE_H
#define _COGUI_TITLE_H

/* button type */
#define COGUI_WINTITLE_BTN_CLOSE      0x01
#define COGUI_WINTITLE_BTN_MINI       0x02
#define COGUI_WINTITLE_BTN_BORDER     0x04

#define COGUI_WINTITLE_BORDER_SIZE          2

#define COGUI_WINTITLE_HEIGHT               40          /**< Title height                   */
#define COGUI_WINTITLE_BTN_HEIGHT           34          /**< Title button height            */
#define COGUI_WINTITLE_BTN_INNER_HEIGHT     30          /**< Title button drawing height    */

struct cogui_window;

void cogui_title_create(struct cogui_window *window);
void cogui_title_delete(struct cogui_window *window);

#endif /* _COGUI_TITLE_H */

/**
 ********************************************************************************
 * @file       title.h
 * @version    V0.7.4
 * @date       2020.04.18
 * @brief      Title widget header file.
 *******************************************************************************
 */ 

#ifndef __GUI_TITLE_H__
#define __GUI_TITLE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* button type */
#define GUI_WINTITLE_BTN_CLOSE      0x01
#define GUI_WINTITLE_BTN_HIDE       0x02
#define GUI_WINTITLE_BTN_BORDER     0x04

#define GUI_WINTITLE_BORDER_SIZE          2

#define GUI_WINTITLE_HEIGHT               40          /**< Title height                   */
#define GUI_WINTITLE_BTN_HEIGHT           28          /**< Title button height            */
#define GUI_WINTITLE_BTN_INNER_HEIGHT     22          /**< Title button drawing height    */

struct window;

void gui_title_create(struct window *win);
void gui_title_delete(struct window *win);

#ifdef __cplusplus
}
#endif

#endif /* __GUI_TITLE_H__ */

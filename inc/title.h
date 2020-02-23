/**
 ********************************************************************************
 * @file       title.h
 * @version    V0.7.1
 * @date       2020.02.23
 * @brief      Title widget header file.
 *******************************************************************************
 */ 

#ifndef __COGUI_TITLE_H__
#define __COGUI_TITLE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* button type */
#define COGUI_WINTITLE_BTN_CLOSE      0x01
#define COGUI_WINTITLE_BTN_MINI       0x02
#define COGUI_WINTITLE_BTN_BORDER     0x04

#define COGUI_WINTITLE_BORDER_SIZE          2

#define COGUI_WINTITLE_HEIGHT               40          /**< Title height                   */
#define COGUI_WINTITLE_BTN_HEIGHT           28          /**< Title button height            */
#define COGUI_WINTITLE_BTN_INNER_HEIGHT     22          /**< Title button drawing height    */

struct cogui_window;

void cogui_title_create(struct cogui_window *win);
void cogui_title_delete(struct cogui_window *win);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_TITLE_H__ */

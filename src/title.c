/**
 ********************************************************************************
 * @file       title.c
 * @version    V0.0.1
 * @date       2019.10.7
 * @brief      Title widget management function.
 *******************************************************************************
 */ 

#include <cogui.h>

const cogui_color_t default_title_background = COGUI_LIGHT_GRAY;
const cogui_color_t default_title_foreground = COGUI_BLACK;

void cogui_title_create(cogui_window_t *win)
{
    cogui_widget_t *close_btn = cogui_widget_create(win);
    cogui_widget_t  *mini_btn = cogui_widget_create(win);

    win->title->gc.foreground = COGUI_BLACK;
    win->title->gc.background = COGUI_LIGHT_GRAY;
    close_btn->gc.foreground = COGUI_BLACK;
    close_btn->gc.background = COGUI_LIGHT_GRAY;
    mini_btn->gc.foreground = COGUI_BLACK;
    mini_btn->gc.background = COGUI_LIGHT_GRAY;

    COGUI_WIDGET_ENABLE(win->title);
    COGUI_WIDGET_ENABLE(close_btn);
    COGUI_WIDGET_ENABLE(mini_btn);

    win->title->flag |= COGUI_WIDGET_FLAG_TITLE | COGUI_WIDGET_FLAG_RECT | COGUI_WIDGET_FLAG_FILLED;
    close_btn->flag |= COGUI_WIDGET_FLAG_TITLE | COGUI_WIDGET_FLAG_BUTTON_CLOSE;
    mini_btn->flag |= COGUI_WIDGET_FLAG_TITLE | COGUI_WIDGET_FLAG_BUTTON_MINI;

    cogui_widget_set_rectangle(win->title, 0, 0, 240, COGUI_WINTITLE_HEIGHT);
    cogui_widget_set_rectangle(close_btn, 2, 2, 36, 36);
    cogui_widget_set_rectangle(mini_btn, 40, 2, 36, 36);

    win->title->gc.padding = COGUI_PADDING(7, 0, 100, 0);

    cogui_widget_set_text_align(win->title, COGUI_TEXT_ALIGN_LEFT|COGUI_TEXT_ALIGN_TOP);
    cogui_widget_set_font(win->title, &tm_font_16x26);
    cogui_widget_set_text(win->title, win->title_name);
}

void cogui_title_delete(cogui_window_t *win)
{
    cogui_widget_t *close_btn = win->title->next;
    cogui_widget_t  *mini_btn = win->title->next->next;
    cogui_widget_delete(close_btn);
    cogui_widget_delete(mini_btn);

    COGUI_WIDGET_DISABLE(win->title);
}

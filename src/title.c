/**
 ********************************************************************************
 * @file       title.c
 * @version    V0.1.2
 * @date       2020.01.18
 * @brief      Title widget management function.
 *******************************************************************************
 */ 

#include <cogui.h>

const cogui_color_t default_title_background  = COGUI_BLACK;
const cogui_color_t default_title_foreground  = COGUI_LIGHT_GRAY;
const cogui_color_t default_button_foreground = COGUI_DARK_GRAY;

extern cogui_font_t tm_symbol_16x16;

/**
 *******************************************************************************
 * @brief      Create a title widget set for new window.
 * @param[in]  *win    Which window this title below.
 * @param[out] None
 * @retval     None 
 *
 * @par Description
 * @details    This function is used to create a title widget set for new 
 *             window contain a minimal button, close button and title
 *             name field.
 *******************************************************************************
 */
void cogui_title_create(cogui_window_t *win)
{
    cogui_widget_t *close_btn = cogui_widget_create(win);
    cogui_widget_t  *mini_btn = cogui_widget_create(win);

    /* filled default color scheme for title */
    win->title->gc.foreground = default_title_foreground;
    win->title->gc.background = default_title_background;
    close_btn->gc.foreground  = default_button_foreground;
    mini_btn->gc.foreground   = default_button_foreground;

    /* enabled all three widgets */
    COGUI_WIDGET_ENABLE(win->title);
    COGUI_WIDGET_ENABLE(close_btn);
    COGUI_WIDGET_ENABLE(mini_btn);

    /* give this three widgets flags */
    win->title->flag |= COGUI_WIDGET_FLAG_TITLE | COGUI_WIDGET_FLAG_RECT | COGUI_WIDGET_FLAG_FILLED;
    close_btn->flag  |= COGUI_WIDGET_FLAG_TITLE;
    mini_btn->flag   |= COGUI_WIDGET_FLAG_TITLE;

    /* set three widgets sizes */
    cogui_widget_set_rectangle(win->title, 65, 0, 240, COGUI_WINTITLE_HEIGHT);
    cogui_widget_set_rectangle(close_btn, 8, 0, 20, 40);
    cogui_widget_set_rectangle(mini_btn, 32, 0, 20, 40);

    /* set title font style */
    cogui_widget_set_text_align(win->title, COGUI_TEXT_ALIGN_LEFT|COGUI_TEXT_ALIGN_MIDDLE);
    cogui_widget_set_font(win->title, &tm_font_16x26);
    cogui_widget_set_text(win->title, win->title_name);

    /* symbol "X" */
    cogui_widget_set_text_align(close_btn, COGUI_TEXT_ALIGN_CENTER|COGUI_TEXT_ALIGN_MIDDLE);
    cogui_widget_set_font(close_btn, &tm_symbol_16x16);
    cogui_widget_set_text(close_btn, "!");
    close_btn->gc.padding = COGUI_PADDING(0,2,0,0);

    /* symbol "-" */
    cogui_widget_set_text_align(mini_btn, COGUI_TEXT_ALIGN_CENTER|COGUI_TEXT_ALIGN_MIDDLE);
    cogui_widget_set_font(mini_btn, &tm_symbol_16x16);
    cogui_widget_set_text(mini_btn, "\"");
}

/**
 *******************************************************************************
 * @brief      Delete title widget set for window.
 * @param[in]  *win    Which window this title below.
 * @param[out] None
 * @retval     None 
 *******************************************************************************
 */
void cogui_title_delete(cogui_window_t *win)
{
    /* delete two button */
    cogui_widget_t *close_btn = win->title->next;
    cogui_widget_t  *mini_btn = win->title->next->next;
    cogui_widget_delete(close_btn);
    cogui_widget_delete(mini_btn);

    /* title widget will delete at window deletion */
    COGUI_WIDGET_DISABLE(win->title);
}

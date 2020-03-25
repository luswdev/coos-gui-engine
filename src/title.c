/**
 ********************************************************************************
 * @file       title.c
 * @version    V0.7.3
 * @date       2020.03.25
 * @brief      Title widget management function.
 *******************************************************************************
 */ 

#include <cogui.h>

static StatusType gui_title_button_on_focus_in(widget_t *widget, event_t *event);
static StatusType gui_title_button_on_focus_out(widget_t *widget, event_t *event);

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
void gui_title_create(window_t *win)
{
    widget_t *close_btn = gui_widget_create(win);
    widget_t  *hide_btn = gui_widget_create(win);

    /* filled default color scheme for title */
    win->title->gc.foreground = light_grey;
    win->title->gc.background = black;
    close_btn->gc.foreground  = dark_grey;
    hide_btn->gc.foreground   = dark_grey;

    /* enabled all three widgets */
    GUI_WIDGET_ENABLE(win->title);
    GUI_WIDGET_ENABLE(close_btn);
    GUI_WIDGET_ENABLE(hide_btn);

    /* give this three widgets flags */
    win->title->flag |= GUI_WIDGET_FLAG_TITLE | GUI_WIDGET_FLAG_RECT | GUI_WIDGET_FLAG_FILLED | GUI_WIDGET_FLAG_HEADER;
    close_btn->flag  |= GUI_WIDGET_FLAG_TITLE | GUI_WIDGET_FLAG_CLOSE_BTN;
    hide_btn->flag   |= GUI_WIDGET_FLAG_TITLE | GUI_WIDGET_FLAG_HIDE_BTN;

    /* set three widgets sizes */
    gui_widget_set_rectangle(win->title, 65, 0, 240, GUI_WINTITLE_HEIGHT);
    gui_widget_set_rectangle(close_btn, 8, 0, 20, 40);
    gui_widget_set_rectangle(hide_btn, 32, 0, 20, 40);

    /* set title font style */
    gui_widget_set_text_align(win->title, GUI_TEXT_ALIGN_LEFT|GUI_TEXT_ALIGN_MIDDLE);
    gui_widget_set_font(win->title, &tm_font_16x26);
    gui_widget_set_text(win->title, win->title_name);

    /* symbol "X" */
    gui_widget_set_text_align(close_btn, GUI_TEXT_ALIGN_CENTER|GUI_TEXT_ALIGN_MIDDLE);
    gui_widget_set_font(close_btn, &tm_symbol_16x16);
    gui_widget_set_text(close_btn, "!");
    close_btn->gc.padding = GUI_PADDING(0,2,0,0);

    /* symbol "-" */
    gui_widget_set_text_align(hide_btn, GUI_TEXT_ALIGN_CENTER|GUI_TEXT_ALIGN_MIDDLE);
    gui_widget_set_font(hide_btn, &tm_symbol_16x16);
    gui_widget_set_text(hide_btn, "\"");

    /* set callbacks */
    close_btn->on_focus_in = gui_title_button_on_focus_in;
    close_btn->on_focus_out = gui_title_button_on_focus_out;
    hide_btn->on_focus_in = gui_title_button_on_focus_in; 
    hide_btn->on_focus_out = gui_title_button_on_focus_out; 
}

/**
 *******************************************************************************
 * @brief      Delete title widget set for window.
 * @param[in]  *win    Which window this title below.
 * @param[out] None
 * @retval     None 
 *******************************************************************************
 */
void gui_title_delete(window_t *win)
{
    /* delete two button */
    widget_t *close_btn = win->title->next;
    widget_t  *hide_btn = win->title->next->next;
    gui_widget_delete(close_btn);
    gui_widget_delete(hide_btn);

    /* title widget will delete at window deletion */
    GUI_WIDGET_DISABLE(win->title);
}

static StatusType gui_title_button_on_focus_in(widget_t *widget, event_t *event)
{
    widget->gc.foreground = high_light;

    return GUI_E_OK;
}

static StatusType gui_title_button_on_focus_out(widget_t *widget, event_t *event)
{
    widget->gc.foreground = dark_grey;

    return GUI_E_OK;
}
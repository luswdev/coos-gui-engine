/**
 *******************************************************************************
 * @file       window.h
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      Window management function header file.
 *******************************************************************************
 */ 

#ifndef __GUI_WINDOW_H__
#define __GUI_WINDOW_H__

#ifdef __cplusplus
extern "C" {
#endif

/* window style */
#define GUI_WINDOW_STYLE_NO_TITLE            0x01  /**< no title window               */
#define GUI_WINDOW_STYLE_NO_BORDER           0x02  /**< no border window              */

#define GUI_WINDOW_MAGIC					  0x57696E00		/* win magic flag */

/* window flag */
#define GUI_WINDOW_FLAG_INIT        0x00
#define GUI_WINDOW_FLAG_SHOW        0x01

#define GUI_WINDOW(w)     ((struct window *)(w))

/* enable (show) */
#define GUI_WINDOW_ENABLE(w)          GUI_WINDOW((w))->flag |= GUI_WINDOW_FLAG_SHOW
#define GUI_WINDOW_DISABLE(w)         GUI_WINDOW((w))->flag &= ~GUI_WINDOW_FLAG_SHOW
#define GUI_WINDOW_IS_ENABLE(w)       (GUI_WINDOW((w))->flag & GUI_WINDOW_FLAG_SHOW)

#define gui_window_create_with_title()        gui_window_create(~GUI_WINDOW_STYLE_NO_TITLE)
#define gui_window_create_without_title()     gui_window_create(GUI_WINDOW_STYLE_NO_TITLE)

/**
 * @struct   cogui_window
 * @brief    Window struct
 * @details  This struct is for window.
 */
struct window
{
    /* window magic word field */
    uint32_t         magic;                          /**< should be 0x57696E00                   */

    /* meta data field */
    widget_t *       widget_list;                    /**< widget list under this window          */
    int16_t          id;                             /**< window id -1 for main window          */
    uint16_t         style;                          /**< window style                           */
    int32_t          flag;                           /**< window flag                            */
    int64_t          update;                         /**< window update count                    */
    int32_t          widget_cnt;                     /**< how many widgets this window have      */
    widget_t *       focus_widget;                   /**< current focus widget                   */
    app_t *          app;                            /**< window belongs to which application    */
    widget_t *       title;                          /**< title bar widget set                   */
    char *           title_name;                     /**< title belongs to application           */

    /* event pointer feild */
    widget_t *       last_mouse_event_widget;        /**< last mouse event widget                */

    /* user private data field */
    void *           user_data;                      /**< user private data                      */

    /* event handler field */
    StatusType (*on_activate)(widget_t *widget, struct event *event);       /**<*/
    StatusType (*on_deactivate)(widget_t *widget, struct event *event);     /**<*/
    StatusType (*on_key)(widget_t *widget, struct event *event);            /**<*/
    uint64_t   (*_do_show)(struct window *win);                             /**<*/
    StatusType (*handler)(struct window *widget ,struct event *event);      /**<*/
};
typedef struct window window_t;

/**
 * @struct   main_app_table
 * @brief    main window struct
 * @details  This struct is for manage installed app of main window.
 */
struct main_app_table {
    widget_t *      app_icon;
    widget_t *      app_title_box;
    char *          title;
};

window_t *gui_window_create(uint16_t style);
void gui_window_delete(window_t *win);

window_t *gui_main_window_create(void);

widget_t *gui_window_get_mouse_event_widget(window_t *top, uint16_t cx, uint16_t cy);
StatusType gui_window_update(window_t *top, widget_t *widget);
StatusType gui_window_refresh(window_t *top);

window_t *gui_get_main_window(void);
window_t *gui_get_current_window(void);

int16_t gui_main_page_app_install(char *title);
void gui_main_page_app_uninstall(int16_t);

StatusType gui_window_close(window_t *win);

StatusType gui_window_show(window_t *win);
StatusType gui_window_onshow(window_t *win);

StatusType gui_window_hide(window_t *win);
StatusType gui_window_onhide(window_t *win);

StatusType gui_window_active(window_t *win);
StatusType gui_window_is_activated(window_t *win);

void gui_window_set_onactivate(window_t *win, event_handler_ptr handler);
void gui_window_set_ondeactive(window_t *win, event_handler_ptr handler);
void gui_window_set_onkey(window_t *win, event_handler_ptr handler);

void gui_window_set_title(window_t *win, const uint8_t *title);
uint8_t *gui_window_get_title(window_t *win);

void gui_assert_failed_page(const char* ex, uint16_t line, const char* func);

#ifdef __cplusplus
}
#endif

#endif /* __GUI_WINDOW_H__ */

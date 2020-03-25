/**
 *******************************************************************************
 * @file       widget.h
 * @version    V0.7.3
 * @date       2020.03.25
 * @brief      Some widget function for GUI engine's widget.	
 *******************************************************************************
 */ 

#ifndef __GUI_WIDGET_H__
#define __GUI_WIDGET_H__

#ifdef __cplusplus
extern "C" {
#endif

struct dc;
struct gc;
struct event;
struct widget;
struct window;

/* widget flag define field */
#define GUI_WIDGET_FLAG_INIT          0x000
#define GUI_WIDGET_FLAG_SHOWN         0x001
#define GUI_WIDGET_FLAG_FOCUS         0x002

/* widget type define field */
#define GUI_WIDGET_TYPE_MASK          0x0F0       /**< B(1111 0000)               */
#define GUI_WIDGET_TYPE_INIT          0x010       /**< Inital type                */
#define GUI_WIDGET_TYPE_WIDGET        0x020       /**< It is a widget             */
#define GUI_WIDGET_BORDER             0x040       /**< Border enable              */

/* widget node flag define field */
#define GUI_WIDGET_FLAG_MASK          0x0F00       /**< B(1111 0000 0000)          */
#define GUI_WIDGET_FLAG_FILLED        0x0100       /**< Node is needed to filled   */
#define GUI_WIDGET_FLAG_RECT          0x0200       /**< Node is rectangle          */
#define GUI_WIDGET_FLAG_TITLE         0x0400       /**< Node is button             */
#define GUI_WIDGET_FLAG_HAS_TEXT      0x0800       /**< node need to print text    */
#define GUI_WIDGET_FLAG_HEADER        0x4000       /**< it is header node          */

#define GUI_WIDGET_FLAG_CLOSE_BTN     0x10000       /**< it is close btn           */
#define GUI_WIDGET_FLAG_HIDE_BTN      0x20000       /**< it is hide bnt            */

/* inline function */
#define GUI_WIDGET(w) ((struct widget *)(w))

/* enable (shown) */
#define GUI_WIDGET_ENABLE(w)          GUI_WIDGET((w))->flag |= GUI_WIDGET_FLAG_SHOWN
#define GUI_WIDGET_DISABLE(w)         GUI_WIDGET((w))->flag &= ~GUI_WIDGET_FLAG_SHOWN
#define COGUI_WIDGET_IS_ENABLE(w)       (GUI_WIDGET((w))->flag & GUI_WIDGET_FLAG_SHOWN)

/* focus */
#define GUI_WIDGET_FOCUS(w)           GUI_WIDGET((w))->flag |= GUI_WIDGET_FLAG_FOCUS
#define GUI_WIDGET_UNFOCUS(w)         GUI_WIDGET((w))->flag &= ~GUI_WIDGET_FLAG_FOCUS
#define GUI_WIDGET_IS_FOCUS(w)        (GUI_WIDGET((w))->flag & GUI_WIDGET_FLAG_FOCUS)

typedef StatusType (*event_handler_ptr)(struct widget *widget, struct event *event);

/**
 * @struct   cogui_widget
 * @brief    Widget struct
 * @details  This struct is for widget.
 */
struct widget
{
    /* node data field */
    struct widget *   next;                       /**< the next widget                        */
    struct window *   top;                        /**< the window that contains this widget   */

    /* meta data field */
    uint64_t          flag;                       /**< widget flag                            */
    int32_t           id;                         /**< widget id (belong to top window)       */
    uint16_t          dc_type;                    /**< hardware device context                */
    struct rect       extent;                     /**< the widget extent                      */
    struct rect       inner_extent;               /**< the widget extent for drawing          */
    int16_t           min_width, min_height;      /**< minimal width and height of widget     */
   
    /* graphic driver field */
    struct dc *       dc_engine;                  /**< DC engine                              */
    struct gc         gc;                         /**< the graphic context of widget          */

    /* user private data field */
    char *            text;                       /**< text need to print                     */
    void *            user_data;                  /**< user private data                      */

    /* event handler field */
    StatusType (*on_focus_in)(struct widget *widget, struct event *event);      /**< on focus in call back function  */
    StatusType (*on_focus_out)(struct widget *widget, struct event *event);     /**< on focus out call back function */
    StatusType (*handler)(struct widget *widget ,struct event *event);          /**< event handler function          */
};
typedef struct widget widget_t;

/* new\kill a widget */
widget_t *gui_widget_create(struct window *top);
void gui_widget_delete(widget_t *widget);

/* for widget list */
widget_t *gui_widget_list_init(struct window *top);

/* screen list operation function */
void gui_widget_list_insert(widget_t *node);
widget_t *gui_widget_list_pop(uint32_t id, struct window *top);

/* screen node operation function */
widget_t *gui_get_widget_node(uint32_t id, struct window *top);

/* do focus */
void gui_widget_focus(widget_t *widget);
void gui_widget_unfocus(widget_t *widget);

/* set widget attributes */
void gui_widget_set_focus(widget_t *widget, event_handler_ptr handler);
void gui_widget_set_unfocus(widget_t *widget, event_handler_ptr handler);

void gui_widget_set_minsize(widget_t *widget, int32_t width, int32_t height);
void gui_widget_set_minwidth(widget_t *widget, int32_t width);
void gui_widget_set_minheight(widget_t *widget, int32_t height);

void gui_widget_set_rectangle(widget_t *widget, int32_t x, int32_t y, int32_t width, int32_t height);
void gui_widget_enable_border(widget_t *widget);

/* get widget size */
void gui_widget_get_rect(widget_t *widget, rect_t *rect);
void gui_widget_get_extent(widget_t *widget, rect_t *rect);

/* set widget text */
void gui_widget_set_font(widget_t* widget, font_t *font);
void gui_widget_set_text_align(widget_t *widget, uint16_t style);
void gui_widget_set_text(widget_t *widget, const char *text);
void gui_widget_append_text(widget_t *widget, const char *text);
void gui_widget_clear_text(widget_t *widget);

/* show/hide widget */
StatusType gui_widget_show(widget_t *widget);
StatusType gui_widget_onshow(widget_t *widget, struct event *event);
StatusType gui_widget_hide(widget_t *widget);
StatusType gui_widget_onhide(widget_t *widget, struct event *event);

/* get the physical position of a logic point on widget */
void gui_widget_point_l2p(widget_t *widget, point_t *point);
/* get the physical position of a logic rect on widget */
void gui_widget_rect_l2p(widget_t *widget, rect_t *rect);

/* get the logic position of a physical point on widget */
void gui_widget_point_p2l(widget_t *widget, point_t *point);
/* get the logic position of a physical rect on widget */
void gui_widget_rect_p2l(widget_t *widget, rect_t *rect);

/* move widget and its children to a logic point */
void gui_widget_move_to_logic(widget_t *widget, int32_t dx, int32_t dy);
void gui_widget_move_to_phy(widget_t *widget, int32_t dx, int32_t dy);

#ifdef __cplusplus
}
#endif

#endif /* __GUI_WIDGET_H__ */

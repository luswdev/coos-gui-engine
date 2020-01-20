/**
 *******************************************************************************
 * @file       widget.h
 * @version    V0.6.1
 * @date       2020.01.20
 * @brief      Some widget function for GUI engine's widget.	
 *******************************************************************************
 */ 

#ifndef __COGUI_WIDGET_H__
#define __COGUI_WIDGET_H__

#ifdef __cplusplus
extern "C" {
#endif

struct cogui_dc;
struct cogui_gc;
struct cogui_event;
struct cogui_widget;
struct cogui_screen;
struct cogui_window;

/* widget flag define field */
#define COGUI_WIDGET_FLAG_INIT          0x000
#define COGUI_WIDGET_FLAG_SHOWN         0x001
#define COGUI_WIDGET_FLAG_FOCUS         0x002

/* widget type define field */
#define COGUI_WIDGET_TYPE_MASK          0x0F0       /**< B(1111 0000)               */
#define COGUI_WIDGET_TYPE_INIT          0x010       /**< Inital type                */
#define COGUI_WIDGET_TYPE_WIDGET        0x020       /**< It is a widget             */
#define COGUI_WIDGET_BORDER             0x040       /**< Border enable              */

/* widget node flag define field */
#define COGUI_WIDGET_FLAG_MASK          0x0F00       /**< B(1111 0000 0000)          */
#define COGUI_WIDGET_FLAG_FILLED        0x0100       /**< Node is needed to filled   */
#define COGUI_WIDGET_FLAG_RECT          0x0200       /**< Node is rectangle          */
#define COGUI_WIDGET_FLAG_TITLE         0x0400       /**< Node is button             */
#define COGUI_WIDGET_FLAG_HAS_TEXT      0x0800       /**< node need to print text    */
#define COGUI_WIDGET_FLAG_HEADER        0x4000       /**< it is header node          */

/* inline function */
#define COGUI_WIDGET(w) ((struct cogui_widget *)(w))

/* enable (shown) */
#define COGUI_WIDGET_ENABLE(w)          COGUI_WIDGET((w))->flag |= COGUI_WIDGET_FLAG_SHOWN
#define COGUI_WIDGET_DISABLE(w)         COGUI_WIDGET((w))->flag &= ~COGUI_WIDGET_FLAG_SHOWN
#define COGUI_WIDGET_IS_ENABLE(w)       (COGUI_WIDGET((w))->flag & COGUI_WIDGET_FLAG_SHOWN)

/* focus */
#define COGUI_WIDGET_FOCUS(w)           COGUI_WIDGET((w))->flag |= COGUI_WIDGET_FLAG_FOCUS
#define COGUI_WIDGET_UNFOCUS(w)         COGUI_WIDGET((w))->flag &= ~COGUI_WIDGET_FLAG_FOCUS
#define COGUI_WIDGET_IS_FOCUS(w)        (COGUI_WIDGET((w))->flag & COGUI_WIDGET_FLAG_FOCUS)

typedef StatusType (*event_handler_ptr)(struct cogui_widget *widget, struct cogui_event *event);

/**
 * @struct   cogui_widget
 * @brief    Widget struct
 * @details  This struct is for widget.
 */
struct cogui_widget
{
    /* node data field */
    struct cogui_widget *   next;                       /**< the next widget                        */
    struct cogui_window *   top;                        /**< the window that contains this widget   */

    /* meta data field */
    co_int32_t              flag;                       /**< widget flag                            */
    co_int32_t              id;                         /**< widget id (belong to top window)       */
    co_uint16_t             dc_type;                    /**< hardware device context                */
    struct cogui_rect       extent;                     /**< the widget extent                      */
    struct cogui_rect       inner_extent;               /**< the widget extent for drawing          */
    co_int16_t              min_width, min_height;      /**< minimal width and height of widget     */
   
    /* graphic driver field */
    struct cogui_dc *       dc_engine;                  /**< DC engine                              */
    struct cogui_gc         gc;                         /**< the graphic context of widget          */

    /* user private data field */
    char *                  text;                       /**< text need to print                     */
    void *                  user_data;                  /**< user private data                      */

    /* event handler field */
    StatusType (*on_focus_in)(struct cogui_widget *widget, struct cogui_event *event);      /**< on focus in call back function  */
    StatusType (*on_focus_out)(struct cogui_widget *widget, struct cogui_event *event);     /**< on focus out call back function */
    StatusType (*handler)(struct cogui_widget *widget ,struct cogui_event *event);          /**< event handler function          */
};
typedef struct cogui_widget cogui_widget_t;

/* new\kill a widget */
cogui_widget_t *cogui_widget_create(struct cogui_window *top);
void cogui_widget_delete(cogui_widget_t *widget);

/* for widget list */
cogui_widget_t *cogui_widget_list_init(struct cogui_window *top);
StatusType cogui_screen_refresh(struct cogui_window *top);

/* screen list operation function */
void cogui_widget_list_insert(cogui_widget_t *node);
void cogui_widget_list_remove(co_uint32_t id, struct cogui_window *top);
cogui_widget_t *cogui_widget_list_pop(co_uint32_t id, struct cogui_window *top);

/* screen node operation function */
cogui_widget_t *cogui_get_widget_node(co_uint32_t id, struct cogui_window *top);

/* do focus */
void cogui_widget_focus(cogui_widget_t *widget);
void cogui_widget_unfocus(cogui_widget_t *widget);

/* set widget attributes */
void cogui_widget_set_focus(cogui_widget_t *widget, event_handler_ptr handler);
void cogui_widget_set_unfocus(cogui_widget_t *widget, event_handler_ptr handler);

void cogui_widget_set_minsize(cogui_widget_t *widget, S32 width, S32 height);
void cogui_widget_set_minwidth(cogui_widget_t *widget, S32 width);
void cogui_widget_set_minheight(cogui_widget_t *widget, S32 height);

void cogui_widget_set_rectangle(cogui_widget_t *widget, S32 x, S32 y, S32 width, S32 height);
void cogui_widget_enable_border(cogui_widget_t *widget);

/* get widget size */
void cogui_widget_get_rect(cogui_widget_t *widget, cogui_rect_t *rect);
void cogui_widget_get_extent(cogui_widget_t *widget, cogui_rect_t *rect);

/* set widget text */
void cogui_widget_set_font(cogui_widget_t* widget, cogui_font_t *font);
void cogui_widget_set_text_align(cogui_widget_t *widget, co_uint16_t style);
void cogui_widget_set_text(cogui_widget_t *widget, const char *text);
void cogui_widget_append_text(cogui_widget_t *widget, const char *text);
void cogui_widget_clear_text(cogui_widget_t *widget);

/* show/hide widget */
StatusType cogui_widget_show(cogui_widget_t *widget);
StatusType cogui_widget_onshow(cogui_widget_t *widget, struct cogui_event *event);
StatusType cogui_widget_hide(cogui_widget_t *widget);
StatusType cogui_widget_onhide(cogui_widget_t *widget, struct cogui_event *event);

/* get the physical position of a logic point on widget */
void cogui_widget_point_l2p(cogui_widget_t *widget, cogui_point_t *point);
/* get the physical position of a logic rect on widget */
void cogui_widget_rect_l2p(cogui_widget_t *widget, cogui_rect_t *rect);

/* get the logic position of a physical point on widget */
void cogui_widget_point_p2l(cogui_widget_t *widget, cogui_point_t *point);
/* get the logic position of a physical rect on widget */
void cogui_widget_rect_p2l(cogui_widget_t *widget, cogui_rect_t *rect);

/* move widget and its children to a logic point */
void cogui_widget_move_to_logic(cogui_widget_t *widget, S32 dx, S32 dy);

/* debug */
void cogui_widget_list_print(struct cogui_window *top);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_WIDGET_H__ */

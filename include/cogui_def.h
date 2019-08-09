/**
 *******************************************************************************
 * @file       cogui_def.h
 * @version    V0.0.2   
 * @date       2019.8.9
 * @brief      This is a definition file for gui engine.
 *******************************************************************************
 */ 

#ifndef _COGUI_DEF_H
#define _COGUI_DEF_H

#include <coocox.h>

struct cogui_widget;
struct cogui_window;
struct cogui_container;
struct cogui_event;
struct cogui_dc;

/**
 *******************************************************************************
 * typedef
 *******************************************************************************
 */

typedef U64 cogui_color_t;
typedef StatusType  (*event_handler_ptr)(struct cogui_widget *widget, struct cogui_event *event);


/**
 *******************************************************************************
 * Structure
 *******************************************************************************
 */

/*---------------------------- basic def -------------------------------------*/

/**
 * double linked list
 */
struct cogui_list_node
{
    struct list_node *prev;
    struct list_node *next;
};
typedef struct cogui_list_node cogui_list_t;

/**
 * single linked list
 */
struct cogui_slist_node
{
    struct cogui_slist_node *next;
};
typedef struct cogui_slist_node cogui_slist_t;

/*---------------------------- region ----------------------------------------*/

/**
 * rectangle
 */
struct cogui_rect_t
{
    S16 x1, x2, y1, y2;
};
typedef struct cogui_rect_t cogui_rect_t;

/**
 * region
 */
struct cogui_region_data
{
    U32 size;
    U32 num_rects;
};
typedef struct cogui_region_data cogui_region_data_t;

struct cogui_region
{
    cogui_rect_t extent;
    cogui_region_data_t *data;

};
typedef struct cogui_region cogui_region_t;

/**
 * 2D point
 */
struct cogui_point
{
    S16 x, y;
};
typedef struct cogui_point cogui_point_t;

/**
 * Border style
 */
enum cogui_border_style
{
    COGUI_BORDER_NONE = 0,
    COGUI_BORDER_SIMPLE,
    COGUI_BORDER_RAISE,
    COGUI_BORDER_SUNKEN,
    COGUI_BORDER_BOX,
    COGUI_BORDER_STATIC,
    COGUI_BORDER_EXTRA,
    COGUI_BORDER_UP,
    COGUI_BORDER_DOWN
};
#define COGUI_BORDER_DEFAULT_WIDTH  2
#define COGUI_WIDGET_DEFAULT_MARGIN 3

/*---------------------------- driver ----------------------------------------*/

/* graphic driver operations */
struct graphic_driver_ops
{
    /* set and get pixel in (x, y) */
    void (*set_pixel)(cogui_color_t *c, S32 x, S32 y);
    void (*get_pixel)(cogui_color_t *c, S32 x, S32 y);

    void (*draw_hline)(cogui_color_t *c, S32 x1, S32 x2, S32 y);
    void (*draw_vline)(cogui_color_t *c, S32 x , S32 y1, S32 y2);

    /* draw raw hline */
    void (*draw_raw_hline)(U8 *pixels, S32 x1, S32 x2, S32 y);
};

/* graphic extension operations */
struct graphic_ext_ops
{
    /* some 2D operations */
    void (*draw_line)(cogui_color_t *c, S32 x1, S32 y1, S32 x2, S32 y2);

    void (*draw_rect)(cogui_color_t *c, S32 x1, S32 y1, S32 x2, S32 y2);
    void (*fill_rect)(cogui_color_t *c, S32 x1, S32 y1, S32 x2, S32 y2);

    void (*draw_circle)(cogui_color_t *c, S32 x, S32 y, S32 r);
    void (*fill_circle)(cogui_color_t *c, S32 x, S32 y, S32 r);

    void (*draw_ellipse)(cogui_color_t *c, S32 x, S32 y, S32 rx, S32 ry);
    void (*fill_ellipse)(cogui_color_t *c, S32 x, S32 y, S32 rx, S32 ry);
};

struct cogui_graphic_driver
{
    /* pixel format and byte per pixel */
    U8 pixel_format;
    U8 bits_per_pixel;
    U16 pitch;

    /* screen width and height */
    U16 width;
    U16 height;

    /* framebuffer address and ops */
    U8 *framebuffer;

    struct graphic_driver_ops *ops;
    struct graphic_ext_ops *ext_ops;
};
typedef struct cogui_graphic_driver cogui_graphic_driver_t;

/*---------------------------- dc --------------------------------------------*/

/**
 *  Graphic context
 */
struct cogui_gc
{
    /* foreground and background color */
    cogui_color_t foreground, background;

    /* text style */
    U16 textstyle;
    /* text align */
    U16 textalign;

    /* font 
    struct rtgui_font *font; */
};

enum cogui_dc_type
{
    COGUI_DC_HW,
    COGUI_DC_CLIENT,
    COGUI_DC_BUFFER,
};

struct cogui_dc_engine
{
    /* interface */
    void (*draw_point)(struct cogui_dc *dc, S32 x, S32 y);
    void (*draw_color_point)(struct cogui_dc *dc, S32 x, S32 y, cogui_color_t color);
    void (*draw_vline)(struct cogui_dc *dc, S32 x, S32 y1, S32 y2);
    void (*draw_hline)(struct cogui_dc *dc, S32 x1, S32 x2, S32 y);
    void (*fill_rect)(struct cogui_dc *dc, cogui_rect_t *rect);

    StatusType (*fini)(struct cogui_dc * dc);
};

struct cogui_dc
{
    /* type of device context */
    enum cogui_dc_type type;

    /* dc engine */
    struct cogui_dc_engine *engine;
};
typedef struct cogui_dc cogui_dc_t;

struct cogui_dc_hw
{
    cogui_dc_t parent;
    struct cogui_widget *owner;
    cogui_graphic_driver_t *hw_driver;
};

struct cogui_dc_buffer
{
    cogui_dc_t parent;

    /* graphic context */
    struct cogui_gc gc;

    /* pixel format */
    U8 pixel_format;
    U8 blend_mode;		/* RTGUI_BLENDMODE: None/Blend/Add/Mod */

    /* width and height */
    U16 width, height;
    /* pitch */
    U16 pitch;

	/* pixel alpha */
    U8 pixel_alpha;
    /* pixel data */
    U8 *pixel;
};

/*---------------------------- application -----------------------------------*/
enum cogui_app_flag
{
    COGUI_APP_FLAG_EXITED  = 0x04,
    COGUI_APP_FLAG_SHOWN   = 0x08,
    COGUI_APP_FLAG_KEEP    = 0x80,
};

struct cogui_app
{
    U8      id;
    char   *name;

    enum cogui_app_flag flag;

    U16     ref_cnt;
    U16     exit_code;

    /* Task id */
    OS_TID tid;
    /* Message queue */
    OS_EventID   mq;

    U32     win_cnt;
    /* window activate count */
    U32     win_acti_cnt;

    /* the event handler */
    StatusType (*handler)(struct cogui_event *event);

    void    *user_data;
};
typedef struct cogui_app cogui_app_t;

/*---------------------------- widget ----------------------------------------*/
struct cogui_widget
{
    /* the widget that contains this widget */
    struct cogui_widget *parent;
    /* the window that contains this widget */
    struct cogui_window *top_level;
    /* the widget children and sibling */
    cogui_list_t sibling;

    S32 flag;
    
    /* hardware device context */
    U64 dc_type;
    const cogui_dc_t dc_engine;

    /* the graphic context of widget */
    struct cogui_gc gc;

    /* the widget extent */
    cogui_rect_t extent;
    /* the visiable extent */
    cogui_rect_t extent_visiable;
    /* the rect clip information */
    cogui_region_t clip;

    /* minimal width and height of widget */
    S16 min_width, min_height;
    /* widget align */
    S32 align;
    U16 border;
    U16 border_style;

    /* call back */
    StatusType  (*on_focus_in)(struct cogui_widget *widget, struct cogui_event *event);
    StatusType (*on_focus_out)(struct cogui_widget *widget, struct cogui_event *event);

    /* the event handler */
    StatusType (*handler)(struct cogui_widget *widget ,struct cogui_event *event);

    /* user private data */
    U32 user_data;
};
typedef struct cogui_widget cogui_widget_t;

/*---------------------------- window ----------------------------------------*/
enum cogui_win_flag
{
    COGUI_WIN_FLAG_INIT        = 0x00,  /* init state              */
    COGUI_WIN_FLAG_MODAL       = 0x01,  /* modal mode window       */
    COGUI_WIN_FLAG_CLOSED      = 0x02,  /* window is closed        */
    COGUI_WIN_FLAG_ACTIVATE    = 0x04,  /* window is activated     */
    COGUI_WIN_FLAG_UNDER_MODAL = 0x08,  /* window is under modal
                                           show(modaled by other)  */
    COGUI_WIN_FLAG_CONNECTED   = 0x10,  /* connected to server */
    /* window is event_key dispatcher(dispatch it to the focused widget in
     * current window) _and_ a key handler(it should be able to handle keys
     * such as ESC). Both of dispatching and handling are in the same
     * function(rtgui_win_event_handler). So we have to distinguish between the
     * two modes.
     *
     * If this flag is set, we are in key-handling mode.
     */
    COGUI_WIN_FLAG_HANDLE_KEY  = 0x20,

    COGUI_WIN_FLAG_CB_PRESSED  = 0x40,
};

struct cogui_window
{
    struct GuiContainer *parent;

    /* update count */
    S64 update;

    /* drawing count */
    S64 drawing;
    cogui_rect_t drawing_rect;

    /* parent window. Co_NULL if the window is a top level window */
    struct cogui_window *parent_window;

    cogui_region_t outer_clip;
    cogui_rect_t outer_extent;

    cogui_widget_t *focus_widget;

    /* which app I belong */
    cogui_app_t *app;

    /* window style */
    U16 style;

    /* window state flag */
    enum cogui_win_flag flag;

    /* last mouse event handled widget */
    cogui_widget_t *last_mouse_event_widget;

    /* window title */
    U8 *title;
    cogui_widget_t *_title_wgt;

    /* call back */
    StatusType (*on_activate)(cogui_widget_t * widget, struct cogui_event *event);
    StatusType (*on_deactivate)(cogui_widget_t * widget, struct cogui_event *event);
    StatusType (*on_close)(cogui_widget_t * widget, struct cogui_event *event);

    StatusType (*on_key)(cogui_widget_t * widget, struct cogui_event *event);

    /* reserved user data */
    void *user_data;

    /* Private data */
    S64 (*_do_show)(struct cogui_window *win);

    /* app ref_count */
    U16 app_ref_cnt;

    /* win magic flag, magic value is 0xA5A55A5A */
    U32	magic;
};
typedef struct cogui_window cogui_window_t;

/**
 * Top window
 */
struct cogui_topwin
{
    /* the window id */
    cogui_window_t *wid;

    /* which app belong */
    cogui_app_t *app;

};
typedef struct cogui_topwin cogui_topwin_t;

/*---------------------------- container -------------------------------------*/
struct cogui_box
{
    U16 orient;
    U16 borders_size;

    struct cogui_container *container;
};
typedef struct cogui_box cogui_box_t;

struct cogui_container
{
    cogui_widget_t *parent;

    StatusType (*handler)(struct cogui_event *event);

    /* layout box */
    cogui_box_t *layout_box;

    cogui_list_t children;

};
typedef struct cogui_container cogui_container_t;

#endif /* _COGUI_DEF_H */

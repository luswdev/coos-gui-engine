/**
 *******************************************************************************
 * @file       GuiDef.h
 * @version    V0.0.1   
 * @date       2019.6.5
 * @brief      This is a definition file for gui engine.
 *******************************************************************************
 */ 

#ifndef _GUI_DEF_H
#define _GUI_DEF_H

#include <coocox.h>

struct cogui_widget;
struct window;
struct GuiContainer;
struct GuiEvent;
struct cogui_dc;

/**
 *******************************************************************************
 * typedef
 *******************************************************************************
 */

typedef U64 cogui_color_t;
typedef StatusType  (*EventHandlerPtr)(struct cogui_widget *widget, struct GuiEvent *event);


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
typedef struct cogui_list_node coogui_list_node_t;

/**
 * single linked list
 */
struct cogui_slist_node
{
    struct cogui_slist_node *next;
};
typedef struct cogui_slist_node cogui_slist_node_t;

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
    U8 pixelFormat;
    U8 blendMode;		/* RTGUI_BLENDMODE: None/Blend/Add/Mod */

    /* width and height */
    U16 width, height;
    /* pitch */
    U16 pitch;

	/* pixel alpha */
    U8 pixelAlpha;
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

typedef struct cogui_app
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
    StatusType (*handler)(struct GuiEvent *event);

    void    *user_tata;
};
typedef struct cogui_app cogui_app_t;

/*---------------------------- widget ----------------------------------------*/
typedef struct cogui_widget
{
    /* the widget that contains this widget */
    struct cogui_widget *parent;
    /* the window that contains this widget */
    struct window *topLevel;
    /* the widget children and sibling */
    CoList sibling;

    S32 flag;
    
    /* hardware device context */
    U64 dcType;
    const cogui_dc_t dc_engine;

    /* the graphic context of widget */
    cogui_graphic_driver_t *gc;

    /* the widget extent */
    cogui_rect_t extent;
    /* the visiable extent */
    cogui_rect_t extentVisiable;
    /* the rect clip information */
    cogui_region_t clip;

    /* minimal width and height of widget */
    S16 minWidth, minHeight;
    /* widget align */
    S32 align;
    U16 border;
    U16 borderStyle;

    /* call back */
    StatusType  (*onFocusIn)(struct cogui_widget *widget, struct GuiEvent *event);
    StatusType (*onFocusOut)(struct cogui_widget *widget, struct GuiEvent *event);

    /* the event handler */
    StatusType (*handler)(struct cogui_widget *widget ,struct GuiEvent *event);

    /* user private data */
    U32 userData;

}cogui_widget_t;

/*---------------------------- window ----------------------------------------*/
enum guiWinFlag
{
    GUI_WIN_FLAG_INIT        = 0x00,  /* init state              */
    GUI_WIN_FLAG_MODAL       = 0x01,  /* modal mode window       */
    GUI_WIN_FLAG_CLOSED      = 0x02,  /* window is closed        */
    GUI_WIN_FLAG_ACTIVATE    = 0x04,  /* window is activated     */
    GUI_WIN_FLAG_UNDER_MODAL = 0x08,  /* window is under modal
                                           show(modaled by other)  */
    GUI_WIN_FLAG_CONNECTED   = 0x10,  /* connected to server */
    /* window is event_key dispatcher(dispatch it to the focused widget in
     * current window) _and_ a key handler(it should be able to handle keys
     * such as ESC). Both of dispatching and handling are in the same
     * function(rtgui_win_event_handler). So we have to distinguish between the
     * two modes.
     *
     * If this flag is set, we are in key-handling mode.
     */
    GUI_WIN_FLAG_HANDLE_KEY  = 0x20,

    GUI_WIN_FLAG_CB_PRESSED  = 0x40,
};

typedef struct window
{
    struct GuiContainer *parent;

    /* update count */
    S64 update;

    /* drawing count */
    S64 drawing;
    cogui_rect_t drawingRect;

    /* parent window. Co_NULL if the window is a top level window */
    struct window *parentWindow;

    cogui_region_t outerClip;
    cogui_rect_t outerExtent;

    cogui_widget_t *focusWidget;

    /* which app I belong */
    cogui_app_t *app;

    /* window style */
    U16 style;

    /* window state flag */
    enum guiWinFlag flag;

    /* last mouse event handled widget */
    cogui_widget_t *lastMeventWidget;

    /* window title */
    U8 *title;
    cogui_widget_t *_titleWgt;

    /* call back */
    StatusType (*onActivate)(cogui_widget_t * widget, struct GuiEvent *event);
    StatusType (*onDeactivate)(cogui_widget_t * widget, struct GuiEvent *event);
    StatusType (*onClose)(cogui_widget_t * widget, struct GuiEvent *event);

    StatusType (*onKey)(cogui_widget_t * widget, struct GuiEvent *event);

    /* reserved user data */
    void *userData;

    /* Private data */
    S64 (*_doShow)(struct window *win);

    /* app ref_count */
    U16 appRefCnt;

    /* win magic flag, magic value is 0xA5A55A5A */
    U32	magic;

}GuiWin,*P_GuiWin;

/**
 * Top window
 */
typedef struct topwin
{
    /* the window id */
    P_GuiWin *wid;

    /* which app belong */
    cogui_app_t **app;

}TopWin,*P_TopWin;

/*---------------------------- container -------------------------------------*/
typedef struct box
{
    U16 orient;
    U16 borderSize;

    struct GuiContainer *container;
}GuiBox,*P_GuiBox;

typedef struct GuiContainer
{
    cogui_widget_t *parent;

    StatusType (*handler)(struct GuiEvent *event);

    /* layout box */
    P_GuiBox layoutBox;

    CoList children;

}GuiContainer,*P_GuiContainer;

#endif /* _GUI_DEF_H */

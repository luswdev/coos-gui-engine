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

struct GuiWidget;
struct window;
struct GuiContainer;
struct GuiEvent;
struct GuiDc;

/**
 *******************************************************************************
 * typedef
 *******************************************************************************
 */

typedef U64 GUI_COLOR;
typedef StatusType  (*EventHandlerPtr)(struct GuiWidget *widget, struct GuiEvent *event);


/**
 *******************************************************************************
 * Structure
 *******************************************************************************
 */

/*---------------------------- basic def -------------------------------------*/

/**
 * double linked list
 */
typedef struct ListNode
{
    struct ListNode *prev;
    struct ListNode *next;
}CoList,*P_CoList;

/**
 * single linked list
 */
typedef struct SListNode
{
    struct SListNode *next;
}CoSList,*P_CoSList;

/*---------------------------- region ----------------------------------------*/

/**
 * rectangle
 */
typedef struct rect
{
    S16 x1, x2, y1, y2;

}GuiRect,*P_GuiRect;

/**
 * region
 */
typedef struct regionData
{
    U32 size;
    U32 nubRects;

}GuiRegionData,*P_GuiRegionData;

typedef struct region
{
    GuiRect extent;

    P_GuiRegionData data;

}GuiRegion,*P_GuiRegion;

/**
 * 2D point
 */
typedef struct point
{
    S16 x, y;
}GuiPoint,*P_GuiPoint;

/*---------------------------- driver ----------------------------------------*/

/* graphic driver operations */
struct graphicDriverOops
{
    /* set and get pixel in (x, y) */
    void (*setPixel)(GUI_COLOR *c, S32 x, S32 y);
    void (*getPixel)(GUI_COLOR *c, S32 x, S32 y);

    void (*drawHline)(GUI_COLOR *c, S32 x1, S32 x2, S32 y);
    void (*drawVline)(GUI_COLOR *c, S32 x , S32 y1, S32 y2);

    /* draw raw hline */
    void (*drawRawHline)(U8 *pixels, S32 x1, S32 x2, S32 y);
};

/* graphic extension operations */
struct graphicExtOps
{
    /* some 2D operations */
    void (*drawLine)(GUI_COLOR *c, S32 x1, S32 y1, S32 x2, S32 y2);

    void (*drawRect)(GUI_COLOR *c, S32 x1, S32 y1, S32 x2, S32 y2);
    void (*fillRect)(GUI_COLOR *c, S32 x1, S32 y1, S32 x2, S32 y2);

    void (*drawCircle)(GUI_COLOR *c, S32 x, S32 y, S32 r);
    void (*fillCircle)(GUI_COLOR *c, S32 x, S32 y, S32 r);

    void (*drawEllipse)(GUI_COLOR *c, S32 x, S32 y, S32 rx, S32 ry);
    void (*fillEllipse)(GUI_COLOR *c, S32 x, S32 y, S32 rx, S32 ry);
};

typedef struct graphicDriver
{
    /* pixel format and byte per pixel */
    U8 pixelFormat;
    U8 bitsPerPixel;
    U16 pitch;

    /* screen width and height */
    U16 width;
    U16 height;

    /* framebuffer address and ops */
    U8 *framebuffer;

    const struct graphicDriverOops *ops;
    const struct graphicExtOps *extOps;
}GuiGD,*P_GuiGD;

/*---------------------------- dc --------------------------------------------*/

/**
 *  Graphic context
 */
struct GuiGc
{
    /* foreground and background color */
    GUI_COLOR foreground, background;

    /* text style */
    U16 textstyle;
    /* text align */
    U16 textalign;

    /* font 
    struct rtgui_font *font; */
};

enum guiDcType
{
    GUI_DC_HW,
    GUI_DC_CLIENT,
    GUI_DC_BUFFER,
};

typedef struct dcEngine
{
    /* interface */
    void (*drawPoint)(struct GuiDc dc, S32 x, S32 y);
    void (*drawColorPoint)(struct GuiDc dc, S32 x, S32 y, GUI_COLOR color);
    void (*drawVline)(struct GuiDc dc, S32 x, S32 y1, S32 y2);
    void (*drawHline)(struct GuiDc dc, S32 x1, S32 x2, S32 y);
    void (*fillRect)(struct GuiDc dc, P_GuiRect rect);

    StatusType (*fini)(struct GuiDc dc);
}GuiDcEng,*P_GuiDcEng;

typedef struct dc
{
    /* type of device context */
    enum guiDcType type;

    /* dc engine */
    const P_GuiDcEng engine;
}GuiDc,*P_GuiDc;

struct dcHw
{
    GuiDc parent;
    struct GuiWidget *owner;
    const P_GuiGD hwDriver;
};

struct dcBuffer
{
    GuiDc parent;

    /* graphic context */
    struct GuiGc gc;

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
enum appFlag
{
    GUI_APP_FLAG_EXITED  = 0x04,
    GUI_APP_FLAG_SHOWN   = 0x08,
    GUI_APP_FLAG_KEEP    = 0x80,
};

typedef struct GuiApp
{
    U8      id;
    char   *name;

    enum appFlag flag;

    U16     refCnt;
    U16     exitCode;

    /* Task id */
    OS_TID tid;
    /* Message queue */
    OS_EventID   mq;

    U32     winCnt;
    /* window activate count */
    U32     winActiCnt;

    /* the event handler */
    StatusType (*handler)(struct GuiEvent *event);

    void    *userData;
}GuiApp,*P_GuiApp;

/*---------------------------- widget ----------------------------------------*/
typedef struct GuiWidget
{
    /* the widget that contains this widget */
    struct GuiWidget *parent;
    /* the window that contains this widget */
    struct window *topLevel;
    /* the widget children and sibling */
    CoList sibling;

    S32 flag;
    
    /* hardware device context */
    U64 dcType;
    const P_GuiDc dc_engine;

    /* the graphic context of widget */
    struct GuiGc gc;

    /* the widget extent */
    GuiRect extent;
    /* the visiable extent */
    GuiRect extentVisiable;
    /* the rect clip information */
    GuiRegion clip;

    /* minimal width and height of widget */
    S16 minWidth, minHeight;
    /* widget align */
    S32 align;
    U16 border;
    U16 borderStyle;

    /* call back */
    StatusType  (*onFocusIn)(struct GuiWidget *widget, struct GuiEvent *event);
    StatusType (*onFocusOut)(struct GuiWidget *widget, struct GuiEvent *event);

    /* the event handler */
    StatusType (*handler)(struct GuiWidget widget ,struct GuiEvent *event);

    /* user private data */
    U32 userData;

}GuiWidget,*P_GuiWidget;

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
    GuiRect drawingRect;

    /* parent window. Co_NULL if the window is a top level window */
    struct window *parentWindow;

    GuiRegion outerClip;
    GuiRect outerExtent;

    P_GuiWidget foucsWidget;

    /* which app I belong */
    P_GuiApp app;

    /* window style */
    U16 style;

    /* window state flag */
    enum guiWinFlag flag;

    /* last mouse event handled widget */
    P_GuiWidget lastMeventWidget;

    /* window title */
    U8 *title;
    P_GuiWidget _titleWgt;

    /* call back */
    StatusType (*onActivate)(P_GuiWidget widget, struct GuiEvent *event);
    StatusType (*onDeactivate)(P_GuiWidget widget, struct GuiEvent *event);
    StatusType (*onClose)(P_GuiWidget widget, struct GuiEvent *event);

    StatusType (*onKey)(P_GuiWidget widget, struct GuiEvent *event);

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
    P_GuiApp *app;

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
    GuiWidget parent;

    StatusType (*handler)(struct GuiEvent *event);

    /* layout box */
    P_GuiBox layoutBox;

    CoSList children;

}GuiContainer,*P_GuiContainer;

#endif /* _GUI_DEF_H */

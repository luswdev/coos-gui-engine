/**
 *******************************************************************************
 * @file       GuiSystem.h
 * @version    V0.0.1   
 * @date       2019.5.15
 * @brief      This is a file for GUI engine.	
 *******************************************************************************
 */ 

#ifndef _GUI_SYSTEM_H
#define _GUI_SYSTEM_H

/*---------------------------- Include ---------------------------------------*/
#include <coocox.h>
#include <CoOS.h>
#include <OsKernelHeap.h>
#include <OsTask.h>

/*---------------------------- Error Codes   ---------------------------------*/
#define E_TITLE_NULL                (StatusType)22
#define E_ERROR                     (StatusType)23
#define E_NOSYS                     (StatusType)24
#define GUI_REGION_STATUS_FAILURE   (StatusType)25
#define GUI_REGION_STATUS_SUCCESS   (StatusType)26

#define _UI_ABS(x)              ((x)>=0? (x):-(x))

#define GUI_ARGB(a, r, g, b)  \
        ((GUI_COLOR)(((U8)(b)|\
        (((U64)(U8)(g))<<8))|\
        (((U64)(U8)(r))<<16)|\
        (((U64)(U8)(a))<<24)))
#define GUI_RGB(r, g, b)  GUI_ARGB(255, (r), (g), (b))

/*---------------------------- Variable Define -------------------------------*/
const GUI_COLOR red     = GUI_RGB(0xff, 0x00, 0x00);
const GUI_COLOR green   = GUI_RGB(0x00, 0xff, 0x00);
const GUI_COLOR blue    = GUI_RGB(0x00, 0x00, 0xff);
const GUI_COLOR black   = GUI_RGB(0x00, 0x00, 0x00);
const GUI_COLOR white   = GUI_RGB(0xff, 0xff, 0xff);

const GUI_COLOR highLight  = GUI_RGB(0xfc, 0xfc, 0xfc);
const GUI_COLOR darkGrey   = GUI_RGB(0x7f, 0x7f, 0x7f);
const GUI_COLOR lightGrey  = GUI_RGB(0xc0, 0xc0, 0xc0);


/*---------------------------- structure -------------------------------------*/
typedef struct ListNode
{
    struct ListNode *prev;
    struct ListNode *next;
}CoList,*P_CoList;

typedef struct SListNode
{
    struct SListNode *next;
}CoSList,*P_CoSList;

typedef struct rect
{
    S16 x1, x2, y1, y2;

}GuiRect,*P_GuiRect;

typedef struct point
{
    S16 x, y;
}GuiPoint,*P_GuiPoint;

/* Graphic context */
struct gc
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

typedef U64 GUI_COLOR
typedef StatusType  (*EventHandlerPtr)(struct GuiWidget *widget, struct GuiEvent *event);

/**
 * Border style
 */
enum GUI_BORDER_STYLE
{
    GUI_BORDER_NONE = 0,
    GUI_BORDER_SIMPLE,
    GUI_BORDER_RAISE,
    GUI_BORDER_SUNKEN,
    GUI_BORDER_BOX,
    GUI_BORDER_STATIC,
    GUI_BORDER_EXTRA,
    GUI_BORDER_UP,
    GUI_BORDER_DOWN
};
#define GUI_BORDER_DEFAULT_WIDTH  2
#define GUI_WIDGET_DEFAULT_MARGIN 3

extern OSTCB    TCBTbl[CFG_MAX_USER_TASKS+SYS_TASK_NUM];

/*---------------------------- Function Define -------------------------------*/
void *GuiMalloc(U32 size);
void GuiFree(void* memBuf);

void *MemMove(void *dest, const void *src, U64 n);

StatusType GuiSend(P_GuiApp app, struct GuiEvent event);
StatusType GuiSendSync(P_GuiApp app, struct GuiEvent event);
StatusType GuiRecv(struct GuiEvent event);

#endif /* _GUI_SYSTEM_H */
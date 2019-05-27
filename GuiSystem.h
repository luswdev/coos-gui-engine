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
#define E_TITLE_NULL          (StatusType)22
#define E_ERROR               (StatusType)23	

/*---------------------------- structure -------------------------------------*/
typedef struct listNode
{
    struct listNode *prev;
    struct listNode *next;
}CoList,*P_CoList;

typedef struct rect
{
    S16 x1, x2, y1, y2;

}GuiRect,*P_GuiRect;

typedef struct region
{
    GuiRect extent;

    U32 size;
    U32 nubRects;

}GuiRegion,*P_GuiRegion;

typedef StatusType (*EventHandlerPtr)(struct GuiWidget *widget, struct GuiEvent *event);

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

StatusType GuiSend(P_GuiApp app, struct GuiEvent event);
StatusType GuiSendSync(P_GuiApp app, struct GuiEvent event);
StatusType GuiRecv(struct GuiEvent event);

#endif /* _GUI_SYSTEM_H */
/**
 *******************************************************************************
 * @file       GuiSystem.h
 * @version    V0.0.1   
 * @date       2019.5.15
 * @brief      This is a file for GUI engine.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 

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

extern OSTCB    TCBTbl[CFG_MAX_USER_TASKS+SYS_TASK_NUM];

/*---------------------------- Function Define -------------------------------*/
void *GuiMalloc(U32 size);
void GuiFree(void* memBuf);

StatusType GuiSend(P_GuiApp app, struct GuiEvent event);
StatusType GuiSendSync(P_GuiApp app, struct GuiEvent event);
StatusType GuiRecv(struct GuiEvent event);
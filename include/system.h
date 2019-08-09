/**
 *******************************************************************************
 * @file       system.h
 * @version    V0.0.2
 * @date       2019.8.9
 * @brief      This is a file for GUI engine.	
 *******************************************************************************
 */ 

#ifndef _COGUI_SYSTEM_H
#define _COGUI_SYSTEM_H

#include <coocox.h>
#include <CoOS.h>
#include <OsKernelHeap.h>
#include <OsTask.h>

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

/*const GUI_COLOR red     = GUI_RGB(0xff, 0x00, 0x00);
const GUI_COLOR green   = GUI_RGB(0x00, 0xff, 0x00);
const GUI_COLOR blue    = GUI_RGB(0x00, 0x00, 0xff);
const GUI_COLOR black   = GUI_RGB(0x00, 0x00, 0x00);
const GUI_COLOR white   = GUI_RGB(0xff, 0xff, 0xff);

const GUI_COLOR highLight  = GUI_RGB(0xfc, 0xfc, 0xfc);
const GUI_COLOR darkGrey   = GUI_RGB(0x7f, 0x7f, 0x7f);
const GUI_COLOR lightGrey  = GUI_RGB(0xc0, 0xc0, 0xc0);*/

#define COGUI_ASSERT(EX) 								\
if(!(EX)){											    \
	cogui_assert_handler(#EX, __FUNCTION__, __LINE__);	\
}													    \

extern OSTCB TCBTbl[CFG_MAX_USER_TASKS+SYS_TASK_NUM];

void cogui_system_init(void *par);

void *cogui_malloc(U32 size);
void cogui_free(void* memBuf);

void *cogui_memmove(void *dest, const void *src, U64 n);

StatusType cogui_ack(struct cogui_event *event, StatusType status);

StatusType cogui_send(cogui_app_t *app, struct cogui_event *event);
StatusType cogui_send_sync(cogui_app_t *app, struct cogui_event *event);
struct cogui_event *cogui_recv(OS_EventID mq, StatusType *result);

void cogui_assert_handler(const char *ex_string, const char *func, U32 line);

#endif /* _COGUI_SYSTEM_H */

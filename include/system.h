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

#define COGUI_ASSERT(EX) 								\
if(!(EX)){											    \
	cogui_assert_handler(#EX, __FUNCTION__, __LINE__);	\
}													    \

#define COGUI_GET_LIST_NEXT(l)  ((l)->list.next)
#define COGUI_GET_LIST_PREV(l)  ((l)->list.prev)
#define COGUI_GET_SLIST_NEXT(l) ((l)->slist.next)

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

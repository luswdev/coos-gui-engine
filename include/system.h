/**
 *******************************************************************************
 * @file       system.h
 * @version    V0.0.3
 * @date       2019.9.29
 * @brief      This is a file for GUI engine.	
 *******************************************************************************
 */ 

#ifndef _COGUI_SYSTEM_H
#define _COGUI_SYSTEM_H

#include "app.h"

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

#define COGUI_LIST(s) (struct list_node *)(s)

extern OSTCB TCBTbl[CFG_MAX_USER_TASKS+SYS_TASK_NUM];

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

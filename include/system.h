/**
 *******************************************************************************
 * @file       system.h
 * @version    V0.1.0
 * @date       2019.10.5
 * @brief      GUI engine system header file.	
 *******************************************************************************
 */ 

#ifndef _COGUI_SYSTEM_H
#define _COGUI_SYSTEM_H

#include "app.h"
#include <coocox.h>

/* Redefine data type define to current code style */
typedef signed   char          co_int8_t;           /**<  8-bit signed integer      */
typedef unsigned char          co_uint8_t;	        /**<  8-bit unsigned integer    */
typedef signed   short         co_int16_t;          /**< 16-bit signed integer      */
typedef unsigned short         co_uint16_t;         /**< 16-bit unsigned integer    */
typedef signed   int           co_int32_t;          /**< 32-bit signed integer      */
typedef unsigned int           co_uint32_t;         /**< 32-bit unsigned integer    */
typedef signed   long long     co_int64_t;          /**< 64-bit signed integer      */
typedef unsigned long long     co_uint64_t;         /**< 64-bit unsigned integer    */

typedef co_int8_t              co_bool_t;           /**< Boolean type               */

#define E_ERROR                (StatusType)22

#define _UI_ABS(x)             ((x)>=0? (x): -(x))  /**< Simple abs function        */

/** assert function */
#define COGUI_ASSERT(EX) 								\
if(!(EX)){											    \
	cogui_assert_handler(#EX, __FUNCTION__, __LINE__);	\
}													    \

#define COGUI_INIT_RECR(r)              \
{                                       \
    (r)->x1 = 0;                        \
    (r)->x2 = 0;                        \
    (r)->y1 = 0;                        \
    (r)->y2 = 0;                        \
}    

#define COGUI_SET_RECT(r, x, y, w, h)   \
{                                       \
    (r)->x1 = (x);                      \
    (r)->x2 = (x) + (w);                \
    (r)->y1 = (y);                      \
    (r)->y2 = (y) + (h);                \
}                                       \

#define COGUI_RECT_EXPAND(r, d)         \
{                                       \
    (r)->x1 -= (d);                     \
    (r)->x2 += (d);                     \
    (r)->y1 -= (d);                     \
    (r)->y2 += (d);                     \
}                                       \

#define COGUI_LIST_PREV(l) ((l)->prev)
#define COGUI_LIST_NEXT(l) ((l)->next)

/**
 * @struct   cogui_list_node dc.h	
 * @brief    Double linked list struct
 * @details  This struct is double linked list.
 */
struct cogui_list_node
{
    struct list_node *prev;
    struct list_node *next;
};
typedef struct cogui_list_node cogui_list_t;

/**
 * @struct   cogui_slist_node dc.h	
 * @brief    Single linked list struct
 * @details  This struct is single linked list.
 */
struct cogui_slist_node
{
    struct cogui_slist_node *next;
};
typedef struct cogui_slist_node cogui_slist_t;

/**
 * @struct   cogui_point dc.h	
 * @brief    2D point struct
 * @details  This struct is 2D point.
 */
struct cogui_point
{
    S16 x, y;
};
typedef struct cogui_point cogui_point_t;

void cogui_system_init(void);

/* memory manange from CoOS */
void *cogui_malloc(U32 size);
void cogui_free(void* memBuf);

/* sync function from CoOS */
StatusType cogui_ack(struct cogui_event *event, StatusType status);
StatusType cogui_send(cogui_app_t *app, struct cogui_event *event);
StatusType cogui_send_sync(cogui_app_t *app, struct cogui_event *event);
StatusType cogui_recv(OS_EventID mq, struct cogui_event *event, co_int32_t timeout);

/* math function for cogui */
U64 cogui_pow(S32 x, S32 y);
void cogui_itoa(co_int16_t n, char* ss);

/* mem function for cogui */
void *cogui_memset(void *s, int c, U64 cnt);
void *cogui_memcpy(void *dest, const void *src, U64 cnt);
void *cogui_memmove(void *dest, const void *src, U64 cnt);
S32 cogui_memcmp(const void *str1, const void *str2, U64 cnt);

/* string function for cogui */
char *cogui_strdup(const char *str);
U64 cogui_strlen(const char *str);
S32 cogui_strncmp(const char *str1, const char *str2, U64 cnt);
S32 cogui_strcmp(const char *str1, const char *str2);

/* debug function */
int cogui_printf(const char *str, ...);
void cogui_assert_handler(const char *ex_string, const char *func, U32 line);

#endif /* _COGUI_SYSTEM_H */

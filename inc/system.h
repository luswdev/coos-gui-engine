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

/****** 宣哲到此一遊:) 2019/01/09
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
    co_int16_t x, y;
};
typedef struct cogui_point cogui_point_t;

/**
 * rectangle
 */
struct cogui_rect
{
    co_int16_t x1, x2, y1, y2;
};
typedef struct cogui_rect cogui_rect_t;

struct cogui_event;
struct cogui_app;
typedef struct cogui_app cogui_app_t;

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
co_uint64_t cogui_pow(co_int32_t x, co_int32_t y);
void cogui_itoa(co_int16_t n, char* ss);

/* mem function for cogui */
void *cogui_memset(void *s, int c, co_uint64_t cnt);
void *cogui_memcpy(void *dest, const void *src, co_uint64_t cnt);
void *cogui_memmove(void *dest, const void *src, co_uint64_t cnt);
co_int32_t cogui_memcmp(const void *str1, const void *str2, co_uint64_t cnt);

/* string function for cogui */
char *cogui_strdup(const char *str);
co_uint64_t cogui_strlen(const char *str);
co_int32_t cogui_strncmp(const char *str1, const char *str2, co_uint64_t cnt);
co_int32_t cogui_strcmp(const char *str1, const char *str2);

/* debug function */
int cogui_printf(const char *str, ...);

void cogui_assert_handler(const char *ex_string, const char *func, U32 line);

#endif /* _COGUI_SYSTEM_H */

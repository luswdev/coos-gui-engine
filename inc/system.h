/**
 *******************************************************************************
 * @file       system.h
 * @version    V0.7.1
 * @date       2020.02.23
 * @brief      GUI engine system header file.	
 *******************************************************************************
 */ 

#ifndef __COGUI_SYSTEM_H__
#define __COGUI_SYSTEM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* define some type variables */
typedef signed   char           bool_t;           /**< Boolean type                */

/* GUI engine status type */
#define GUI_E_ERROR            (StatusType)22       /**< occurred error status       */
#define GUI_E_OK               (StatusType)23       /**< everythings OK status       */
#define GUI_E_APP_NULL         (StatusType)24       /**< run null application status */
#define GUI_E_APP_FULL         (StatusType)25       /**< run null application status */

/* some math inline function */
#define ABS(x)             ((x)>=0? (x): -(x))      /**< simple abs function         */

/** assert function */
#define COGUI_ASSERT(EX) 								\
if(!(EX)){											    \
	cogui_assert_handler(#EX, __FUNCTION__, __LINE__);	\
}													    \

/** initial a rectangle to zero */
#define COGUI_INIT_RECR(r)              \
{                                       \
    (r)->x1 = 0;                        \
    (r)->x2 = 0;                        \
    (r)->y1 = 0;                        \
    (r)->y2 = 0;                        \
}    

/** setting a rectangle */
#define COGUI_SET_RECT(r, x, y, w, h)   \
{                                       \
    (r)->x1 = (x);                      \
    (r)->x2 = (x) + (w);                \
    (r)->y1 = (y);                      \
    (r)->y2 = (y) + (h);                \
}                                       \

/** expand a rectangle */
#define COGUI_RECT_EXPAND(r, d)         \
{                                       \
    (r)->x1 -= (d);                     \
    (r)->x2 += (d);                     \
    (r)->y1 -= (d);                     \
    (r)->y2 += (d);                     \
}                                       \

/** resize a rectangle with padding value */
#define COGUI_RECT_PADDING(r, p)    \
{                                   \
    (r)->x1 += (p)>>8  & 0x0FF;     \
    (r)->x2 -= (p)     & 0x0FF;     \
    (r)->y1 += (p)>>24 & 0x0FF;     \
    (r)->y2 -= (p)>>16 & 0x0FF;     \
}                                   \

/* rectangle width and height */
#define COGUI_RECT_WIDTH(r)         ((r)->x2-(r)->x1)
#define COGUI_RECT_HEIGHT(r)        ((r)->y2-(r)->y1)

/* list previous and next node */
#define COGUI_LIST_PREV(l) ((l)->prev)
#define COGUI_LIST_NEXT(l) ((l)->next)

/** return a new result type */
#define COGUI_RETURN_TYPE(r)    \
    if ((r) == E_OK)            \
        return GUI_E_OK;        \
    else                        \
        return GUI_E_ERROR;     \

/**
 * @struct   cogui_list_node
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
 * @struct   cogui_slist_node	
 * @brief    Single linked list struct
 * @details  This struct is single linked list.
 */
struct cogui_slist_node
{
    struct cogui_slist_node *next;
};
typedef struct cogui_slist_node cogui_slist_t;

/**
 * @struct   cogui_point
 * @brief    2D point struct
 * @details  This struct is 2D point.
 */
struct cogui_point
{
    int16_t x, y;
};
typedef struct cogui_point cogui_point_t;

/**
 * @struct   cogui_rect	
 * @brief    Rectangle struct
 * @details  This struct is rectangle.
 */
struct cogui_rect
{
    int16_t x1, x2, y1, y2;
};
typedef struct cogui_rect cogui_rect_t;

struct cogui_event;
struct cogui_app;
typedef struct cogui_app cogui_app_t;

void cogui_system_init(void);

/* memory manange from CoOS */
void *cogui_malloc(U32 size);
void cogui_free(void* ptr);

/* sync function from CoOS */
StatusType cogui_ack(struct cogui_event *event, StatusType status);
StatusType cogui_send(cogui_app_t *app, struct cogui_event *event);
StatusType cogui_send_sync(cogui_app_t *app, struct cogui_event *event);
StatusType cogui_recv(OS_EventID mq, struct cogui_event *event, int32_t timeout);

/* math function for cogui */
uint64_t cogui_pow(int32_t base, int32_t exp);
void cogui_itoa(int16_t n, char* ss);

/* mem function for cogui */
void *cogui_memset(void *buf, int val, uint64_t size);
void *cogui_memcpy(void *dest, const void *src, uint64_t size);
void *cogui_memmove(void *dest, const void *src, uint64_t size);
int32_t cogui_memcmp(const void *str1, const void *str2, uint64_t size);

/* string function for cogui */
char *cogui_strdup(const char *str);
uint64_t cogui_strlen(const char *str);
uint64_t cogui_strnlen(const char *str, uint64_t maxlen);
int32_t cogui_strncmp(const char *str1, const char *str2, uint64_t size);
int32_t cogui_strcmp(const char *str1, const char *str2);

/* debug function */
int cogui_printf(const char *fmt, ...);
int cogui_sprintf(char *buf, const char *fmt, ...);
void cogui_assert_handler(const char *ex_string, const char *func, U32 line);

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_SYSTEM_H__ */
